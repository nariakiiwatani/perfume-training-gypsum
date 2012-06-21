/*!
*/
#pragma once

class BvhTask;
class TaskPose;
class ofCamera;
#include "Factor.h"
#include "ofTypes.h"


class ModelDraw : public Factor
{
public:
	ModelDraw();
	void draw(int prio);
	void proc();
	void bindTask(string bind_type, FactorTask* task);
	void setCamera(ofCamera* camera) { camera_ = camera; }
private:
	BvhTask* source_;
	TaskPose* pose_;
	ofCamera* camera_;
};

/* EOF */