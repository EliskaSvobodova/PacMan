#include "CTile.h"

CTile::CTile(bool free_to_go, size_t x, size_t y)
	: m_free_to_go(free_to_go), m_x(x), m_y(y)
{}

CTile::CTile(const CTile & src)
	: m_free_to_go(src.m_free_to_go), m_x(src.m_x), m_y(src.m_y)
{}

CTile::~CTile()
{}

// defalut function for non-teleport tiles
void CTile::validateTeleports(size_t x, size_t y)
{}

bool CTile::freeToGo()
{
	return m_free_to_go;
}

// default function
void CTile::addNeighbour(CTile *)
{}

// pickAndGetScore() function called on non-space projects - there is certainly no bonus - return 0
unsigned CTile::pickAndGetScore()
{
	return 0;
}

// default value for tiles where entities can not go
unsigned CTile::getNumNeighbours()
{
	return 0;
}

// default - return the empty list
list<CTile *> CTile::getListOfNeighbours()
{
	list<CTile *> tmp;
	return tmp;
}

size_t CTile::getX()
{
	return m_x;
}

size_t CTile::getY()
{
	return m_y;
}

// cannot put bonus here
int CTile::isBonus()
{
	return -1;
}

// default function for tiles where you can't put a bonus
void CTile::putBonus(const CCherry & bonus)
{}