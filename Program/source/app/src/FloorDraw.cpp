/*!
*/

#include "FloorDraw.h"
#include "FactorManager.h"
#include "PrfmRSMDef.h"
#include "ofCamera.h"

FloorDraw::FloorDraw()
:Factor()
,camera_(NULL)
{
}

void FloorDraw::proc()
{
	FactorManager::getCurrent()->addDraw(PRIO_FLOOR, this);
}

void FloorDraw::draw(int prio)
{
	if(camera_) {
		camera_->begin();
	}
	int interval = 50;
	int min_x = -200;
	int max_x = 150;
	int min_z = -350;
	int max_z = 200;
	for(int x = min_x; x <= max_x; x += interval) {
		ofLine(x, 0, min_z, x, 0, max_z);
	}
	for(int z = min_z; z <= max_z; z += interval) {
		ofLine(min_x, 0, z, max_x, 0, z);
	}
	if(camera_) {
		camera_->end();
	}
}


/* EOF */