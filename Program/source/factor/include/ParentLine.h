/*!
*/
#pragma once

class FactorTask;
class TaskPose;
#include "Factor.h"

class ParentLine : public Factor
{
public:
	ParentLine(string id="");
	void proc();
	void draw();
	void bindTask(string bind_type, FactorTask* task);
private:
	TaskPose* pose_;
};
/* EOF */