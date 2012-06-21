/*!
*/
#pragma once

class ofCamera;
class TaskKey;
class BvhTask;
#include "Factor.h"
#include "ofTypes.h"


class CameraControl : public Factor
{
public:
	CameraControl();
	void proc();
	void bindTask(string bind_type, FactorTask* task);
	void setCamera(ofCamera* camera) { camera_ = camera; }

private:
	void procKeyboard();

private:
	BvhTask* model_;
	TaskKey* keyboard_;
	ofCamera* camera_;

	struct CameraSetting {
		ofVec3f	look_at;
		bool	look_at_model;
		float	distance;
		ofVec3f	slide;
		ofVec3f	rotate;
		float	scale;
		float	fov;
		int index;
		CameraSetting();
		void incIndex();
		void decIndex();
		void incValue();
		void decValue();
		void showDebugText();
	} setting_;
};

/* EOF */