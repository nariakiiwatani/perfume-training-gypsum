/*!
*/

#include "BvhTask.h"

BvhTask::BvhTask(string file)
:FactorTask()
{
	model_.load(file);
}

BvhTask::~BvhTask()
{
	model_.unload();
}

void BvhTask::update()
{
//	incFrame(1);
	model_.update();
}

void BvhTask::drawModel()
{ 
//	model_.draw();
	
	glEnable(GL_DEPTH_TEST);
	ofEnableAlphaBlending();
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	ofPushStyle();
	ofFill();

	struct Joints {
		const ofxBvhJoint* sta;
		const ofxBvhJoint* end;
		bool sphere;
	};

	Joints joints[] = {
		{ model_.getJoint("Hips"),			model_.getJoint("Neck"),						false},
		{ model_.getJoint("Neck"),			model_.getJoint("Head")->getChildren()[0],		true },
		{ model_.getJoint("Neck"),			model_.getJoint("LeftShoulder"),				false},
		{ model_.getJoint("LeftShoulder"),	model_.getJoint("LeftElbow"),					true },
		{ model_.getJoint("LeftElbow"),		model_.getJoint("LeftWrist")->getChildren()[0],					true },
		{ model_.getJoint("Neck"),			model_.getJoint("RightShoulder"),				false},
		{ model_.getJoint("RightShoulder"),	model_.getJoint("RightElbow"),					true },
		{ model_.getJoint("RightElbow"),	model_.getJoint("RightWrist")->getChildren()[0],					true },
		{ model_.getJoint("Hips"),			model_.getJoint("LeftHip"),						false},
		{ model_.getJoint("LeftHip"),		model_.getJoint("LeftKnee"),					true },
		{ model_.getJoint("LeftKnee"),		model_.getJoint("LeftAnkle"),					true },
		{ model_.getJoint("Hips"),			model_.getJoint("RightHip"),					false},
		{ model_.getJoint("RightHip"),		model_.getJoint("RightKnee"),					true },
		{ model_.getJoint("RightKnee"),		model_.getJoint("RightAnkle"),					true },
	};
	for(int i = 0; i < 14; ++i) {
		ofPushMatrix();
		ofVec3f wpos = joints[i].sta->getPosition();
		ofVec3f oppo = joints[i].end->getPosition();
		ofTranslate(wpos);
		oppo -= wpos;
		ofSetColor(0,0,0,200);
		ofSetLineWidth(10);
		ofLine(0,0,0, oppo.x,oppo.y,oppo.z);
		ofSetColor(255,255,255,200);
		ofSetLineWidth(14);
		ofLine(0,0,0, oppo.x,oppo.y,oppo.z);
		if(joints[i].sphere) {
			ofSetColor(255,0,255,200);
			ofSphere(oppo,4);
		}
		ofPopMatrix();
	}
	ofPopStyle();
	ofDisableAlphaBlending();
	glDisable(GL_DEPTH_TEST);
}

void BvhTask::incFrame(int frame)
{
	setFrame(model_.getFrame()+frame);
}

void BvhTask::decFrame(int frame)
{
	setFrame(model_.getFrame()-frame);
}

void BvhTask::randomFrame()
{
	setFrame(ofRandom(getNumFrames()));
}

int BvhTask::getNumFrames()
{
	return model_.getNumFrames();
}

void BvhTask::setFrame(int frame)
{
	model_.setFrame(frame);
}

int BvhTask::getFrame()
{
	return model_.getFrame();
}

ofVec3f BvhTask::getPosition()
{
	return model_.getJoint("Hips")->getPosition();
}

float BvhTask::getTall()
{
	return 164;
}

/* EOF */