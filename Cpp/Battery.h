/* Battery.h : Classe da bateria do KIVA */

#ifndef BATTERY_H
#define BATTERY_H

class Battery
{
private:
	float chargeLevel; //0-100

public:
	Battery();
	Battery(unsigned int charge);
	~Battery();
	//getter
	float getChargeLevel();
	//setter
	void setChargeLevel(float level);
	//decrementa de "dec" o nivel da bateria 
	void decChargeLevel(float dec);
};

#endif // BATTERY_H