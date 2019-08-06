#include "CBehavior.h"
#include <iostream>

CAggresive::CAggresive()
{}

CAggresive::CAggresive(const CAggresive & src)
{}

CAggresive::~CAggresive()
{}

CBehavior * CAggresive::copy() const
{
	CBehavior * cpy = new CAggresive(*this);
	return cpy;
}

pair<size_t, size_t> CAggresive::nextStep(CMap * map, CEntity * prey, size_t from_x, size_t from_y)
{
	list<pair<size_t, size_t>> l = AtoB(map, from_x, from_y, prey->getX(), prey->getY());
	// way not found
	if(l.empty())
		return make_pair(from_x, from_y);
	l.pop_front();
	// ghost catched pac man
	if(l.empty())
		return make_pair(prey->getX(), prey->getY());
	return l.front();
}