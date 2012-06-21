/*!
*/

#include "SkeletonDraw.h"
#include "DeviceTask.h"
#include "FactorManager.h"
#include "PrfmRSMDef.h"
#include "TaskPose.h"
#include "ofCamera.h"
#include "ofxTrackedUser.h"
#include "CustomJoint.h"

SkeletonDraw::SkeletonDraw()
:Factor()
,source_(NULL)
{
}

void SkeletonDraw::proc()
{
	if(source_) {
		getManager()->addDraw(PRIO_SKELETON_2D, this);
	}
}

void SkeletonDraw::draw(int prio)
{
	ofSetColor(255, 255, 255);
	ofSetRectMode(OF_RECTMODE_CORNER);
	source_->getUserGenerator()->draw(320, 240);
}

void SkeletonDraw::bindTask(string bind_type, FactorTask* task)
{
	source_ = dynamic_cast<DeviceTask*>(task);
}

/* ====================================== */
/* ====================================== */

SkeletonDrawTransformed::SkeletonDrawTransformed()
:Factor()
,source_(NULL)
,camera_(NULL)
,transform_(NULL)
{
}

void SkeletonDrawTransformed::proc()
{
	if(source_ && source_->isValid()) {
		getManager()->addDraw(PRIO_SKELETON_3D, this);
	}
}


void SkeletonDrawTransformed::draw(int prio)
{
	if(camera_) {
		camera_->begin();
	}
	const ofVec3f& trans = transform_->getTranslation();
	const ofVec3f& scale = transform_->getScale();

	ofPushMatrix();
	glEnable(GL_DEPTH_TEST);
	ofEnableAlphaBlending();
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	ofPushStyle();
	ofTranslate(trans);
	ofScale(-1,-1,1);

	ofTranslate(-source_->hips_);
	struct Joints {
		ofVec3f& pos0;
		ofVec3f& pos1;
		bool sphere;
	};
	Joints joints[] = {
		{ source_->l_hi_,		source_->r_hi_,	false},
		{ source_->hips_,		source_->neck_,	false},
		{ source_->neck_,		source_->head_,	true},
		{ source_->neck_,		source_->l_sh_,	false},
		{ source_->l_sh_,		source_->l_el_,	true},
		{ source_->l_el_,		source_->l_wr_,	true},
		{ source_->neck_,		source_->r_sh_,	false},
		{ source_->r_sh_,		source_->r_el_,	true},
		{ source_->r_el_,		source_->r_wr_,	true},
		{ source_->l_hi_,		source_->l_kn_,	true},
		{ source_->l_kn_,		source_->l_an_,	true},
		{ source_->r_hi_,		source_->r_kn_,	true},
		{ source_->r_kn_,		source_->r_an_,	true},
	};
	for(int i = 0; i < 13; ++i) {
		ofSetColor(0,0,0,128);
		ofSetLineWidth(10);
		ofLine(joints[i].pos0, joints[i].pos1);
		ofSetColor(255,255,0,128);
		ofSetLineWidth(14);
		ofLine(joints[i].pos0, joints[i].pos1);
		if(joints[i].sphere) {
			ofSetColor(0,255,0,128);
			ofSphere(joints[i].pos1,4);
		}
	}
	ofPopStyle();
	ofDisableAlphaBlending();
	glDisable(GL_DEPTH_TEST);
	ofPopMatrix();

	if(camera_) {
		camera_->end();
	}
	
}

void SkeletonDrawTransformed::bindTask(string type, FactorTask* task)
{
	if(type=="source") {
		source_ = dynamic_cast<CustomJoint*>(task);
	}
	else/* if(type=="transform")*/ {
		transform_ = dynamic_cast<TaskPose*>(task);
	}

}

void SkeletonDrawTransformed::setCamera(ofCamera* camera)
{
	camera_ = camera;
}


/* EOF */