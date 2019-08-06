#include <iostream>
#include <ncurses.h>

#include "CBonus.h"

CBonus::CBonus(unsigned score)
	: m_score(score)
{}

CBonus::CBonus(const CBonus & src)
{}

CBonus::~CBonus()
{}

unsigned CBonus::getScore()
{
	return m_score;
}