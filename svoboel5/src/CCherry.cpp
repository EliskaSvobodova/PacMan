#include <ncurses.h>

#include "CBonus.h"
#include "CGame.h"

CCherry::CCherry()
	: CBonus(CHERRY_POINTS)
{}

CCherry::CCherry(const CCherry & src)
	: CBonus(src.m_score)
{}

CCherry::~CCherry()
{}

void CCherry::drawBonus(size_t y, size_t x, WINDOW * win)
{
	wattron(win, COLOR_PAIR(CGame::RED_COLOR));
	mvwaddch(win, y, x, '*');
	wattroff(win, COLOR_PAIR(CGame::RED_COLOR));
	wrefresh(win);
}

CBonus * CCherry::copy()
{
	return new CCherry(*this);
}