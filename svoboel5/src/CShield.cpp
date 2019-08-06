#include <ncurses.h>

#include "CBonus.h"
#include "CGame.h"

CShield::CShield()
	: CBonus(SHIELD_POINTS)
{}

CShield::CShield(const CShield & src)
	: CBonus(src.m_score)
{}

CShield::~CShield()
{}

void CShield::drawBonus(size_t y, size_t x, WINDOW * win)
{
	wattron(win, COLOR_PAIR(CGame::RED_COLOR));
	mvwaddch(win, y, x, 'o');
	wattroff(win, COLOR_PAIR(CGame::RED_COLOR));
	wrefresh(win);
}

CBonus * CShield::copy()
{
	return new CShield(*this);
}