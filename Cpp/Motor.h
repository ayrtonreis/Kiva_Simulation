/* Motor.cpp : classe abstrata. Classe pai dos outros motores */

#ifndef MOTOR_H
#define MOTOR_H

class Motor
{
protected:
	unsigned int PWM;
	int RPM;
	bool isReversed;

public:
	Motor();
	~Motor();
	virtual bool rotate(int angle) = 0;
};

#endif // MOTOR_H