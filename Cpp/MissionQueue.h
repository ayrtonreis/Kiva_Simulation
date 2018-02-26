#ifndef MISSION_QUEUE_H
#define MISSION_QUEUE_H

#include "Mission.h"
#include<list>

using namespace std;

class MissionQueue
{
private:
	list<Mission> list;

public:
	MissionQueue();
	~MissionQueue();
	unsigned int size();
	void addMission(Mission m);
	void addMissionFront(Mission m);
	Mission popFront();
	bool removeMissionFromId(unsigned int id);
	void printQueue();

};

#endif // MISSION_QUEUE_H