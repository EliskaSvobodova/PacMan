
#include "CBehavior.h"

#include <cmath>
#include <iostream>
#include <fstream>

CScatter::CScatter(int corner)
	: m_first(true), m_corner(corner)
{}

CScatter::CScatter(const CScatter & src)
	: m_first(src.m_first), m_corner(src.m_corner)
{}

CScatter::~CScatter()
{}

CBehavior * CScatter::copy() const
{
	CBehavior * cpy = new CScatter(*this);
	return cpy;
}

pair<size_t, size_t> CScatter::nextStep(CMap * map, CEntity * prey, size_t from_x, size_t from_y)
{
	if(m_first){
		findLoop(map);
		m_route_to_start = AtoB(map, from_x, from_y, m_goal.first, m_goal.second);
		m_first = false;
	}
	auto find = m_route.find(make_pair(from_x, from_y));

	if(find == m_route.end() && (m_route_to_start.front().first != from_x || m_route_to_start.front().second != from_y)){
		m_route_to_start = AtoB(map, from_x, from_y, m_goal.first, m_goal.second);
	}

	if(find == m_route.end()){
		m_route_to_start.pop_front();
		pair<size_t, size_t> next = m_route_to_start.front();
		return next;
	}
	return make_pair((*find).second.first, (*find).second.second);
}

void CScatter::findLoop(CMap * map)
{
	

	switch(m_corner){
		case LEFT_UP:	countLeftUp(map);
						break;
		case RIGHT_UP:	countRightUp(map);
						break;
		case RIGHT_DOWN:countRightDown(map);
						break;
		case LEFT_DOWN:	countLeftDown(map);
						break;
	}
}

void CScatter::countLeftUp(CMap * map)
{
	double tmp, min = sqrt((double)pow(map->getWidth()-1, 2) + (double)pow(map->getHeight()-1, 2));
	size_t x, y;
	bool found = false;
	for(int i = 0; !found; ++i){	// look in the map for the nearest free tile
		for(int j = i, k = 0; j >= 0; --j, ++k){
			if(map->freeToGo(k, j) && (tmp = sqrt((double)pow(k, 2) + (double)pow(j, 2))) < min){
					min = tmp;
					x = k;
					y = j;
					found = true;
			}
		}
	}
	m_goal = make_pair(x, y);
	m_route = smallestCycle(map, x, y);
}

void CScatter::countRightUp(CMap * map)
{
	double tmp, min = sqrt((double)pow(0 - (double)(map->getWidth() + 1), 2) + (double)pow(map->getHeight() - 1, 2));
	size_t x, y;
	bool found = false;
	for(int i = 0; !found; ++i){	// look in the map for the nearest free tile
		for(int j = i, k = map->getWidth() - 1; j >= 0; --j, --k){
			if(map->freeToGo(k, j) && (tmp = sqrt((double)pow((double)k - (double)(map->getWidth() - 1), 2) + (double)pow(j, 2))) < min){
					min = tmp;
					x = k;
					y = j;
					found = true;
			}
		}
	}
	m_goal = make_pair(x, y);
	m_route = smallestCycle(map, x, y);
}

void CScatter::countRightDown(CMap * map)
{
	double tmp, min = sqrt((double)pow(0 - (double)(map->getWidth()) + 1, 2) + (double)pow(0 - map->getHeight() + 1, 2));
	size_t x, y;
	bool found = false;
	for(int i = map->getWidth() - 1; !found; --i){	// look in the map for the nearest free tile
		for(int j = map->getHeight() - 1, k = i; (size_t)k < map->getWidth(); --j, ++k){
			if(map->freeToGo(k, j) && (tmp = sqrt((double)pow((double)k - (double)(map->getWidth()) + 1, 2) + (double)pow(j - (double)(map->getHeight()) + 1, 2))) < min){
					min = tmp;
					x = k;
					y = j;
					found = true;
			}
		}
	}
	m_goal = make_pair(x, y);
	m_route = smallestCycle(map, x, y);
}

void CScatter::countLeftDown(CMap * map)
{
	double tmp, min = sqrt((double)pow(map->getWidth() - 1, 2) + (double)pow(0 - (double)(map->getHeight()) + 1, 2));
	size_t x, y;
	bool found = false;
	for(int i = 0; !found; ++i){	// look in the map for the nearest free tile
		for(int j = map->getHeight() - 1, k = i; j >= 0; --j, --k){
			if(map->freeToGo(k, j) && (tmp = sqrt((double)pow((double)k - (double)(map->getWidth()), 2) + (double)pow(j, 2))) < min){
					min = tmp;
					x = k;
					y = j;
					found = true;
			}
		}
	}
	m_goal = make_pair(x, y);
	m_route = smallestCycle(map, x, y);
}

void CScatter::changeRoute(CMap * map, CEntity * prey, size_t from_x, size_t from_y)
{
	auto find = m_route.find(make_pair(from_x, from_y));
	if(find == m_route.end() && (m_route_to_start.front().first != from_x || m_route_to_start.front().second != from_y)){
		m_route_to_start = AtoB(map, from_x, from_y, m_goal.first, m_goal.second);
	}
}