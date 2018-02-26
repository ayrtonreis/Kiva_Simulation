/* Mission.h : engloba as coordenadas X e Y das posicoes Inicial e Final
** da missao, assim como a direcao tangente 'a trajetoria que o robo deve
** se locomover para carregar ou descarregar as estantes de produtos
*/

#include "MissionQueue.h"

MissionQueue::MissionQueue()
{
}

MissionQueue::~MissionQueue()
{
}

unsigned int MissionQueue::size() 
{
	return list.size();
}

void MissionQueue::addMission(Mission m) 
{
	list.push_back(m);
}

void MissionQueue::addMissionFront(Mission m)
{
	list.push_front(m);
}

Mission MissionQueue::popFront() 
{
	Mission m = list.front();
	list.pop_front();
	return m;
}
bool MissionQueue::removeMissionFromId(unsigned int id)
{

	for (std::list<Mission>::iterator it = list.begin(); it != list.end(); ++it) {
		if (it->id == id) {
			it = list.erase(it);
			return true;
		}
		else {
			++it;
		}
	}
	
	return false;
}

void MissionQueue::printQueue() 
{
	unsigned int i = 0;
	for (std::list<Mission>::iterator it = list.begin(); it != list.end(); ++it) {
		cout << "[" << i << "]\t";
		it->printMission();
		i++;
	}
}