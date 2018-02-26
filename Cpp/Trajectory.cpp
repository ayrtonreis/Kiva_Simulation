/* Trajectory.h : implementa uma lista circular com as localizacoes da trajetoria do Kiva */


#include "Trajectory.h"

Trajectory::Trajectory(vector<Location>* vPtr): 
	vecPtr(vPtr), rechargeBaseLocation(vPtr->at(0)), rechargeBaseDirection(4)
{
}


Trajectory::~Trajectory()
{
	delete vecPtr;
}

/* Encontra a direcao (1: h, 0: anti-h) do caminho mais curto
entre dois pontos quaisquer da trajetoria*/
bool Trajectory::chooseDirection(const Location& l1, const Location& l2) 
{
	vector<Location>::iterator it1, it2;
	it1 = find(vecPtr->begin(), vecPtr->end(), l1);
	it2 = find(vecPtr->begin(), vecPtr->end(), l2);

	if (it1 == vecPtr->end() || it2 == vecPtr->end()) 
		cerr << "ERROR: LOCATION NOT FOUND IN THE TRAJECTORY.\n";


	unsigned int index1, index2;
	index1 = distance(vecPtr->begin(), it1);
	index2 = distance(vecPtr->begin(), it2);

	//cout << "index1: " << index1 << ", index2: " << index2 << endl;

	if (index2 > index1) {
		return (index2 - index1) <= (vecPtr->size() - 1 - index2 + index1);
	}
	else {
		return (vecPtr->size() - 1 - index1 + index2) <= (index1 - index2);
	}

	return false;
}

unsigned int Trajectory::findCurrentIndexPos(const Location& l) 
{
	vector<Location>::iterator it = find(vecPtr->begin(), vecPtr->end(), l);
	return distance(vecPtr->begin(), it);
}

/*Retorna a proxima posicao na trajetoria, dado o indice da localizacao atual do robo
e o sentido (h ou anti-h) que ele deve seguir*/
Location& Trajectory::getNext(bool direction, unsigned int currentIndexPos)
{
	if (direction) 
	{
		currentIndexPos++;
		//Impede que currentIndexPos seja seja maior que o ultimo index do vetor
		currentIndexPos %= vecPtr->size();
	}
	else if (currentIndexPos > 0) {
		currentIndexPos--;
	}
	else {
		//Impede que currentIndexPos seja negativo
		currentIndexPos = vecPtr->size()-1;
	}

	return vecPtr->at(currentIndexPos);
}

unsigned int Trajectory::incrementIndexPos(bool direction, unsigned int currentIndexPos) 
{
	
	if (direction) {
		//cout << "a";
		return (currentIndexPos + 1) % vecPtr->size();
	}
		
	else if (currentIndexPos > 0) {
		//cout << "b";
		return (currentIndexPos - 1);
	}
		
	else {
		//cout << "c";
		return (vecPtr->size() - 1);
	}
		
}

void Trajectory::printTrajectory() 
{
	cout << "Trajectory::printTrajectory\n";
	for (vector<Location>::iterator it = vecPtr->begin(); it != vecPtr->end(); ++it) {
		cout << "x: " << it->x << " y: " << it->y << endl;
	}

	cout << "Trajectory size: " << (*vecPtr).size() << endl;

	Location l2(28, 20), l1(16, 52);
	cout << "L1: " << l1 << "\tL2: " << l2 << endl;

	cout << "Choose Trajectory: " << chooseDirection(l1, l2) <<endl;

}