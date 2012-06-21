/*!
*/

#include "PrfmRSM.h"


void PrfmRSM::setup()
{
	FactorManager::pushCurrent(&factor_man_);
	app_man_.init();
}

void PrfmRSM::update()
{
	FactorManager::getCurrent()->update();
	FactorManager::getCurrent()->proc();
}

void PrfmRSM::draw()
{
	FactorManager::getCurrent()->draw();
}

void PrfmRSM::exit()
{
	app_man_.exit();
	FactorManager::popCurrent();
}

/* EOF */