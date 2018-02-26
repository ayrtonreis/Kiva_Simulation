/* Motor.h : classe abstrata. Classe pai dos outros motores */


#include "Motor.h"

Motor::Motor()
{
	PWM = 0;
	RPM = 0;
	isReversed = false;
}

Motor::~Motor()
{
}