#include "InfraRedSensor.h"

InfraRedSensor::InfraRedSensor()
{
}

InfraRedSensor::~InfraRedSensor()
{
}

unsigned int InfraRedSensor::getDistance() {

	/* A distancia e' inicializada para um valor arbitrariamente alto,
	** significando a ausencia de objetos proximos 'a frente do robo
	*/
	unsigned int distance = 999999;
	
	/* detalhes de implementacao incluem:
	** - obtencao de um conjunto n de medicoes do sensor
	** - tratamento estatistico das medicoes (descartar outliers)
	*/
	return distance;
}