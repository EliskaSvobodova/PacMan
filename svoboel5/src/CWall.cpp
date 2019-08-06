#include <iostream>
#include <ncurses.h>
#include <fstream>

using namespace std;

#include "CTile.h"

CWall::CWall(size_t x, size_t y)
	: CTile(false, x, y)
{}

CWall::CWall(const CWall & src)
	: CTile(src.m_free_to_go, src.m_x, src.m_y)
{}

CWall::~CWall()
{}

void CWall::draw(size_t x, size_t y, WINDOW * win)
{
	wattron(win, COLOR_PAIR(2));
	mvwaddch(win, y, x, ' ');	// space will be colored
	wattroff(win, COLOR_PAIR(2));
	wrefresh(win);
}

CTile * CWall::copy()
{
	CTile * cpy = new CWall(*this);
	return cpy;
}
