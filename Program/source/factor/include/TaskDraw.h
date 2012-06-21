/*!
*/
#pragma once

#include "FactorTask.h"

class TaskDraw : public FactorTask
{
public:
	TaskDraw(string id="");
	virtual void draw()=0;
	virtual void setParam(string id, string value, string func);
	int getPrio(){return prio_;}
	void setPrio(int prio){prio_=prio;}
private:
	int prio_;
};

/* EOF */