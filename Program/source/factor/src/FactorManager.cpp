/*!
*/

#include "FactorManager.h"
#include "Factor.h"
#include "FactorTask.h"
#include "TaskPose.h"

FactorManager* FactorManager::current_;

FactorManager::FactorManager()
:prev_(NULL)
,alive_(true)
{
	factor_.clear();
	task_.clear();
	update_.clear();
	proc_.clear();
	draw_.clear();
}

FactorManager::~FactorManager()
{
	alive_ = false;
	for(multimap<string, Factor*>::iterator it = factor_.begin(); it != factor_.end(); ++it) {
		delete (*it).second;
	}
	factor_.clear();
	for(multimap<string, FactorTask*>::iterator it = task_.begin(); it != task_.end(); ++it) {
		delete (*it).second;
	}
	task_.clear();
}

FactorManager* FactorManager::getCurrent()
{
	return current_;
}

void FactorManager::pushCurrent(FactorManager* man)
{
	man->prev_ = current_;
	current_ = man;
}

void FactorManager::popCurrent()
{
	current_ = current_->prev_;
}

void FactorManager::addFactor(string id, Factor* factor)
{
	/**
	if(factor_.find(id) != factor_.end()) {
		removeProc(factor_[id]);
		delete factor_[id];
	}
	/**/
	factor_.insert(pair<string, Factor*>(id, factor));
}

void FactorManager::addTask(string id, FactorTask* task)
{
	/**
	if(task_.find(id) != task_.end()) {
		removeUpdate(task_[id]);
		delete task_[id];
	}
	/**/
	task_.insert(pair<string, FactorTask*>(id, task));
}

void FactorManager::removeFactor(Factor* factor)
{
	if(!alive_) {
		return;
	}
	for(multimap<string, Factor*>::iterator it = factor_.begin(); it != factor_.end(); ++it) {
		if((*it).second == factor) {
			factor_.erase(it);
			break;
		}
	}
}

void FactorManager::removeFactor(string id)
{
	if(!alive_) {
		return;
	}
	factor_.erase(id);
}

void FactorManager::removeTask(FactorTask* task)
{
	if(!alive_) {
		return;
	}
	for(multimap<string, FactorTask*>::iterator it = task_.begin(); it != task_.end(); ++it) {
		if((*it).second == task) {
			task_.erase(it);
			break;
		}
	}
}

void FactorManager::removeTask(string id)
{
	if(!alive_) {
		return;
	}
	task_.erase(id);
}


void FactorManager::addUpdate(FactorTask* task)
{
	update_.push_back(task);
}

void FactorManager::removeUpdate(FactorTask* task)
{
	for (vector<FactorTask*>::iterator it = update_.begin(); it != update_.end(); ){
		if ( (*it) == task ) {
			it = update_.erase(it);
		}
		else {
			++it;
		}
	}
}

void FactorManager::addProc(Factor* factor)
{
	proc_.push_back(factor);
}

void FactorManager::removeProc(Factor* factor)
{
	for (vector<Factor*>::iterator it = proc_.begin(); it != proc_.end(); ){
		if ( (*it) == factor ) {
			it = proc_.erase(it);
		}
		else {
			++it;
		}
	}
}

void FactorManager::addDraw(int prio, Factor* factor)
{
	draw_.insert(pair<int, Factor*>(prio, factor));
}

void FactorManager::update()
{
	vector<FactorTask*> update(update_);
	int n = update.size();
	for(int i = 0; i < n; ++i) {
		update[i]->updateAnimation();
	}
	for(int i = 0; i < n; ++i) {
		update[i]->update();
	}
}
void FactorManager::proc()
{
	vector<Factor*> proc(proc_);
	int n = proc.size();
	for(int i = 0; i < n; ++i) {
		proc[i]->proc();
	}
}
void FactorManager::draw()
{
	for(multimap<int, Factor*, greater<int>>::iterator it=draw_.begin(); it!=draw_.end(); ++it) {
		(*it).second->draw((*it).first);
	}
	draw_.clear();
}

void FactorManager::clearUpdate()
{
	update_.clear();
}
void FactorManager::clearProc()
{
	proc_.clear();
}
void FactorManager::clearDraw()
{
	draw_.clear();
}

/* EOF */