/*!
*/

#include "ParentLine.h"
#include "FactorManager.h"
#include "TaskPose.h"
#include "ofGraphics.h"

ParentLine::ParentLine(string id)
:Factor(id)
,pose_(NULL)
{
}

void ParentLine::proc()
{
	FactorManager::getCurrent()->addDraw(0, this);
}
void ParentLine::draw()
{
	ofPushMatrix();
	ofTranslate(400,300);
	ofScale(1,-1,1);
	if(pose_) {
		if(TaskPose* parent = pose_->getParent()) {
			parent->pushSetMatrix();
			const ofMatrix4x4* mat = pose_->getLocalMatrix();
			ofLine(ofPoint(0,0,0), mat->getTranslation());
			parent->popMatrix();
		}
	}
	ofPopMatrix();
}
void ParentLine::bindTask(string bind_type, FactorTask* task)
{
	if(bind_type == "pose") {
		pose_ = dynamic_cast<TaskPose*>(task);
	}
}

/* EOF */