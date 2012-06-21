/*!
*/

#include "VideoDraw.h"
#include "DeviceTask.h"
#include "FactorManager.h"
#include "PrfmRSMDef.h"
#include "BvhTask.h"


VideoDraw::VideoDraw()
:Factor()
,source_(NULL)
{
}

void VideoDraw::proc()
{
	if(source_) {
		getManager()->addDraw(PRIO_VIDEO, this);
	}
}

void VideoDraw::draw(int prio)
{
	ofSetColor(255, 255, 255);
	ofSetRectMode(OF_RECTMODE_CORNER);
	source_->getImageGenerator()->draw(0, 0, 320, 240);
}

void VideoDraw::bindTask(string bind_type, FactorTask* task)
{
	source_ = dynamic_cast<DeviceTask*>(task);
}

/* EOF */