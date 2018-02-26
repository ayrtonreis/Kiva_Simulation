#ifndef HOST_H
#define HOST_H

#include "Trajectory.h"
#include "Location.h"
#include "Kiva.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Host
{
private:
	Trajectory* trajectoryPtr;
	Trajectory* createTrajectory();
	vector<Kiva*> availableKivas;

public:
	Host();
	~Host();
	bool includeKiva(Kiva* k);
	void startMissionsRoutine();
	void printTrajectory();
};

#endif // HOST_H