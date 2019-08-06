
#include "CEntity.h"
#include <typeinfo>

CPacMan::CPacMan()
{
	m_direction = LEFT;
	m_just_teleported = false;
}

CPacMan::CPacMan(const CPacMan & src)
{}

CPacMan::~CPacMan()
{}

int CPacMan::move(WINDOW * win, CMap * map, int & mode)
{
	if(!m_just_teleported && typeid(*(map->getElement(m_x, m_y))) == typeid(CTeleport)){
		// destination of the teleport will be first in the list of neigbours
		map->getElement(m_x, m_y)->draw(m_x+1, m_y+1, win);
		m_x = map->getElement(m_x, m_y)->getListOfNeighbours().front()->getX();
		m_y = map->getElement(m_x, m_y)->getListOfNeighbours().front()->getY();
		draw(win);
		m_just_teleported = true;
		return 0;
	}
	
	switch(m_direction){
		case UP:	if(m_y != 0 && map->freeToGo(m_x, m_y-1)){	// is pac man allowed to go there?
						if(m_just_teleported)
							map->getElement(m_x, m_y)->draw(m_x+1, m_y+1, win);
						else
							mvwaddch(win, m_y + 1, m_x + 1, ' ');	// erase pac man from the previous position
						--m_y;	// update position
						draw(win);	// draw pac man on the new position
					}
					m_just_teleported = false;
					return map->grabBonus(m_x, m_y, mode);	// if there is a bonus, grab it
		case RIGHT:	if(m_x != map->getWidth()-1 && map->freeToGo(m_x+1, m_y)){
						if(m_just_teleported)
							map->getElement(m_x, m_y)->draw(m_x+1, m_y+1, win);
						else
							mvwaddch(win, m_y + 1, m_x + 1, ' ');
						++m_x;
						draw(win);
					}
					m_just_teleported = false;
					return map->grabBonus(m_x, m_y, mode);
		case DOWN:	if(m_y != map->getHeight()-1 && map->freeToGo(m_x, m_y+1)){
						if(m_just_teleported)
							map->getElement(m_x, m_y)->draw(m_x+1, m_y+1, win);
						else
							mvwaddch(win, m_y + 1, m_x + 1, ' ');
						++m_y;
						draw(win);
					}
					m_just_teleported = false;
					return map->grabBonus(m_x, m_y, mode);
		case LEFT:	if(m_x != 0 && map->freeToGo(m_x-1, m_y)){
						if(m_just_teleported)
							map->getElement(m_x, m_y)->draw(m_x+1, m_y+1, win);
						else
							mvwaddch(win, m_y + 1, m_x + 1, ' ');
						--m_x;
						draw(win);
					}
					m_just_teleported = false;
					return map->grabBonus(m_x, m_y, mode);
	}
	return 0;
}

void CPacMan::setStartPosition(size_t x, size_t y)
{
	m_start_x = m_x = x;
	m_start_y = m_y = y;
}

void CPacMan::draw(WINDOW * win)
{
	wattron(win, COLOR_PAIR(1));
	mvwaddch(win, m_y + 1, m_x + 1, 'O');
	wattroff(win, COLOR_PAIR(1));
	wrefresh(win);
}

void CPacMan::changeDirection(unsigned direction)
{
	m_direction = direction;
}

unsigned CPacMan::getDirection()
{
	return m_direction;
}

void CPacMan::reset(WINDOW * win, CMap * map)
{
	m_x = m_start_x;
	m_y = m_start_y;

	draw(win);
}