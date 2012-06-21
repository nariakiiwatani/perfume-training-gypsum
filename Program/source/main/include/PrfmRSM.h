/*!
*/
#pragma once

#include "ofBaseApp.h"
#include "FactorManager.h"
#include "AppManager.h"

class PrfmRSM : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	void exit();
private:
	FactorManager factor_man_;
	AppManager app_man_;
};

/* EOF */