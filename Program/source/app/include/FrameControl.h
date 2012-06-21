/*!
*/
#pragma once

class TaskKey;
class BvhTask;
#include "Factor.h"
#include "ofTypes.h"


class FrameControl : public Factor
{
public:
	FrameControl();
	void proc();
	void bindTask(string bind_type, FactorTask* task);

private:
	BvhTask* model_;
	TaskKey* keyboard_;
};

/* EOF */