/* Location.cpp : engloba as coordenadas X e Y de posicao.
** Overload de operadores foram implementados para facilitar a comparacao
** entre duas localizacoes e a escrita de objetos na tela e em arquivos
 */

#include "Location.h"

Location::Location()
{
	x = 0;
	y = 0;
}

Location::Location(unsigned int x, unsigned int y): x(x), y(y)
{
}

Location& Location::operator=(const Location &rhs) {
	if (this != &rhs) {
		x = rhs.x;
		y = rhs.y;
	}

	return *this;
}

bool Location::operator==(const Location &rhs) const {
	return x == rhs.x && y == rhs.y;
}

bool Location::operator!=(const Location &rhs) const {
	return !(*this == rhs);
}

ostream & operator<<(ostream & os, const Location & l)
{
	os << "(" << l.x << ';' << l.y << ")";
	return os;
}

Location::~Location()
{
}