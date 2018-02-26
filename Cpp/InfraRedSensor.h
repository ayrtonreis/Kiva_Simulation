/*InfraRedSensor.h : classe do sensor de distancia infravermelho */

#ifndef INFRA_RED_SENSOR_H
#define INFRA_RED_SENSOR_H

class InfraRedSensor
{
public:
	InfraRedSensor();
	~InfraRedSensor();
	unsigned int getDistance();
};

#endif // INFRA_RED_SENSOR_H