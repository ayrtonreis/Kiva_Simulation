/* Mission.h : engloba as coordenadas X e Y das posicoes Inicial e Final
** da missao, assim como a direcao tangente 'a trajetoria que o robo deve
** se locomover para carregar ou descarregar as estantes de produtos
*/

#ifndef MISSION_H
#define MISSION_H

#include "Location.h"

class Mission
{
private:
	Location origin;
	Location destination;
	unsigned int originDir, destinationDir;

public:
	const unsigned int id;
	Mission(unsigned int m_id, Location l1, unsigned int l1_dir, Location l2, unsigned int l2_dir);
	~Mission();
	void setOrigin(unsigned int x, unsigned int y, unsigned int dir);
	void setDestination(unsigned int x, unsigned int y, unsigned int dir);
	Location getOrigin();
	unsigned int getOriginDir();
	Location getDestination();
	unsigned int getDestinationDir();
	void printMission();

};

#endif // MISSION_H