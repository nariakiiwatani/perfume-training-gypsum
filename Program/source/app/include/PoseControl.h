/*!
*/
#pragma once

class TaskKey;
class TaskPose;
class BvhTask;
class DeviceTask;
#include "Factor.h"
#include "ofTypes.h"


class PoseControl : public Factor
{
public:
	PoseControl();
	void proc();
	void bindTask(string bind_type, FactorTask* task);

private:
	void procKeyboard();
	void showDebugText();

private:
	TaskPose* target_;
	BvhTask* model_;
	DeviceTask* source_;
	TaskKey* keyboard_;
	struct PoseSetting {
		PoseSetting();
		void incIndex();
		void decIndex();
		void incValue();
		void decValue();
		void showDebugText();
		int index;
		ofVec3f trans;
		ofVec3f scale;
	} setting_;
};

/* EOF */