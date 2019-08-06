#include "CEntity.h"

CGhost::CGhost(CEntity * prey, unsigned color, const CBehavior & chase, const CBehavior & scatter, 
	const CBehavior & frightened) 
	: m_color(color), m_color_orig(color)
{
	m_chase = chase.copy();
	m_scatter = scatter.copy();
	m_frightened = frightened.copy();

	m_prey = prey;
}

CGhost::CGhost(const CGhost & src)
{
	m_chase = src.m_chase->copy();
	m_scatter = src.m_scatter->copy();
	m_frightened = src.m_frightened->copy();

	m_prey = src.m_prey;
}

CGhost::~CGhost()
{
	delete m_chase;
	delete m_scatter;
	delete m_frightened;
}

int CGhost::move(WINDOW * win, CMap * map, int & mode)
{
	pair<size_t, size_t> next;
	switch(mode){	// according to mode choose logic to calculate next position
		case CGame::CHASE:		next = m_chase->nextStep(map, m_prey, m_x, m_y);
								break;
		case CGame::SCATTER:	next = m_scatter->nextStep(map, m_prey, m_x, m_y);
								break;
		case CGame::FRIGHTENED:	next = m_frightened->nextStep(map, m_prey, m_x, m_y);
								break;
	}

	map->getElement(m_x, m_y)->draw(m_x+1, m_y+1, win);
	m_x = next.first;
	m_y = next.second;
	draw(win);

	return 0;	// ghost doesn't pick up bonuses
}

void CGhost::setStartPosition(size_t x, size_t y)
{
	m_start_x = m_x = x;
	m_start_y = m_y = y;
}

void CGhost::draw(WINDOW * win)
{
	wattron(win, COLOR_PAIR(m_color));
	mvwaddch(win, m_y + 1, m_x + 1, 'M');
	wattroff(win, COLOR_PAIR(m_color));
	wrefresh(win);
}

void CGhost::changeMode(WINDOW * win, CMap * map, int mode)
{
	if(mode == CGame::FRIGHTENED){
		m_color = CGame::FRIGHTENED_COLOR;
		m_chase->changeRoute(map, m_prey, m_x, m_y);
		m_scatter->changeRoute(map, m_prey, m_x, m_y);
		m_frightened->changeRoute(map, m_prey, m_x, m_y);
	} else {
		m_color = m_color_orig;
		m_chase->changeRoute(map, m_prey, m_x, m_y);
		m_scatter->changeRoute(map, m_prey, m_x, m_y);
		m_frightened->changeRoute(map, m_prey, m_x, m_y);
	}

	draw(win);
}

void CGhost::reset(WINDOW * win, CMap * map)
{
	m_x = m_start_x;
	m_y = m_start_y;

	m_chase->changeRoute(map, m_prey, m_x, m_y);
	m_scatter->changeRoute(map, m_prey, m_x, m_y);
	m_frightened->changeRoute(map, m_prey, m_x, m_y);

	draw(win);
}

void CGhost::changeColor(WINDOW * win)
{
	m_color = m_color_orig;
	draw(win);
}