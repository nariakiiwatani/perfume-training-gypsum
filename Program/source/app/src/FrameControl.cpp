/*!
*/

#include "FrameControl.h"
#include "TaskKey.h"
#include "BvhTask.h"
#include "DebugString.h"

FrameControl::FrameControl()
:Factor()
,keyboard_(NULL)
,model_(NULL)
{
}

void FrameControl::proc()
{
	if(model_) {
		if(keyboard_) {
			unsigned int trigger = keyboard_->getTrigger();
			unsigned int repeat = keyboard_->getRepeat();
			unsigned int hold = keyboard_->getHold();
			unsigned int key = trigger|repeat;
			if(key & KEY_LEFT) {
				model_->decFrame(1);
			}
			if(key & KEY_RIGHT) {
				model_->incFrame(1);
			}
			if(key & KEY_DOWN) {
				model_->decFrame(50);
			}
			if(key & KEY_UP) {
				model_->incFrame(50);
			}
			if(key & KEY_SPACE) {
				model_->randomFrame();
			}
		}
	}
}

void FrameControl::bindTask(string type, FactorTask* task)
{
	if(type == "keyboard") {
		keyboard_ = dynamic_cast<TaskKey*>(task);
	}
	else/* if(type == "model")*/ {
		model_ = dynamic_cast<BvhTask*>(task);
	}
}

/* EOF */