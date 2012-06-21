/*!
*/
#pragma once

class FactorTask;
#include "FactorManager.h"
#include "ofTypes.h"


class Factor
{
public:
	Factor(string id="", FactorManager* man=FactorManager::getCurrent());
	virtual ~Factor();
	void enable();
	void disable();
	bool isEnable() { return enable_; }
	virtual void proc(){};
	virtual void draw(int prio){};
	virtual void bindTask(string bind_type, FactorTask* task){};
	FactorManager* getManager() { return man_; }
private:
	FactorManager* man_;
	bool enable_;
};
/* EOF */