/*!
*/

#include "CameraControl.h"
#include "TaskKey.h"
#include "ofCamera.h"
#include "BvhTask.h"
#include "DebugString.h"

CameraControl::CameraControl()
:Factor()
,keyboard_(NULL)
,model_(NULL)
,camera_(NULL)
,setting_()
{
}

void CameraControl::proc()
{
	if(camera_) {
#ifdef _DEBUG
		if(keyboard_) {
			procKeyboard();
		}
		setting_.showDebugText();
#endif // _DEBUG
		if(model_ && setting_.look_at_model) {
			ofVec3f m_pos = model_->getPosition();
			setting_.look_at.x = m_pos.x;
			setting_.look_at.z = m_pos.z;
		}
		ofVec3f look_at = setting_.look_at + setting_.slide;
		camera_->setScale(setting_.scale);
		camera_->lookAt(look_at);
		ofVec3f pos(0,0,-setting_.distance);
		pos.rotate(setting_.rotate.x, setting_.rotate.y, setting_.rotate.z);
		setting_.rotate.y += 0.1f;
		camera_->setPosition(pos+look_at);
		camera_->setFov(setting_.fov);
	}
}

void CameraControl::bindTask(string type, FactorTask* task)
{
	if(type == "keyboard") {
		keyboard_ = dynamic_cast<TaskKey*>(task);
	}
	else/* if(type == "model")*/ {
		model_ = dynamic_cast<BvhTask*>(task);
	}
}


void CameraControl::procKeyboard()
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
		INDEX_LOOK_AT_MODEL,
		INDEX_LOOK_AT_X,
		INDEX_LOOK_AT_Y,
		INDEX_LOOK_AT_Z,
		INDEX_DISTANCE,
		INDEX_SLIDE_X,
		INDEX_SLIDE_Y,
		INDEX_SLIDE_Z,
		INDEX_TILT,
		INDEX_PAN,
		INDEX_FOV,
		INDEX_SCALE,
		INDEX_COUNT
	};
}
CameraControl::CameraSetting::CameraSetting()
:look_at(0.0f,77.0f,0.0f)
,look_at_model(true)
,distance(100)
,slide(0,0,0)
,rotate(-12,0,0)
,scale(1)
,fov(85)
,index(0)
{
}

void CameraControl::CameraSetting::incIndex()
{
	if(++index >= INDEX_COUNT) {
		index = 0;
	}
}

void CameraControl::CameraSetting::decIndex()
{
	if(--index < 0) {
		index = INDEX_COUNT-1;
	}
}

void CameraControl::CameraSetting::incValue()
{
	switch(index) {
		case INDEX_LOOK_AT_MODEL:
			look_at_model = !look_at_model;
			break;
		case INDEX_LOOK_AT_X:
			look_at.x += 1;
			break;
		case INDEX_LOOK_AT_Y:
			look_at.y += 1;
			break;
		case INDEX_LOOK_AT_Z:
			look_at.z += 1;
			break;
		case INDEX_DISTANCE:
			distance += 5;
			break;
		case INDEX_SLIDE_X:
			slide.x += 1;
			break;
		case INDEX_SLIDE_Y:
			slide.y += 1;
			break;
		case INDEX_SLIDE_Z:
			slide.z += 1;
			break;
		case INDEX_TILT:
			rotate.x += 1.0f;
			break;
		case INDEX_PAN:
			rotate.y += 1.0f;
			break;
		case INDEX_FOV:
			fov += 1.0f;
			break;
		case INDEX_SCALE:
			scale += 0.01f;
			break;
	}
}

void CameraControl::CameraSetting::decValue()
{
	switch(index) {
		case INDEX_LOOK_AT_MODEL:
			look_at_model = !look_at_model;
			break;
		case INDEX_LOOK_AT_X:
			look_at.x -= 1;
			break;
		case INDEX_LOOK_AT_Y:
			look_at.y -= 1;
			break;
		case INDEX_LOOK_AT_Z:
			look_at.z -= 1;
			break;
		case INDEX_DISTANCE:
			distance -= 5;
			break;
		case INDEX_SLIDE_X:
			slide.x -= 1;
			break;
		case INDEX_SLIDE_Y:
			slide.y -= 1;
			break;
		case INDEX_SLIDE_Z:
			slide.z -= 1;
			break;
		case INDEX_TILT:
			rotate.x -= 1.0f;
			break;
		case INDEX_PAN:
			rotate.y -= 1.0f;
			break;
		case INDEX_FOV:
			fov -= 1.0f;
			break;
		case INDEX_SCALE:
			scale -= 0.01f;
			break;
	}
}

void CameraControl::CameraSetting::showDebugText()
{
	DebugString("%slook at model :%s",		index== 0?"---":"   ", look_at_model?"true":"false");
	DebugString("%slook at x     :%.2f",	index== 1?"---":"   ", look_at.x);
	DebugString("%slook at y     :%.2f",	index== 2?"---":"   ", look_at.y);
	DebugString("%slook at z     :%.2f",	index== 3?"---":"   ", look_at.z);
	DebugString("%sdistance      :%.2f",	index== 4?"---":"   ", distance);
	DebugString("%sslide x       :%.2f",	index== 5?"---":"   ", slide.x);
	DebugString("%sslide y       :%.2f",	index== 6?"---":"   ", slide.y);
	DebugString("%sslide z       :%.2f",	index== 7?"---":"   ", slide.z);
	DebugString("%stilt          :%.2f",	index== 8?"---":"   ", rotate.x);
	DebugString("%span           :%.2f",	index== 9?"---":"   ", rotate.y);
	DebugString("%sfov           :%.2f",	index==10?"---":"   ", fov);
	DebugString("%sscale         :%.2f",	index==11?"---":"   ", scale);
}



/* EOF */