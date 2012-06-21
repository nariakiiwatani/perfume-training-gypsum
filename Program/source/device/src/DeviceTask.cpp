/*!
*/

#include "DeviceTask.h"
#include "PrfmRSMDef.h"
#include "ofxTrackedUser.h"

DeviceTask::DeviceTask()
:FactorTask()
{
	context_.setup();	// all nodes created by code -> NOT using the xml config file at all
//	recordHandTracker.setSmoothing(0.1f);		// built in openni hand track smoothing...
//	recordHandTracker.setFilterFactors(0.1f);	// custom smoothing/filtering (can also set per hand with setFilterFactor)...set them all to 0.1f to begin with

//	recordContext.toggleRegisterViewport();
//	context_.toggleMirror();
	image_.setup(&context_);
	depth_.setup(&context_);
	depth_.setDepthColoring(COLORING_GREY);
	user_.setup(&context_);
	user_.setMaxNumberOfUsers(1);
}

DeviceTask::~DeviceTask()
{
}

void DeviceTask::update()
{
	context_.update();
	image_.update();
	depth_.update();
	user_.update();
/**
	for(int i = 0, max = user_.getNumberOfTrackedUsers(); i < max; ++i) {
		ofxTrackedUser* usr = user_.getTrackedUser(i+1);
		ofLog(OF_LOG_NOTICE, "ID:%d", i);
		ofLog(OF_LOG_NOTICE, "hip:%.2f,%.2f,%.2f",usr->hip.position[0].X,usr->hip.position[0].Y,usr->hip.position[0].Z);
		ofLog(OF_LOG_NOTICE, "neck:%.2f,%.2f,%.2f",usr->neck.position[0].X,usr->neck.position[0].Y,usr->neck.position[0].Z);
	}
/**/
}

ofxTrackedUser* DeviceTask::getTrackedUser(int index)
{
	if(user_.getNumberOfTrackedUsers() > index) {
		return user_.getTrackedUser(index+1);
	}
	return NULL;
}


/* EOF */