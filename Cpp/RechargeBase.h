#ifndef RECHARGE_BASE_H
#define RECHARGE_BASE_H

#include "Location.h"
#include "Battery.h"

class RechargeBase
{
public:
	bool rechargeKiva(Battery& battery);
	RechargeBase();
	~RechargeBase();
};

#endif // !RECHARGE_BASE_H