/*Kiva.h : classe do robo movel */

#ifndef KIVA_H
#define KIVA_H

#include "Trajectory.h"
#include "Camera.h"
#include "Location.h"
#include "Environment.h"
#include "InfraredSensor.h"
#include "MotorWheel.h"
#include "MotorScrew.h"
#include "Battery.h"
#include "MissionQueue.h"
#include "Mission.h"

#include <ctime>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;

class Kiva
{
	// distancia maxima da frente do kiva a um objeto desconhecido,
	// antes de executar uma frenagem de emergencia
	static const unsigned int DISTANCE_THRESHOLD = 10;
private:
	Environment* environmentPtr;
	Trajectory* trajectoryPtr;
	Location currentLocation;
	unsigned int currentIndexPos;
	unsigned int currentDir;
	Mission* currentMissionPtr;
	Camera bottomCam, topCam;
	MotorWheel motorRight, motorLeft;
	MotorScrew motorTop;
	InfraRedSensor IRSensor;
	Battery battery;
	bool isLoaded;


	bool updateCurrentLocation();
	bool liftLoad();
	bool unliftLoad();
	bool rotate(int angle);
	bool goTo(const Location& destination);
	bool accelerate();
	bool decelerate();
	bool accelerateThenDecelerate();
	bool maneuverIn(unsigned int direction);
	bool maneuverOut(unsigned int direction);


public:
	MissionQueue missions;
	const unsigned int id;
	Kiva(unsigned int id_number, Environment* envPtr);
	~Kiva();
	void completeMissions();
	bool executeMission(Mission& mission);
	bool executeRecharge();
	void setTrajectory(Trajectory* tPtr);
	void printTrajectory();
	void printMissions();
	void printCurrentState();
	void wait(unsigned int milliseconds);
	void updateDataToSimulator(); 
};



#endif // KIVA_H