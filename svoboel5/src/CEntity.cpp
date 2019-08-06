
#include "CEntity.h"

CEntity::CEntity()
{}

CEntity::CEntity(const CEntity & src)
{}

CEntity::~CEntity()
{}

// default function for ghost
void CEntity::changeDirection(unsigned direction)
{}

size_t CEntity::getX()
{
	return m_x;
}

size_t CEntity::getY()
{
	return m_y;
}

size_t CEntity::getStartX()
{
	return m_start_x;
}

size_t CEntity::getStartY()
{
	return m_start_y;
}

// default for ghosts
unsigned CEntity::getDirection()
{
	return 0;
}

void CEntity::reset(WINDOW * win, CMap * map)
{}

void CEntity::changeColor(WINDOW * win)
{}

void CEntity::changeMode(WINDOW * win, CMap * map, int mode)
{}