/*!
*/

#include "PoseCheck.h"
#include "FactorManager.h"
#include "PrfmRSMDef.h"
#include "BvhTask.h"
#include "CustomJoint.h"
#include "DebugString.h"
#include "DeviceTask.h"
#include "TaskKey.h"

namespace {
const int CROP_WIDTH = 214;
}

PoseCheck::PoseCheck()
:Factor()
,model_(NULL)
,source_(NULL)
,device_(NULL)
,keyboard_(NULL)
,ok_count_(0)
,ok_rate_(0.98f)
,ok_rate2_(0.96f)
,bad_rate_(0.90f)
,match_rate_(0)
,save_folder_("")
{
	image_capture_.allocate(640,480,3);
	image_divide_capture_.allocate(CROP_WIDTH, 480, 3);
	depth_capture_.allocate(640,480,1);
	sprintf(fmt_str_, "%s", "%04d");
}

PoseCheck::~PoseCheck()
{
	image_capture_.clear();
	image_divide_capture_.clear();
	depth_capture_.clear();
}

void PoseCheck::setFolder(string folder)
{
	save_folder_ = folder;
	ofDirectory depth(folder+"/depth");
	ofDirectory image(folder+"/image");
	ofDirectory divide(folder+"/image_div3");
	if(!depth.exists()) {
		depth.create();
	}
	if(!image.exists()) {
		image.create();
	}
	if(!divide.exists()) {
		divide.create();
	}
}

void PoseCheck::proc()
{
	getManager()->addDraw(PRIO_GAUGE, this);
	unsigned int repeat = keyboard_->getTrigger()|keyboard_->getRepeat();
	
	if(repeat & KEY_X) {
		ok_rate2_ += 0.001f;
		if(ok_rate2_ > ok_rate_) {
			ok_rate2_ = ok_rate_;
		}
	}
	else if(repeat & KEY_Z) {
		ok_rate2_ -= 0.001f;
		if(ok_rate2_ < bad_rate_) {
			ok_rate2_ = bad_rate_;
		}
	}
	if(keyboard_->getTrigger() & KEY_ENTER) {
		ok_count_ = OK_COUNT_MAX;
	}
	else {
		if(!source_->isValid()) {
			return;
		}
		match_rate_ = getMatchRate();
		float inversed_match_rate = getMatchRateInverse();
		if(inversed_match_rate > match_rate_) {
			match_rate_ = inversed_match_rate;
		}
		if(match_rate_ > ok_rate_) {
			ok_count_ += 5;
			printf("%.3f\n", match_rate_);
		}
		else if(match_rate_ > ok_rate2_) {
			ok_count_ += 2;
		}
		else if(match_rate_ < bad_rate_) {
			ok_count_ = 0;
		}
		static int count = 0;
		if(count++ % 60 == 0) {
			printf("%.3f\n", match_rate_);
		}
	}
	getManager()->addDraw(PRIO_SHUTTER, this);
	
	if(ok_count_ >= OK_COUNT_MAX) {
		model_->incFrame();
		getManager()->addDraw(PRIO_SCREEN_SHOT, this);
		ok_count_ = 0;
	}
}

