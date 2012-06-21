/*!
*/
#pragma once

class DeviceTask;
class ofCamera;
class TaskPose;
class CustomJoint;
#include "Factor.h"
#include "ofTypes.h"


class SkeletonDraw : public Factor
{
public:
	SkeletonDraw();
	void draw(int prio);
	void proc();
	void bindTask(string bind_type, FactorTask* task);
private:
	DeviceTask* source_;
};


class SkeletonDrawTransformed : public Factor
{
public:
	SkeletonDrawTransformed();
	void draw(int prio);
	void proc();
	void bindTask(string bind_type, FactorTask* task);
	void setCamera(ofCamera* camera);
private:
	CustomJoint* source_;
//	DeviceTask* source_;
	ofCamera* camera_;
	TaskPose* transform_;
};

/* EOF */