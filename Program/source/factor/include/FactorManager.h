/*!
*/
#pragma once

#include <vector>
#include <map>
#include "Poco/HashMap.h"
#include "ofTypes.h"

class Factor;
class FactorTask;
class TaskDraw;

class FactorManager
{
public:
	static FactorManager* getCurrent();
	static void pushCurrent(FactorManager* man);
	static void popCurrent();

private:
	static FactorManager* current_;
	FactorManager* prev_;

public:
	FactorManager();
	~FactorManager();
	void addFactor(string id, Factor* factor);
	void addTask(string id, FactorTask* task);
	Factor* getFactor(string id){return (*factor_.find(id)).second;}
	FactorTask* getTask(string id){return (*task_.find(id)).second;}
	void removeFactor(Factor* factor);
	void removeTask(FactorTask* task);
	void removeFactor(string id);
	void removeTask(string id);

	
	void addUpdate(FactorTask* task);
	void removeUpdate(FactorTask* task);
	void addProc(Factor* factor);
	void removeProc(Factor* factor);
	void addDraw(int prio, Factor* factor);
	void update();
	void proc();
	void draw();
	void clearUpdate();
	void clearProc();
	void clearDraw();

private:
	multimap<string, Factor*> factor_;
	multimap<string, FactorTask*> task_;
	vector<FactorTask*> update_;
	vector<Factor*>	proc_;
	multimap<int, Factor*, std::greater<int>> draw_;
	bool alive_;
};

/* EOF */