float PoseCheck::getMatchRate()
{
	ofxBvh* bvh = model_->getModel();
	struct Limb {
		ofVec3f mdl;
		ofVec3f src;
		float dot;
	};
	int limb_count = 14;
	Limb limbs[] = {
		{ 	bvh->getJoint("Neck")->getPosition()					- bvh->getJoint("Hips")->getPosition(),			source_->neck_ - source_->hips_ },
		{ 	bvh->getJoint("Head")->getChildren()[0]->getPosition()	- bvh->getJoint("Neck")->getPosition(),			source_->head_ - source_->neck_ },
		{ 	bvh->getJoint("LeftShoulder")->getPosition()			- bvh->getJoint("Neck")->getPosition(),			source_->l_sh_ - source_->neck_ },
		{ 	bvh->getJoint("LeftElbow")->getPosition()				- bvh->getJoint("LeftShoulder")->getPosition(),	source_->l_el_ - source_->l_sh_ },
		{ 	bvh->getJoint("LeftWrist")->getPosition()				- bvh->getJoint("LeftElbow")->getPosition(),	source_->l_wr_ - source_->l_el_ },
		{ 	bvh->getJoint("RightShoulder")->getPosition()			- bvh->getJoint("Neck")->getPosition(),			source_->r_sh_ - source_->neck_ },
		{ 	bvh->getJoint("RightElbow")->getPosition()				- bvh->getJoint("RightShoulder")->getPosition(),source_->r_el_ - source_->r_sh_ },
		{ 	bvh->getJoint("RightWrist")->getPosition()				- bvh->getJoint("RightElbow")->getPosition(),	source_->r_wr_ - source_->r_el_ },
		{ 	bvh->getJoint("LeftHip")->getPosition()					- bvh->getJoint("Hips")->getPosition(),			source_->l_hi_ - source_->hips_ },
		{ 	bvh->getJoint("LeftKnee")->getPosition()				- bvh->getJoint("LeftHip")->getPosition(),		source_->l_kn_ - source_->l_hi_ },
		{ 	bvh->getJoint("LeftAnkle")->getPosition()				- bvh->getJoint("LeftKnee")->getPosition(),		source_->l_an_ - source_->l_kn_ },
		{ 	bvh->getJoint("RightHip")->getPosition()				- bvh->getJoint("Hips")->getPosition(),			source_->r_hi_ - source_->hips_ },
		{ 	bvh->getJoint("RightKnee")->getPosition()				- bvh->getJoint("RightHip")->getPosition(),		source_->r_kn_ - source_->r_hi_ },
		{ 	bvh->getJoint("RightAnkle")->getPosition()				- bvh->getJoint("RightKnee")->getPosition(),	source_->r_an_ - source_->r_kn_ },
	};
	float match_rate = 0;
	vector<float> dots;
	for(int i = 0; i < limb_count; ++i) {
		limbs[i].mdl.normalize();
		limbs[i].src.normalize();
		limbs[i].src.x *= -1;
		limbs[i].src.y *= -1;
		limbs[i].dot = limbs[i].mdl.dot(limbs[i].src);
//		match_rate += limbs[i].dot/(float)limb_count;
		dots.push_back(limbs[i].dot);
	}
	sort(dots.begin(),dots.end());
	// 悪いデータを捨ててみる
	int ignore_count = 2;
	for(int i = ignore_count; i < limb_count; ++i) {
		match_rate += dots[i]/(float)(limb_count-ignore_count);
	}
	return match_rate;
}

float PoseCheck::getMatchRateInverse()
{
	ofxBvh* bvh = model_->getModel();
	struct Limb {
		ofVec3f mdl;
		ofVec3f src;
		float dot;
	};
	int limb_count = 14;
	Limb limbs[] = {
		{ 	bvh->getJoint("Neck")->getPosition()									- bvh->getJoint("Hips")->getPosition(),			source_->neck_ - source_->hips_ },
		{ 	bvh->getJoint("Head")->getChildren()[0]->getPosition()					- bvh->getJoint("Neck")->getPosition(),			source_->head_ - source_->neck_ },
		{ 	bvh->getJoint("LeftShoulder")->getPosition()							- bvh->getJoint("Neck")->getPosition(),			source_->r_sh_ - source_->neck_ },
		{ 	bvh->getJoint("LeftElbow")->getPosition()								- bvh->getJoint("LeftShoulder")->getPosition(),	source_->r_el_ - source_->r_sh_ },
		{ 	bvh->getJoint("LeftWrist")->getChildren()[0]->getPosition()				- bvh->getJoint("LeftElbow")->getPosition(),	source_->r_wr_ - source_->r_el_ },
		{ 	bvh->getJoint("RightShoulder")->getPosition()							- bvh->getJoint("Neck")->getPosition(),			source_->l_sh_ - source_->neck_ },
		{ 	bvh->getJoint("RightElbow")->getPosition()								- bvh->getJoint("RightShoulder")->getPosition(),source_->l_el_ - source_->l_sh_ },
		{ 	bvh->getJoint("RightWrist")->getChildren()[0]->getPosition()			- bvh->getJoint("RightElbow")->getPosition(),	source_->l_wr_ - source_->l_el_ },
		{ 	bvh->getJoint("LeftHip")->getPosition()									- bvh->getJoint("Hips")->getPosition(),			source_->r_hi_ - source_->hips_ },
		{ 	bvh->getJoint("LeftKnee")->getPosition()								- bvh->getJoint("LeftHip")->getPosition(),		source_->r_kn_ - source_->r_hi_ },
		{ 	bvh->getJoint("LeftAnkle")->getPosition()								- bvh->getJoint("LeftKnee")->getPosition(),		source_->r_an_ - source_->r_kn_ },
		{ 	bvh->getJoint("RightHip")->getPosition()								- bvh->getJoint("Hips")->getPosition(),			source_->l_hi_ - source_->hips_ },
		{ 	bvh->getJoint("RightKnee")->getPosition()								- bvh->getJoint("RightHip")->getPosition(),		source_->l_kn_ - source_->l_hi_ },
		{ 	bvh->getJoint("RightAnkle")->getPosition()								- bvh->getJoint("RightKnee")->getPosition(),	source_->l_an_ - source_->l_kn_ },
	};
	float match_rate = 0;
	vector<float> dots;
	for(int i = 0; i < limb_count; ++i) {
		limbs[i].mdl.normalize();
		limbs[i].src.normalize();
		limbs[i].src.x *= -1;
		limbs[i].src.y *= -1;
		limbs[i].dot = limbs[i].mdl.dot(limbs[i].src);
//		match_rate += limbs[i].dot/(float)limb_count;
		dots.push_back(limbs[i].dot);
	}
	sort(dots.begin(),dots.end());
	// 悪いデータを捨ててみる
	int ignore_count = 2;
	for(int i = ignore_count; i < limb_count; ++i) {
		match_rate += dots[i]/(float)(limb_count-ignore_count);
	}
	return match_rate;
}

