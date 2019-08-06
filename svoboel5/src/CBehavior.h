#ifndef CBEHAVIOR_H
#define CBEHAVIOR_H

#include "CEntity.h"

#include <map>

class CEntity;

/**
*	Abstract class for different kinds of behaviors
*	- has common methods for counting the route of the ghost
*/

class CBehavior
{
public:
	/// constructor
	CBehavior();
	/// copy constructor
	CBehavior(const CBehavior & src);
	/// destructor
	virtual ~CBehavior();
	/// method that copies elements
	virtual CBehavior * copy() const = 0;
	/// returns where to go in the next step
	virtual pair<size_t, size_t> nextStep(CMap * map, CEntity * prey, size_t from_x, size_t from_y) = 0;
	/// resets routes
	virtual void changeRoute(CMap * map, CEntity * prey, size_t from_x, size_t from_y);
protected:
	/// bfs for finding the shortest way from A to B
	list<pair<size_t, size_t>> AtoB(CMap * map, size_t from_x, size_t from_y, size_t to_x, size_t to_y);
	/// picks a random place where entity can go
	pair<size_t, size_t> pickRandomPlace(CMap * map);
	///	creates a route (list of coordinates) from 2D array with ancestors of the each (searched) tile
	list<pair<size_t, size_t>> makeList(vector<vector<CTile *>> ancestor, size_t x, size_t y);
	/// creates a route (map of tiles and coordinates from where to get on them) from 2D array with ancestors of the each (searched) tile
	map<pair<size_t, size_t>, pair<size_t, size_t>> makeMap(vector<vector<CTile *>> ancestor, size_t x, size_t y, size_t x2, size_t y2);
	/// finds smallest cycle from the starting point
	map<pair<size_t, size_t>, pair<size_t, size_t>> smallestCycle(CMap * map, size_t start_x, size_t start_y);
};

/**
*	Class for Aggresive strategy, derived from CBehavior
*	- it finds the shortest way from starting point to the prey
*/

class CAggresive : public CBehavior
{
public:
	/// constructor
	CAggresive();
	/// copy constructor
	CAggresive(const CAggresive & src);
	/// destructor
	virtual ~CAggresive();
	/// copies the instance and returns its copy
	virtual CBehavior * copy() const;
	/// returns where to go next
	virtual pair<size_t, size_t> nextStep(CMap * map, CEntity * prey, size_t from_x, size_t from_y);
};

/**
*	Class for Ambush strategy, derived from CBehavior
*	- it finds the shortest way to the place where prey is heading (next crossroads)
*/

class CAmbush : public CBehavior
{
public:
	/// constructor
	CAmbush();
	/// copy constructor
	CAmbush(const CAmbush & src);
	/// destructor
	virtual ~CAmbush();
	/// copies the instance and returns its copy
	virtual CBehavior * copy() const;
	/// returns where to go next
	virtual pair<size_t, size_t> nextStep(CMap * map, CEntity * prey, size_t from_x, size_t from_y);
private:
	// finds out the next cross-roads where prey will be, if it doesn't change it's direction
	pair<size_t, size_t> preyHeading(CMap * map, unsigned prey_direction, size_t x, size_t y);
};

/**
*	Clas for Patrol strategy, derived from CVehavior
*	- it patrols the area of the maze
*	- it picks the random place in the currently looked quarter of the maze and goes there, then it picks the next quarter and repeats
*/

class CPatrol : public CBehavior
{
public:
	/// constructor
	CPatrol();
	/// copy constructor
	CPatrol(const CPatrol & src);
	/// destructor
	virtual ~CPatrol();
	/// copies the instance and returns its copy
	virtual CBehavior * copy() const;
	/// returns where to go next
	virtual pair<size_t, size_t> nextStep(CMap * map, CEntity * prey, size_t from_x, size_t from_y);
	/// recounts the route
	virtual void changeRoute(CMap * map, CEntity * prey, size_t from_x, size_t from_y);
private:
	list<pair<size_t, size_t>> m_route; // save the calculated path
	pair<size_t, size_t> m_goal;	// to where is ghost heading
	unsigned m_corner; // 0 1	// numbers of corners (to which is ghost heading)
				  	   // 2 3
	bool m_first;
	// picks a random place, where entity can go and is in the right quarter
	pair<size_t, size_t> pickGoal(CMap * map);
};

/**
*	Class for strategy of Random behavior, derived from CBehavior
*	- it picks a random place in the map and goes there by shortest way
*	- if the entity is too close to the pray, it recounts the route
*/

class CRandomOutOfWay : public CBehavior
{
public:
	/// constructor
	CRandomOutOfWay();
	/// copy constructor
	CRandomOutOfWay(const CRandomOutOfWay & src);
	/// destructor
	virtual ~CRandomOutOfWay();
	/// copies the instance and returns its copy
	virtual CBehavior * copy() const;
	/// returns where to go next
	virtual pair<size_t, size_t> nextStep(CMap * map, CEntity * prey, size_t from_x, size_t from_y);
	/// recounts the route
	virtual void changeRoute(CMap * map, CEntity * prey, size_t from_x, size_t from_y);
private:
	list<pair<size_t, size_t>> m_route; // save the calculated path
	pair<size_t, size_t> m_goal;	// to where is ghost heading
	bool m_first;
	const unsigned m_radius = 5;	// definition of what means "close to the prey"

	// finds out whether the given place is too close to the prey
	bool tooClose(CEntity * prey, size_t x, size_t y);

};

/**
*	class for Scatter strategy, derived from CBahavior
*	- it has a given corner where to go
*	- it picks the place, free to go for the entity, nearest of that corner and the shortest way how to get there
*	- also calculates the smallest cycle int that corner, where will be entity going around
*	- go around the smallest cycle in the given corner
*/

class CScatter : public CBehavior
{
public:
	/// constructor
	CScatter(int corner);
	/// copy constructor
	CScatter(const CScatter & src);
	/// destructor
	virtual ~CScatter();
	/// copies the instance and returns its copy
	virtual CBehavior * copy() const;
	/// returns where to go next
	virtual pair<size_t, size_t> nextStep(CMap * map, CEntity * prey, size_t from_x, size_t from_y);
	/// recounts the route
	virtual void changeRoute(CMap * map, CEntity * prey, size_t from_x, size_t from_y);
	/// symbolic constant for a corner
	static const int LEFT_UP = 1;
	/// symbolic constant for a corner
	static const int RIGHT_UP = 2;
	/// symbolic constant for a corner
	static const int RIGHT_DOWN = 3;
	/// symbolic constant for a corner
	static const int LEFT_DOWN = 4;
private:
	// finds the smallest loop in the given corner
	void findLoop(CMap * map);
	// counts the nearest from the, possible to go place
	void countLeftUp(CMap * map);
	void countRightUp(CMap * map);
	void countRightDown(CMap * map);
	void countLeftDown(CMap * map);
	
	bool m_first;
	int m_corner;
	list<pair<size_t, size_t>> m_route_to_start;	// route to the cycle
	pair<size_t, size_t> m_goal;	// corner
	map<pair<size_t, size_t>, pair<size_t, size_t>> m_route;	// the cycle
};

#endif // CBEHAVIOR_H