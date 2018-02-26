/* Mission.cpp : engloba as coordenadas X e Y das posicoes Inicial e Final
** da missao, assim como a direcao tangente 'a trajetoria que o robo deve
** se locomover para carregar ou descarregar as estantes de produtos
*/

#include "Mission.h"

Mission::Mission(unsigned int m_id, Location l1, unsigned int l1_dir, Location l2, unsigned int l2_dir): 
	id(m_id), origin(l1), destination(l2), originDir(l1_dir), destinationDir(l2_dir)
{
}

Mission::~Mission()
{
}

void Mission::setOrigin(unsigned int x, unsigned int y, unsigned int dir) 
{
	origin.x = x;
	origin.y = y;
	originDir = dir;
}
void Mission::setDestination(unsigned int x, unsigned int y, unsigned int dir) 
{
	destination.x = x;
	destination.y = y;
	destinationDir = dir;
}
Location Mission::getOrigin() 
{
	return origin;
}

unsigned int Mission::getOriginDir() 
{
	return originDir;
}

Location Mission::getDestination() 
{
	return destination;
}

unsigned int Mission::getDestinationDir() 
{
	return destinationDir;
}

void Mission::printMission() 
{
	cout << "From: " << origin << "\tTo: " << destination << endl;
}