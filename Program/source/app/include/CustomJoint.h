/*!
*/
#pragma once

class DeviceTask;
#include "FactorTask.h"
#include "ofTypes.h"

class CustomJoint : public FactorTask
{
public:
	CustomJoint();
	void update();
	void setSource(DeviceTask* source) { source_ = source; }
	bool isValid() { return valid_; }
	const ofVec2f& getHipPos2D() { return hip_2d_; }

public:
	ofVec3f hips_;
	ofVec3f neck_;
	ofVec3f head_;
	ofVec3f l_sh_;
	ofVec3f l_el_;
	ofVec3f l_wr_;
	ofVec3f l_hi_;
	ofVec3f l_kn_;
	ofVec3f l_an_;
	ofVec3f r_sh_;
	ofVec3f r_el_;
	ofVec3f r_wr_;
	ofVec3f r_hi_;
	ofVec3f r_kn_;
	ofVec3f r_an_;

	ofVec2f hip_2d_;

private:
	bool valid_;
	DeviceTask* source_;
};

/* EOF */