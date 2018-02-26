/* Environment.cpp : classe do Ambiente */
#include "Host.h"

Host::Host()
{
	trajectoryPtr = createTrajectory();
}

//Cria a lista circular de localizacoes
Trajectory* Host::createTrajectory() 
{
	vector<Location>* v = new vector<Location>();
	ifstream file;

	int posX, posY;
	file.open("trajectory.txt");

	if (file.is_open()){
		while (file >> posX){
			file >> posY;
			Location currentLocation(posX, posY);
			(*v).push_back(currentLocation);
		}
		file.close();
	}

	Trajectory* tPtr = new Trajectory(v);

	return tPtr;
}


Host::~Host()
{
	delete trajectoryPtr;	// Desalocacao da trajetoria
}

bool Host::includeKiva(Kiva* kPtr) {
	availableKivas.push_back(kPtr);
	kPtr->setTrajectory(trajectoryPtr);

	return true;
}

void Host::startMissionsRoutine() {
	ifstream file;

	int id, startX, startY, startDir, finalX, finalY, finalDir;
	file.open("missions.txt");

	if (file.is_open()){

		string line;
		getline(file, line);

		while (file >> id){
			file >> startX >> startY >> startDir >> finalX >>finalY >> finalDir;

			Mission m(id, Location(startX, startY), startDir, Location(finalX, finalY), finalDir);
			availableKivas[0]->missions.addMission(m);
		}
		file.close();
	}

	for (vector<Kiva*>::iterator it = availableKivas.begin(); it != availableKivas.end(); ++it) {
		(*(*it)).completeMissions();
	}

}

void Host::printTrajectory() {

	cout << "Host::printTrajectory\n";
	trajectoryPtr->printTrajectory();
}