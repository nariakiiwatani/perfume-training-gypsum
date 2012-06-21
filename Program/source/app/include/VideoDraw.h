/*!
*/
#pragma once

class DeviceTask;
#include "Factor.h"
#include "ofTypes.h"


class VideoDraw : public Factor
{
public:
	VideoDraw();
	void draw(int prio);
	void proc();
	void bindTask(string bind_type, FactorTask* task);
private:
	DeviceTask* source_;
};

/* EOF */