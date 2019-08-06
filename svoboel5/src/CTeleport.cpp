#include <cstddef>
#include <iostream>
#include <ncurses.h>
#include <list>

using namespace std;

#include "CTile.h"

CTeleport::CTeleport(size_t x, size_t y)
	: CTile(true, x, y)
{}

CTeleport::CTeleport(const CTeleport & src)
	: CTile(src.m_free_to_go, src.m_x, src.m_y), m_where_x(src.m_where_x), m_where_y(src.m_where_y)
{}

CTeleport::~CTeleport()
{}

void CTeleport::draw(size_t x, size_t y, WINDOW * win)
{
	wattron(win, COLOR_PAIR(3));
	mvwaddch(win, y, x, 'T');
	wattroff(win, COLOR_PAIR(3));
	wrefresh(win);
}

CTile * CTeleport::copy()
{
	CTile * cpy = new CTeleport(*this);
	return cpy;
}

void CTeleport::validateTeleports(size_t x, size_t y)
{
	m_where_x = x;
	m_where_y = y;
}

void CTeleport::addNeighbour(CTile * n)
{
	m_neighbours.push_back(n);
}

unsigned CTeleport::getNumNeighbours()
{
	return m_neighbours.size();
}

list<CTile *> CTeleport::getListOfNeighbours()
{
	return m_neighbours;
}