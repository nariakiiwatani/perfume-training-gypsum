/*!
*/

#include "TaskDraw.h"
#include "FactorManager.h"

TaskDraw::TaskDraw(string id)
:FactorTask(id)
,prio_(0)
{
}

void TaskDraw::setParam(string id, string value, string func)
{
	if(id=="prio") {
		setPrio(atoi(value.c_str()));
	}
	else {
		FactorTask::setParam(id, value, func);
	}
}

/* EOF */