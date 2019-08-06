
#include "CBehavior.h"
#include <iostream>

CAmbush::CAmbush()
{}

CAmbush::CAmbush(const CAmbush & src)
{}

CAmbush::~CAmbush()
{}

CBehavior * CAmbush::copy() const
{
	CBehavior * cpy = new CAmbush(*this);
	return cpy;
}

pair<size_t, size_t> CAmbush::nextStep(CMap * map, CEntity * prey, size_t from_x, size_t from_y)
{
	// count where is prey heading (next crossroads)

	pair<size_t, size_t> pm_heading_orig = make_pair(prey->getX(), prey->getY());	// where will be prey next time (if it won't change its direction)
	pair<size_t, size_t> pm_heading_new = preyHeading(map, prey->getDirection(), prey->getX(), prey->getY());	// to know when prey is in the corner
	while(map->countNeighbours(pm_heading_orig.first, pm_heading_orig.second) == 2 && pm_heading_orig != pm_heading_new){	// find the end of the "street without braches" (first crossroads)
		pm_heading_orig = pm_heading_new;
		pm_heading_new = preyHeading(map, prey->getDirection(), pm_heading_orig.first, pm_heading_orig.second);
	}
	//std::cout << pm_heading_orig.first << " " << pm_heading_orig.second << std::endl;
	list<pair<size_t, size_t>> l = AtoB(map, from_x, from_y, pm_heading_orig.first, pm_heading_orig.second);
	
	// way not found
	if(l.empty())
		return make_pair(from_x, from_y);
	l.pop_front();
	// ghost catched pac man
	if(l.empty())
		return make_pair(prey->getX(), prey->getY());
	return l.front();
}

pair<size_t, size_t> CAmbush::preyHeading(CMap * map, unsigned prey_direction, size_t x, size_t y)
{
	switch(prey_direction){
		case CPacMan::UP:		if(y != 0 && map->freeToGo(x, y - 1))
									return make_pair(x, y - 1);
								else
									return make_pair(x, y);
		case CPacMan::DOWN:		if(y != map->getHeight() - 1 && map->freeToGo(x, y + 1))
									return make_pair(x, y + 1);
								else
									return make_pair(x, y);
		case CPacMan::LEFT:		if(x != 0 && map->freeToGo(x - 1, y))
									return make_pair(x - 1, y);
								else
									return make_pair(x, y);
		case CPacMan::RIGHT:	if(x != map->getWidth() - 1 && map->freeToGo(x + 1, y))
									return make_pair(x + 1, y);
								else
									return make_pair(x, y);
		default:				return make_pair(0, 0);
	}
}