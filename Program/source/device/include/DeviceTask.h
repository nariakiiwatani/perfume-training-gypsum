/*!
*/
#pragma once

#ifndef DEVICE_TASK_H
#define DEVICE_TASK_H

#include "FactorTask.h"
#include "ofTypes.h"
#include "ofxOpenNIContext.h"
#include "ofxImageGenerator.h"
#include "ofxDepthGenerator.h"
#include "ofxUserGenerator.h"


class DeviceTask : public FactorTask
{
public:
	DeviceTask();
	~DeviceTask();

	void update();

	ofxImageGenerator* getImageGenerator() { return &image_; }
	ofxDepthGenerator* getDepthGenerator() { return &depth_; }
	ofxUserGenerator* getUserGenerator() { return &user_; }
	

	ofxTrackedUser* getTrackedUser(int index);

private:
	ofxOpenNIContext	context_;
	ofxImageGenerator	image_;
	ofxDepthGenerator	depth_;
	ofxUserGenerator	user_;
};

#endif // DEVICE_TASK_H
/* EOF */