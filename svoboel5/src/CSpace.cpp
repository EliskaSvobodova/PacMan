#include <cstddef>
#include <iostream>
//#include <ncurses.h>
#include <list>

using namespace std;

#include "CTile.h"

CSpace::CSpace(size_t x, size_t y)
	: CTile(true, x, y)
{
	m_bonus = NULL;
}

CSpace::CSpace(size_t x, size_t y, const CCoin & coin)
	: CTile(true, x, y)
{
	m_bonus = new CCoin(coin);
}

CSpace::CSpace(size_t x, size_t y, const CCherry & cherry)
	: CTile(true, x, y)
{
	m_bonus = new CCherry(cherry);
}

CSpace::CSpace(size_t x, size_t y, const CShield & shield)
	: CTile(true, x, y)
{
	m_bonus = new CShield(shield);
}

CSpace::CSpace(const CSpace & src)
	: CTile(src.m_free_to_go, src.m_x, src.m_y)
{
	if(src.m_bonus != NULL){
		m_bonus = (*src.m_bonus).copy();
	} else {
		m_bonus = NULL;
	}
}

CSpace::~CSpace()
{
	if(m_bonus != NULL)
		delete m_bonus;
}

void CSpace::draw(size_t x, size_t y, WINDOW * win)
{
	if(m_bonus != NULL){
		(*m_bonus).drawBonus(y, x, win);
	} else{
		mvwaddch(win, y, x, ' ');
		wrefresh(win);
	}
}

CTile * CSpace::copy()
{
	CTile * cpy = new CSpace(*this);
	return cpy;
}

void CSpace::addNeighbour(CTile * n)
{
	m_neighbours.push_back(n);
}

unsigned CSpace::getNumNeighbours()
{
	return m_neighbours.size();
}

unsigned CSpace::pickAndGetScore()
{
	unsigned score;
	if(m_bonus != NULL){
		score = m_bonus->getScore();
		delete m_bonus;
		m_bonus = NULL;
		return score;
	}
	return 0;
}

list<CTile *> CSpace::getListOfNeighbours()
{
	return m_neighbours;
}

int CSpace::isBonus()
{
	if(m_bonus == NULL)
		return 0;
	return 1;
}

void CSpace::putBonus(const CCherry & bonus)
{
	m_bonus = new CCherry(bonus);
}