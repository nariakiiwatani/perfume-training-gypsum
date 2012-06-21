/*!
*/

#include "ModelDraw.h"
#include "BvhTask.h"
#include "FactorManager.h"
#include "PrfmRSMDef.h"
#include "TaskPose.h"
#include "ofCamera.h"

ModelDraw::ModelDraw()
:Factor()
,source_(NULL)
,pose_(NULL)
,camera_(NULL)
{
}

void ModelDraw::proc()
{
	if(source_) {
		FactorManager::getCurrent()->addDraw(PRIO_MODEL, this);
	}
}

void ModelDraw::draw(int prio)
{
	if(camera_) {
		camera_->begin();
	}
	pose_->pushSetMatrix();
	source_->drawModel();
	pose_->popMatrix();
	if(camera_) {
		camera_->end();
	}
}

void ModelDraw::bindTask(string type, FactorTask* task)
{
	if(type == "source") {
		source_ = dynamic_cast<BvhTask*>(task);
	}
	else/* if(type == "pose")*/ {
		pose_ = dynamic_cast<TaskPose*>(task);
	}
}

/* EOF */