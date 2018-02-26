/* Trajectory.h : implementa uma lista circular com as localizacoes da trajetoria do Kiva */

#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include <vector>
#include <iostream>
#include "Location.h"

using namespace std;

class Trajectory
{
private:
	//ponteiro para vetor de localizacoes, que e' usado na implementacao
	//da lista circular
	vector<Location>* vecPtr;
public:
	const Location rechargeBaseLocation;
	const unsigned int rechargeBaseDirection;
	Trajectory(vector<Location>* vPtr);
	~Trajectory();
	bool chooseDirection(const Location& l1, const Location& l2);
	unsigned int findCurrentIndexPos(const Location& l);
	Location& getNext(bool direction, unsigned int currentIndexPos);
	unsigned int incrementIndexPos(bool direction, unsigned int currentIndexPos);
	void printTrajectory();
};

#endif // TRAJECTORY_H