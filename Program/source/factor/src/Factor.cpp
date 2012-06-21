/*!
*/

#include "Factor.h"
#include "TaskPose.h"

Factor::Factor(string id, FactorManager* man)
:man_(man)
,enable_(true)
{
	man_->addFactor(id, this);
	man_->addProc(this);
}

Factor::~Factor()
{
	man_->removeFactor(this);
	if(enable_) {
		man_->removeProc(this);
	}
}

void Factor::enable()
{
	if(!enable_) {
		enable_ = true;
		man_->addProc(this);
	}
}

void Factor::disable()
{
	if(enable_) {
		enable_ = false;
		man_->removeProc(this);
	}
}


/* EOF */