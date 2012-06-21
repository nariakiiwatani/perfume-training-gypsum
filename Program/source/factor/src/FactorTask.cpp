/*!
*/

#include "FactorTask.h"
#include "FactorManager.h"

FactorTask::FactorTask(string id, FactorManager* man)
:man_(man)
,enable_(true)
,frame_count_(0)
,dirty_flags_(NONE)
,parent_(NULL)
,child_(NULL)
,sibling_(NULL)
{
	man_->addTask(id, this);
	man_->addUpdate(this);
}

FactorTask::~FactorTask()
{
	man_->removeTask(this);
	if(enable_) {
		man_->removeUpdate(this);
	}
	if(parent_) {
		setParent(NULL);
	}
	while(child_) {
		child_->setParent(NULL);
	}
}

void FactorTask::enable()
{
	if(!enable_) {
		enable_ = true;
		man_->addUpdate(this);
	}
}
void FactorTask::disable()
{
	if(enable_) {
		enable_ = false;
		man_->removeUpdate(this);
	}
}

void FactorTask::setParent(FactorTask* parent)
{
	if(parent == parent_) {
		return;
	}
	if(parent_) {
		FactorTask* child = parent_->child_;
		if(child == this) {
			parent_->child_ = sibling_;
		}
		else {
			while(child->sibling_ != this) {
				child = child->sibling_;
			}
			child->sibling_ = sibling_;
		}
	}
	if(parent) {
		sibling_ = parent->child_;
		parent->child_ = this;
	}
	else {
		sibling_ = NULL;
	}
	parent_ = parent;
	dirty_flags_ |= PARENT;
	if(child_) {
		child_->dirty(PARENT);
	}
}

void FactorTask::dirty(UINT flag)
{
	dirty_flags_ |= flag;
	if(child_) {
		child_->dirty(PARENT);
	}
	if(sibling_ && flag & PARENT) {
		sibling_->dirty(flag);
	}
}

void FactorTask::addAnimation(FactorTaskAnimation* animation, int start, int length, int loop_times, vector<vector<string>> assign)
{
	std::pair<AnimationSetting, FactorTaskAnimation*> pair;
	pair.first.start_frame = start;
	pair.first.length = length;
	pair.first.times = loop_times;
	pair.first.assign = assign;
	pair.second = animation;
	animations_.push_back(pair);
}

void FactorTask::addAnimation(FactorTaskAnimation* animation, string seq_id, string target, int loop_times)
{
	std::pair<AnimationSetting, FactorTaskAnimation*> pair;
	pair.first.start_frame = 0;
	pair.first.length = 0;
	pair.first.times = loop_times;
	vector<string> assign;
	assign.push_back(seq_id);
	assign.push_back(target);
	assign.push_back("set");
	pair.first.assign.push_back(assign);
	pair.second = animation;
	animations_.push_back(pair);
}

void FactorTask::updateAnimation()
{
	for(std::vector<std::pair<AnimationSetting, FactorTaskAnimation*>>::iterator it=animations_.begin(); it!=animations_.end(); ++it) {
		AnimationSetting& setting = (*it).first;
		FactorTaskAnimation* animation = (*it).second;
		if(frame_count_ < setting.start_frame || (setting.length > 0 && setting.start_frame+setting.length < frame_count_)) {
			continue;
		}
		if(setting.times > 0 && (frame_count_-setting.start_frame)/animation->getLength() >= setting.times) {
			continue;
		}
		for(vector<vector<string>>::iterator ss=setting.assign.begin(); ss!=setting.assign.end(); ++ss) {
			procAnimation(animation, (*ss)[0], (frame_count_-setting.start_frame)%animation->getLength(), (*ss)[1], (*ss)[2]);
		}
	}
	++frame_count_;
}

void FactorTask::setParam(string id, string value, string func)
{
}

void FactorTask::procAnimation(FactorTaskAnimation* animation, string seq_id, int frame, string target, string func)
{
}


/* EOF */