/*!
*/

#include "PoseControl.h"
#include "TaskKey.h"
#include "TaskPose.h"
#include "BvhTask.h"
#include "DeviceTask.h"
#include "ofxTrackedUser.h"
#include "DebugString.h"

PoseControl::PoseControl()
:Factor()
,keyboard_(NULL)
,target_(NULL)
,model_(NULL)
,source_(NULL)
{
}

void PoseControl::proc()
{
#ifdef _DEBUG
	if(keyboard_) {
		procKeyboard();
	}
#endif // _DEBUG
	if(target_) {
		if(model_) {
			setting_.trans = model_->getPosition();
			if(ofxTrackedUser* user = source_->getTrackedUser(0)) {
				float tall = model_->getTall();
				float ratio =  tall/((user->left_lower_leg.position[1].Y+user->right_lower_leg.position[1].Y)/2.0f - user->neck.position[0].Y);
				setting_.scale.x = -ratio;
				setting_.scale.y = -ratio;
				setting_.scale.z = 0.3f*ratio;
			}
		}
		target_->setTranslation(setting_.trans);
		target_->setScale(setting_.scale);
	}
	setting_.showDebugText();
}

void PoseControl::bindTask(string type, FactorTask* task)
{
	if(type == "keyboard") {
		keyboard_ = dynamic_cast<TaskKey*>(task);
	}
	else if(type == "pose") {
		target_ = dynamic_cast<TaskPose*>(task);
	}
	else if(type == "source") {
		source_ = dynamic_cast<DeviceTask*>(task);
	}
	else/* if(type == "model")*/ {
		model_ = dynamic_cast<BvhTask*>(task);
	}
}


void PoseControl::procKeyboard()
{
	unsigned int trigger = keyboard_->getTrigger();
	unsigned int repeat = keyboard_->getRepeat();
	unsigned int hold = keyboard_->getHold();
	unsigned int key = trigger|repeat;
	if(key & KEY_UP) {
		setting_.decIndex();
	}
	if(key & KEY_DOWN) {
		setting_.incIndex();
	}
	if(key & KEY_LEFT) {
		setting_.decValue();
	}
	if(key & KEY_RIGHT) {
		setting_.incValue();
	}
}


namespace {
	enum {
		INDEX_MOVE_X,
		INDEX_MOVE_Y,
		INDEX_MOVE_Z,
		INDEX_SCALE_X,
		INDEX_SCALE_Y,
		INDEX_SCALE_Z,
		INDEX_COUNT
	};
}
PoseControl::PoseSetting::PoseSetting()
:trans(0,164,0)
,scale(-1,-1,0.1f)
,index(0)
{
}

void PoseControl::PoseSetting::incIndex()
{
	if(++index >= INDEX_COUNT) {
		index = 0;
	}
}

void PoseControl::PoseSetting::decIndex()
{
	if(--index < 0) {
		index = INDEX_COUNT-1;
	}
}

void PoseControl::PoseSetting::incValue()
{
	switch(index) {
		case INDEX_MOVE_X:
			trans.x += 1;
			break;
		case INDEX_MOVE_Y:
			trans.y += 1;
			break;
		case INDEX_MOVE_Z:
			trans.z += 1;
			break;
		case INDEX_SCALE_X:
			scale.x += 0.01f;
			break;
		case INDEX_SCALE_Y:
			scale.y += 0.01f;
			break;
		case INDEX_SCALE_Z:
			scale.z += 0.01f;
			break;
	}
}

void PoseControl::PoseSetting::decValue()
{
	switch(index) {
		case INDEX_MOVE_X:
			trans.x -= 1;
			break;
		case INDEX_MOVE_Y:
			trans.y -= 1;
			break;
		case INDEX_MOVE_Z:
			trans.z -= 1;
			break;
		case INDEX_SCALE_X:
			scale.x -= 0.01f;
			break;
		case INDEX_SCALE_Y:
			scale.y -= 0.01f;
			break;
		case INDEX_SCALE_Z:
			scale.z -= 0.01f;
			break;
	}
}

void PoseControl::PoseSetting::showDebugText()
{
	DebugString("PoseControl");
	DebugString("%s trans x :%.2f",	index== 0?"---":"   ", trans.x);
	DebugString("%s trans y :%.2f",	index== 1?"---":"   ", trans.y);
	DebugString("%s trans z :%.2f",	index== 2?"---":"   ", trans.z);
	DebugString("%s scale x :%.2f",	index== 3?"---":"   ", scale.x);
	DebugString("%s scale y :%.2f",	index== 4?"---":"   ", scale.y);
	DebugString("%s scale z :%.2f",	index== 5?"---":"   ", scale.z);
}



/* EOF */