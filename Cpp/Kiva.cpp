/*InfraRedSensor.cpp : classe do sensor de distancia infravermelho */

#include "Kiva.h"

Kiva::Kiva(unsigned int id_number, Environment* envPtr): id(id_number), environmentPtr(envPtr)
{
	trajectoryPtr = NULL;
	currentMissionPtr = NULL;
	isLoaded = false;
	updateCurrentLocation();
}

Kiva::~Kiva()
{
}

bool Kiva::updateCurrentLocation()
{
	//A posicao e direcao iniciais sao obtidos pela camera
	vector<unsigned int> vec = bottomCam.getQR();

	//vec[0] diz se o QR Code e' do chao (bottom) ou da estante (top)
	currentDir = vec[1];
	currentLocation = Location(vec[2],vec[3]);

	return true;
}

bool Kiva::liftLoad() {
	for (int i = 0; i < 5; i++) {
		rotate(90);
		wait(300);
	}
	isLoaded = true;

	return true;
}

bool Kiva::unliftLoad() {
	for (int i = 0; i < 5; i++) {
		rotate(-90);
		wait(300);
	}
	isLoaded = false;
		
	return true;
}

bool Kiva::accelerate() {
	//detalhes de implementacao de hardware

	return true;
}

bool Kiva::decelerate() {
	//detalhes de implementacao de hardware

	return true;
}

bool Kiva::accelerateThenDecelerate() {
	//detalhes de implementacao de hardware

	return true;
}

// Manobra de entrada em uma posicao adjacente 'a trajetoria
bool Kiva::maneuverIn(unsigned int direction) {

	switch (currentDir)
	{
	case 1:
		switch (direction)
		{
		case 2:
			rotate(90);
			break;
		case 3:
			rotate(180);
			break;
		case 4:
			rotate(-90);
			break;
		default:
			break;
		}

		break;
	case 2:
		switch (direction)
		{
		case 1:
			rotate(-90);
			break;
		case 3:
			rotate(90);
			break;
		case 4:
			rotate(180);
			break;
		default:
			break;
		}

		break;
	case 3:
		switch (direction)
		{
		case 1:
			rotate(180);
			break;
		case 2:
			rotate(-90);
			break;
		case 4:
			rotate(90);
			break;
		default:
			break;
		}

		break;
	case 4:
		switch (direction)
		{
		case 1:
			rotate(90);
			break;
		case 2:
			rotate(180);
			break;
		case 3:
			rotate(-90);
			break;
		default:
			break;
		}

		break;
	}

	

	Location loc;

	switch (direction)
	{
	case 1:
		loc = Location(currentLocation.x, currentLocation.y - 4);
		break;
	case 2:
		loc = Location(currentLocation.x + 4, currentLocation.y);
		break;
	case 3:
		loc = Location(currentLocation.x, currentLocation.y + 4);
		break;
	case 4:
		loc = Location(currentLocation.x - 4, currentLocation.y);
		break;
	default:
		loc = Location(currentLocation);
		break;
	}

	currentLocation = loc;
	updateDataToSimulator();

	return true;
}

// Manobra de saida em uma posicao adjacente 'a trajetoria
bool Kiva::maneuverOut(unsigned int direction) {
	switch (direction)
	{
	case 1:
		maneuverIn(3);
		break;
	case 2:
		maneuverIn(4);
		break;
	case 3:
		maneuverIn(1);
		break;
	case 4:
		maneuverIn(2);
		break;
	default:
		break;
	}
	return true;
}

/*Rotaciona o robo em angulos: +-90 e +- 180*/
bool Kiva::rotate(int angle)
{
	int times = angle / 90;
	currentDir += times;


	if (angle > 0 && currentDir > 4){
		currentDir %= 4;
	}
	else if (angle < 0 && currentDir <= 0) {
		currentDir = 4 - currentDir;
	}

	battery.decChargeLevel(0.34);
	updateDataToSimulator();
	wait(100);
	return true;
}

bool Kiva::goTo(const Location& destination)
{
	currentIndexPos = trajectoryPtr->findCurrentIndexPos(currentLocation);
	cout << "\n\nCURRENT POSINDEX: " << currentIndexPos << "\t"<< currentLocation << endl;

	bool isClockwise = trajectoryPtr->chooseDirection(currentLocation, destination);
	cout << "IS CLOCKWISE?" << isClockwise << endl << endl;

	Location nextLoc_1 = trajectoryPtr->getNext(isClockwise, currentIndexPos);
	Location nextLoc_2;

	if (nextLoc_1 == destination) {
		accelerateThenDecelerate();
		currentLocation = destination;
		currentIndexPos = trajectoryPtr->incrementIndexPos(isClockwise, currentIndexPos);
	}

	while (currentLocation != destination) {
		int dx_1 = nextLoc_1.x - currentLocation.x;
		int dy_1 = nextLoc_1.y - currentLocation.y;

		// O robo precisara' fazer uma mudanca de direcao logo a seguir
		if (dx_1) {
			decelerate();
			if (dx_1 > 0 && currentDir != 2) {

				switch (currentDir){
				case 1:
					rotate(90);
					break;
				case 3:
					rotate(-90);
					break;
				default:
					rotate(180);
					break;
				}
			}

			else if (dx_1 < 0 && currentDir != 4) {

				switch (currentDir){
				case 1:
					rotate(-90);
					break;
				case 2:
					rotate(-180);
					break;
				default:
					rotate(90);
					break;
				}
			}
			updateDataToSimulator();
			
		}
		else {
			if (dy_1 > 0 && currentDir != 3) {

				switch (currentDir)
				{
				case 1:
					rotate(180);
					break;
				case 2:
					rotate(90);
					break;
				default:
					rotate(-90);
					break;
				}
			}

			else if (dy_1 < 0 && currentDir != 1) {

				switch (currentDir)
				{
				case 2:
					rotate(-90);
					break;
				case 3:
					rotate(-180);
					break;
				default:
					rotate(90);
					break;
				}
			}
			updateDataToSimulator();
			
		}
		if (nextLoc_1 == destination) {
			decelerate();
			currentLocation = destination;
			currentIndexPos = trajectoryPtr->incrementIndexPos(isClockwise, currentIndexPos);
		}
		else {
			unsigned int nextIndex = trajectoryPtr->incrementIndexPos(isClockwise, currentIndexPos);
			nextLoc_2 = trajectoryPtr->getNext(isClockwise, nextIndex);

			
			
			currentLocation = nextLoc_1;
			currentIndexPos = trajectoryPtr->incrementIndexPos(isClockwise, currentIndexPos);
			nextLoc_1 = nextLoc_2;
			
		}
		battery.decChargeLevel(0.28);
		cout << currentDir << "~" << currentLocation << "\t";
		updateDataToSimulator();
	}
	
	cout << "----- END GOTO ----- " << endl << endl;
	return true;
}

