#include <ncurses.h>
#include <iostream>

#include "CBonus.h"
#include "CGame.h"

using namespace std;

CCoin::CCoin()
	: CBonus(COIN_POINTS)
{}

CCoin::CCoin(const CCoin & src)
	: CBonus(src.m_score)
{}

CCoin::~CCoin()
{}

void CCoin::drawBonus(size_t y, size_t x, WINDOW * win)
{
	wattron(win, COLOR_PAIR(CGame::PACMAN_COLOR));
	mvwaddch(win, y, x, '.');
	wattroff(win, COLOR_PAIR(CGame::PACMAN_COLOR));
	wrefresh(win);
}

CBonus * CCoin::copy()
{
	return new CCoin(*this);
}