void PoseCheck::draw(int prio)
{
	if(prio == PRIO_SCREEN_SHOT) {
		ofxImageGenerator* image = device_->getImageGenerator();
		ofxDepthGenerator* depth = device_->getDepthGenerator();
		memcpy(image_capture_.getPixels(), image->getPixels(), sizeof(char)*640*480*3);
		memcpy(depth_capture_.getPixels(), depth->getXnDepthPixels(), sizeof(short)*640*480);
		int crop_x = (int)source_->getHipPos2D().x - CROP_WIDTH/2;
		if(crop_x < 0) {
			crop_x = 0;
		}
		else if(crop_x > 640 - CROP_WIDTH-1) {
			crop_x = 640 - CROP_WIDTH-1;
		}
		image_capture_.cropTo(image_divide_capture_, crop_x, 0, CROP_WIDTH, 480);

		char number[8]={};
		sprintf(number, fmt_str_, model_->getFrame()-1);
		string number_str = ofToString(number);

		ofSaveImage(image_capture_, save_folder_+"/image/image_"+number_str+".jpg");
		ofSaveImage(image_divide_capture_, save_folder_+"/image_div3/image_"+number_str+".jpg");
		ofSaveImage(depth_capture_, save_folder_+"/depth/image_"+number_str+".png");
	}
	else if(prio == PRIO_SHUTTER) {
		ofEnableAlphaBlending();
		ofFill();
		ofSetColor(ofColor(255,255,255,ok_count_*255/60));
		ofRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
		ofDisableAlphaBlending();
	}
	else if(prio == PRIO_GAUGE) {
		int x = 0;
		int y = 250;
		int w = 320;
		int h = 30;
		ofNoFill();
		ofSetColor(0,0,0);
		ofSetLineWidth(1);
		ofRect(x,y,w,h);
		if(match_rate_ >= bad_rate_) {
			float ratio = (match_rate_-bad_rate_)/(ok_rate_-bad_rate_);
			ofFill();
			ofSetColor(255*ratio,0,0);
			ofRect(x+1,y+1,w*ratio-2,h-2);
		}
		float ok_ratio = (ok_rate2_-bad_rate_)/(ok_rate_-bad_rate_);
		ofSetColor(255,0,0);
		ofLine(w*ok_ratio,y,w*ok_ratio,y+h);
	}
}

void PoseCheck::bindTask(string type, FactorTask* task)
{
	if(type == "source") {
		source_ = dynamic_cast<CustomJoint*>(task);
	}
	else if(type == "model") {
		model_ = dynamic_cast<BvhTask*>(task);
		int frames = model_->getNumFrames();
		int digit = 1;
		while(frames >= 10) {
			frames /= 10;
			++digit;
		}
		fmt_str_[2] = ofToString(digit).c_str()[0];
	}
	else if(type == "keyboard") {
		keyboard_ = dynamic_cast<TaskKey*>(task);
	}
	else {
		device_ = dynamic_cast<DeviceTask*>(task);
	}
}

/* EOF */