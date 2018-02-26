/* Battery.cpp : Classe da bateria do KIVA */

#include "stdafx.h"
#include "Battery.h"


Battery::Battery()
{
	chargeLevel = 100;
}

Battery::Battery(unsigned int charge)
{
	if (charge > 100)
		charge = 100;
	chargeLevel = charge;
}

Battery::~Battery()
{
}

float Battery::getChargeLevel() {
	return chargeLevel;
}

void Battery::setChargeLevel(float level) {
	if (level > 100)
		chargeLevel = 100;
	else if (level < 0)
		chargeLevel = 0;
	else
		chargeLevel = level;
}

void Battery::decChargeLevel(float dec) {
	chargeLevel -= dec;
}