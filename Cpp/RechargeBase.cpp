#include "RechargeBase.h"

bool RechargeBase::rechargeKiva(Battery& battery) 
{
	float level = battery.getChargeLevel();

	battery.setChargeLevel(level+2.5);

	return true;
}

RechargeBase::RechargeBase()
{
}


RechargeBase::~RechargeBase()
{
}