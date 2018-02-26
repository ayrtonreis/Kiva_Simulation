/* MotorScrew.cpp: classe do motor da rosca que levanta ou abaixa a carga */

#ifndef MOTOR_SCREW_H
#define MOTOR_SCREW_H

#include "Motor.h"

class MotorScrew : public Motor
{
public:
	MotorScrew();
	~MotorScrew();
	bool rotate(int angle);
};

#endif // !MOTOR_SCREW_H