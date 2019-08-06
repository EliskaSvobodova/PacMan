#ifndef CTILE_H
#define CTILE_H

#include <ncurses.h>
#include <list>
#include "CBonus.h"

using namespace std;

/** Abstract class for different kinds of tiles in the map
* 	- also includes getters for position of all different tiles
*/

class CTile
{
public:
	/// constructor
	CTile(bool free_to_go, size_t x, size_t y);
	/// copy constructor
	CTile(const CTile & src);
	/// destructor
	virtual ~CTile();
	/// returns whether entity can go to the tile or not
	bool freeToGo();
	/// draw a tile, abstract
	virtual void draw(size_t x, size_t y, WINDOW * win) = 0;
	/// for copying different tiles
	virtual CTile * copy() = 0;
	/// validate teleports, if the tile isn't a teleport use default function
	virtual void validateTeleports(size_t x, size_t y);
	/// add neigbour node to the list of neigbour tiles (if we are able to got to this tile)
	virtual void addNeighbour(CTile * n);
	/// returns the number of neigbours
	virtual unsigned getNumNeighbours();
	/// if there is a bonus, delete it and return score
	virtual unsigned pickAndGetScore();
	/// returns the list of neighbours
	virtual list<CTile *> getListOfNeighbours();
	/// is there a bonus?
	virtual int isBonus();
	/// add bonus
	virtual void putBonus(const CCherry & bonus);
	/// getter for x position of the tile
	size_t getX();
	/// getter for y position of the tile
	size_t getY();
protected:
	bool m_free_to_go;	// is this a border or a free space?
	size_t m_x;	// position of the tile
	size_t m_y;
};

/**
 *	Class for teleport, derived from CTile
 *	- moving entities can go to the 'T' symbol on the map and appear on the second 'T'
 */

class CTeleport : public CTile
{
public:
	/// constructor
	CTeleport(size_t x, size_t y);
	/// copy constructor
	CTeleport(const CTeleport & src);
	/// destructor
	~CTeleport();
	/// draws 'T' in the position of teleport
	virtual void draw(size_t x, size_t y, WINDOW * win);
	/// for copying different tiles
	virtual CTile * copy();
	/// set positions of the other teleport to each other
	virtual void validateTeleports(size_t x, size_t y);
	/// add next option of where to go from here
	virtual void addNeighbour(CTile * n);
	/// returns the number of neigbour tiles (including other side of the teleport)
	virtual unsigned getNumNeighbours();
	/// returns the list of neigbour tiles (pointers to them) (including other side of the teleport)
	virtual list<CTile *> getListOfNeighbours();
private:
	size_t m_where_x; // position of the other side of teleport
	size_t m_where_y;
	list<CTile *> m_neighbours;
};

/** 
*	Class for ordinary space, derived from CTile
*	- free space in the maze, can hold bonuses (coin/cherry/shield)
*	- is able to work with it's bonus
*/

class CSpace : public CTile
{
public:
	/// constructor for empty space (without bonus)
	CSpace(size_t x, size_t y);
	/// constructor for space with a coin
	CSpace(size_t x, size_t y, const CCoin & coin);
	/// constructor for space with a cherry
	CSpace(size_t x, size_t y, const CCherry & cherry);
	/// constructor for space with a shield
	CSpace(size_t x, size_t y, const CShield & shield);
	/// copy constructor
	CSpace(const CSpace & src);
	/// destructor
	~CSpace();
	/// draw empty space ' ' or a right kind of bonus if there is
	virtual void draw(size_t x, size_t y, WINDOW * win);
	/// for copying different tiles
	virtual CTile * copy();
	/// add where to go next
	virtual void addNeighbour(CTile * n);
	/// if there is a bonus on the tile delete it from the map and return the right score for the kind of bonus
	virtual unsigned pickAndGetScore();
	/// returns the number of neigbour tiles
	virtual unsigned getNumNeighbours();
	/// returns the list of neigbour tiles (pointers to them)
	virtual list<CTile *> getListOfNeighbours();
	/// 0 - no bonus, 1 - there is a bonus, -1 - you cannot put a bonus here
	virtual int isBonus();
	/// add bonus
	virtual void putBonus(const CCherry & bonus);
private:
	CBonus * m_bonus;	// pointer to a type of bonus class, or NULL if there is no bonus
	list<CTile *> m_neighbours;
};

/**
*	Class for a wall, derived from CTile
*	- entities can't go there
*/

class CWall : public CTile
{
public:
	/// constructor
	CWall(size_t x, size_t y);
	/// copy constructor
	CWall(const CWall & src);
	/// destructor
	~CWall();
	/// draw a wall on the given position (colored ' ')
	virtual void draw(size_t x, size_t y, WINDOW * win);
	/// for copying different tiles
	virtual CTile * copy();
private:
};

#endif // CTILE_H