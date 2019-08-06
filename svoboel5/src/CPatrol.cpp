
#include "CBehavior.h"

#include <cstdlib>
#include <iostream>

CPatrol::CPatrol()
{
	m_first = true;
}

CPatrol::CPatrol(const CPatrol & src)
	: m_corner(src.m_corner), m_first(src.m_first)
{}

CPatrol::~CPatrol()
{}

CBehavior * CPatrol::copy() const
{
	CBehavior * cpy = new CPatrol(*this);
	return cpy;
}

pair<size_t, size_t> CPatrol::nextStep(CMap * map, CEntity * prey, size_t from_x, size_t from_y)
{
	if(m_first){
		srand(time(0));
		m_corner = rand() % 4;
		m_first = false;
		m_goal = pickGoal(map);
		m_route = AtoB(map, from_x, from_y, m_goal.first, m_goal.second);
	} else if(m_route.size() == 1){
		m_corner = (m_corner == 3 ? 0 : m_corner + 1);
		m_goal = pickGoal(map);
		m_route = AtoB(map, from_x, from_y, m_goal.first, m_goal.second);
	} else if(m_route.empty()){
		m_goal = pickGoal(map);
		m_route = AtoB(map, from_x, from_y, m_goal.first, m_goal.second);
	}

	// randomly picked route of size 1 (bad luck)
	while(m_route.size() <= 1){
		m_goal = pickGoal(map);
		m_route = AtoB(map, from_x, from_y, m_goal.first, m_goal.second);
	}
	m_route.pop_front();
	return m_route.front();
}

pair<size_t, size_t> CPatrol::pickGoal(CMap * map)
{
	// 0 1	// numbers of corners (to which is ghost heading)
	// 3 2
	while(true){	// while some place isn't chosen
		m_goal = pickRandomPlace(map);
		switch(m_corner){
			case 0:	if(m_goal.first < (map->getWidth() / 2) && m_goal.second < (map->getHeight() / 2))
						return m_goal;
					break;
			case 1:	if(m_goal.first > (map->getWidth() / 2) && m_goal.second < (map->getHeight() / 2))
						return m_goal;
					break;
			case 2:	if(m_goal.first > (map->getWidth() / 2) && m_goal.second > (map->getHeight() / 2))
						return m_goal;
					break;
			case 3:	if(m_goal.first < (map->getWidth() / 2) && m_goal.second > (map->getHeight() / 2))
						return m_goal;
					break;
		}
	}
}

void CPatrol::changeRoute(CMap * map, CEntity * prey, size_t from_x, size_t from_y)
{
	srand(time(0));
	m_corner = rand() % 4;
	m_goal = pickGoal(map);
	m_route = AtoB(map, from_x, from_y, m_goal.first, m_goal.second);
}