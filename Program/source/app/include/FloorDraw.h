/*!
*/
#pragma once

class ofCamera;
#include "Factor.h"
#include "ofTypes.h"


class FloorDraw : public Factor
{
public:
	FloorDraw();
	void draw(int prio);
	void proc();
	void bindTask(string bind_type, FactorTask* task){}
	void setCamera(ofCamera* camera) { camera_ = camera; }
private:
	ofCamera* camera_;
};

/* EOF */