/* MotorWheel.cpp: classe do motor das rodas */

#ifndef MOTOR_WHEEL_H
#define MOTOR_WHEEL_H

#include "Motor.h"

class MotorWheel : public Motor
{
public:
	MotorWheel();
	~MotorWheel();
	bool rotate(int angle);
};

#endif // !MOTOR_WHEEL_H