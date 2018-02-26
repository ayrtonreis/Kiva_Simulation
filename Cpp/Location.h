/* Location.h : engloba as coordenadas X e Y de posicao.
** Overload de operadores foram implementados para facilitar a comparacao
** entre duas localizacoes e a escrita de objetos na tela e em arquivos
 */

#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>

using namespace std;

class Location
{
public:
	unsigned int x, y;
	Location();
	Location(unsigned int x, unsigned int y);
	~Location();
	Location& operator=(const Location &rhs);
	bool operator==(const Location &rhs) const;
	bool operator!=(const Location &rhs) const;
	friend ostream& operator<<(ostream& os, const Location& l);
};

#endif // LOCATION_H