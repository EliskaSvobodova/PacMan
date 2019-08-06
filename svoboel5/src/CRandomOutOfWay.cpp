
#include "CBehavior.h"

#include <cmath>
#include <cstdlib>
#include <iostream>

CRandomOutOfWay::CRandomOutOfWay()
{
	m_first = true;
}

CRandomOutOfWay::CRandomOutOfWay(const CRandomOutOfWay & src)
{}

CRandomOutOfWay::~CRandomOutOfWay()
{}

CBehavior * CRandomOutOfWay::copy() const
{
	CBehavior * cpy = new CRandomOutOfWay(*this);
	return cpy;
}

pair<size_t, size_t> CRandomOutOfWay::nextStep(CMap * map, CEntity * prey, size_t from_x, size_t from_y)
{
	if(m_first){
		m_goal = pickRandomPlace(map);
		m_route = AtoB(map, from_x, from_y, m_goal.first, m_goal.second);
		m_first = false;
	} 
	if(m_route.size() <= 1 || tooClose(prey, from_x, from_y)){
		m_goal = pickRandomPlace(map);
		m_route = AtoB(map, from_x, from_y, m_goal.first, m_goal.second);
	}

	// way not found
	while(m_route.empty()){
		m_goal = pickRandomPlace(map);
		m_route = AtoB(map, from_x, from_y, m_goal.first, m_goal.second);
	}

	m_route.pop_front();
	// ghost catched pac man
	if(m_route.empty())
		return make_pair(from_x, from_y);
	return m_route.front();
}

bool CRandomOutOfWay::tooClose(CEntity * prey, size_t x, size_t y)
{
	size_t square = sqrt(pow((double)x - (double)(prey->getX()), 2) + pow((double)y - (double)(prey->getY()), 2));
	if(square <= m_radius)
		return true;
	return false;
}

void CRandomOutOfWay::changeRoute(CMap * map, CEntity * prey, size_t from_x, size_t from_y)
{
	m_goal = pickRandomPlace(map);
	m_route = AtoB(map, from_x, from_y, m_goal.first, m_goal.second);
}