void Kiva::completeMissions() 
{
	updateCurrentLocation();
	wait(1000);
	cout << "Kiva started working on Missions" <<endl;
	printMissions();
	
	while (missions.size()) {
		if (battery.getChargeLevel() >= 30) {
			Mission currentMission = missions.popFront();
			currentMissionPtr = &currentMission;
			cout << "Current Mission >> ";
			currentMission.printMission();
			executeMission(currentMission);
			currentMissionPtr = NULL;
			cout << "---------------- Mission Completed ----------------" <<endl<<endl;
			wait(1600);
		}
		else {
			cout << "WARNING: BATTERY LOW" << endl << endl;
			executeRecharge();
		}
		printCurrentState();
	}
	missions.printQueue();
	currentMissionPtr = NULL;
	updateDataToSimulator();

	cout << "Kiva finished working on Missions" << endl;

	if (battery.getChargeLevel() < 30) {
		cout << "WARNING: BATTERY LOW" << endl << endl;
		executeRecharge();
	}

	cout << "\nSTAND BY\n\n";
}

bool Kiva::executeMission(Mission& mission) {

	cout << currentLocation <<"~" <<currentDir << " ------> " << mission.getOrigin() << "~" << mission.getOriginDir();
	if (currentLocation != mission.getOrigin()) {
		cout << " - DIFERENT\n\n";
		goTo(mission.getOrigin());
	}
	maneuverIn(mission.getOriginDir());
	liftLoad();
	maneuverOut(mission.getOriginDir());

	cout << currentLocation << "~" << currentDir << " ------> " << mission.getDestination() << "~" << mission.getDestinationDir();
	if (mission.getOrigin ()!= mission.getDestination()) {
		cout << " - DIFERENT\n\n";
		goTo(mission.getDestination());
	}
	maneuverIn(mission.getDestinationDir());
	unliftLoad();
	maneuverOut(mission.getDestinationDir());

	return true;
}

bool Kiva::executeRecharge() {
	const Location& rechargeLocation = trajectoryPtr->rechargeBaseLocation;
	const int& rechargeDir = trajectoryPtr->rechargeBaseDirection;

	goTo(rechargeLocation);

	unsigned int oldDir = currentDir;

	maneuverIn(rechargeDir);

	while (battery.getChargeLevel() < 100) {
		environmentPtr->rechargeBase.rechargeKiva(battery);
		updateDataToSimulator();
	}
	
	maneuverOut(rechargeDir);

	return true;
}

void Kiva::setTrajectory(Trajectory* tPtr) {
	trajectoryPtr = tPtr;
}

void Kiva::printTrajectory() {

	cout << "Kiva::printTrajectory\n";
	trajectoryPtr->printTrajectory();
}

void Kiva::printMissions() {
	missions.printQueue();
}

void Kiva::printCurrentState() {
	cout << "Kiva id: " << id << " current state" << endl;
	cout << "Pos: " << currentLocation;
	cout << "\tDir: " << currentDir;
	cout << "\tCharge: " << battery.getChargeLevel() << "%" <<endl;
}

void Kiva::wait(unsigned int milliseconds) {
	clock_t starting = clock();
	while (clock() - starting < milliseconds) {}
}

void Kiva::updateDataToSimulator() {
	srand(time(0));
	ofstream file("cpp_output.csv");
	if (file.is_open())
	{
		file << "lastPosX,lastPosY,changingPosTo,lastOrientation,changingOrientationTo,chargeLevel,isLoaded,mission" << endl;

		file << currentLocation.x << ",";
		file << currentLocation.y << ",";
		file << rand() % 5 << ","; // 0: not changing
		file << currentDir << ",";
		file << rand() % 5 << ","; // 0: not changing
		file << battery.getChargeLevel() << ",";
		file << isLoaded << ","; // 0: not changing

		if (currentMissionPtr) {
			file << currentMissionPtr->getOrigin() << " " << currentMissionPtr->getDestination();;
		}
		else {
			file << "none";
		}

		

		file.close();
	}
	wait(202);
}