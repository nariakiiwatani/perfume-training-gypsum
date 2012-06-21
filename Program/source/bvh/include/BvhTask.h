/*!
*/
#pragma once

#include "FactorTask.h"
#include "ofTypes.h"
#include "ofxBvh.h"


class BvhTask : public FactorTask
{
public:
	BvhTask(string file);
	~BvhTask();

	void incFrame(int frame=1);
	void decFrame(int frame=1);
	void randomFrame();
	void setFrame(int frame);
	int getFrame();
	int getNumFrames();
	float getTall();

	void update();
	void drawModel();
	ofVec3f getPosition();

	ofxBvh* getModel() { return &model_; }

private:
	ofxBvh model_;
};

/* EOF */