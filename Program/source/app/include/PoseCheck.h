/*!
*/
#pragma once

class BvhTask;
class CustomJoint;
class DeviceTask;
class TaskKey;
#include "Factor.h"
#include "ofTypes.h"
#include "ofPixels.h"


class PoseCheck : public Factor
{
public:
	PoseCheck();
	~PoseCheck();
	void proc();
	void draw(int prio);
	void bindTask(string bind_type, FactorTask* task);
	void setFolder(string folder);
private:
	float getMatchRate();
	float getMatchRateInverse();
private:
	BvhTask* model_;
	CustomJoint* source_;
	DeviceTask* device_;
	TaskKey* keyboard_;
	
	ofPixels image_capture_;
	ofPixels image_divide_capture_;
	ofShortPixels depth_capture_;

	static const int OK_COUNT_MAX = 60;
	string save_folder_;
	int ok_count_;
	float ok_rate_;
	float ok_rate2_;
	float bad_rate_;
	float match_rate_;

	char fmt_str_[8];
};

/* EOF */