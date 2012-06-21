/*!
*/
#pragma once

#include <vector>

class Factor;
class FactorDraw;
#include "FactorTaskAnimation.h"
#include "FactorManager.h"

class FactorTask
{
public:
	FactorTask(string id="", FactorManager* man=FactorManager::getCurrent());
	virtual ~FactorTask();
	void enable();
	void disable();
	bool isEnable() { return enable_; }
	void updateAnimation();
	virtual void update(){}
	virtual void setParent(FactorTask* parent);
	virtual void setParam(string id, string value, string func);
	void addAnimation(FactorTaskAnimation* animation, int start, int length, int loop_times, vector<vector<string>> assign);
	void addAnimation(FactorTaskAnimation* animation, string seq_id, string target, int loop_times);
	virtual void procAnimation(FactorTaskAnimation* animation, string seq_id, int frame, string target, string func);
	FactorManager* getManager() { return man_; }

protected:
	enum {
		NONE	= 0x0000,
		LOCAL	= 0x0001,
		PARENT	= 0x0002,
	};
	void dirty(UINT flag);
	bool isDirty(UINT chk) const{return (dirty_flags_&chk)!=0;}
	void clsDirtyFlag(UINT flag){dirty_flags_&=~flag;}
	FactorTask* getParent(){return parent_;}
	FactorTask* getChild(){return child_;}
	FactorTask* getSibling(){return sibling_;}

protected:
	vector<string> split(const string &str, char delim){
	  istringstream iss(str); string tmp; vector<string> res;
	  while(getline(iss, tmp, delim)) res.push_back(tmp);
	  return res;
	}


private:
	FactorTask* parent_;
	FactorTask* child_;
	FactorTask* sibling_;
	UINT dirty_flags_;
	FactorManager* man_;
	bool enable_;
	
	struct AnimationSetting {
		int start_frame;
		int length;
		int times;
		vector<vector<string>> assign;
	};
	int frame_count_;
	vector<pair<AnimationSetting, FactorTaskAnimation*>> animations_;
};

/* EOF */