#ifndef CENTITY_H
#define CENTITY_H

#include <cstddef>
#include <ncurses.h>

#include "CMap.h"
#include "CBehavior.h"
#include "CGame.h"

class CBehavior;

/** 
*	Abstract class for moving objects - entities
*/

class CEntity
{
public:
	/// constructor
	CEntity();
	/// copy constructor
	CEntity(const CEntity & src);
	/// destructor
	virtual ~CEntity();
	/// move with the entity
	virtual int move(WINDOW * win, CMap * map, int & mode) = 0;
	/// set the starting point for entities
	virtual void setStartPosition(size_t x, size_t y) = 0;
	/// draw entity
	virtual void draw(WINDOW * win) = 0;
	/// change direction where pac man is going
	virtual void changeDirection(unsigned direction);
	/// getter for pac man's direction
	virtual unsigned getDirection();
	/// put ghost in the starting state
	virtual void reset(WINDOW * win, CMap * map);
	/// change color
	virtual void changeColor(WINDOW * win);
	/// change mode
	virtual void changeMode(WINDOW * win, CMap * map, int mode);
	/// getter for current x position
	size_t getX();
	/// getter for current y position
	size_t getY();
	/// getter for starting x position
	size_t getStartX();
	/// getter for starting y position
	size_t getStartY();
protected:
	/// current position of the entity
	size_t m_x;
	/// current position of the entity
	size_t m_y;
	/// starting position of the entity
	size_t m_start_x;
	/// starting position of the entity
	size_t m_start_y;
};

/**
*	Class for by user controled entity - Pac Man, derived from CEntity
*/

class CPacMan : public CEntity
{
public:
	/// constructor
	CPacMan();
	/// copy constructor
	CPacMan(const CPacMan & src);
	/// destructor
	virtual ~CPacMan();
	/// move with pac man in the direction it is heading (if possible)
	virtual int move(WINDOW * win, CMap * map, int & mode);
	/// set values of m_x, m_y
	virtual void setStartPosition(size_t x, size_t y);
	/// set pac man to starting position
	virtual void reset(WINDOW * win, CMap * map);
	/// draw pac man - yellow 'O'
	virtual void draw(WINDOW * win);
	/// change direction of movement
	virtual void changeDirection(unsigned direction);
	/// returns direction
	virtual unsigned getDirection();
	/// symbolic constant for direction where Pac Man is heading
	static const unsigned UP = 0;
	/// symbolic constant for direction where Pac Man is heading
	static const unsigned RIGHT = 1;
	/// symbolic constant for direction where Pac Man is heading
	static const unsigned DOWN= 2;
	/// symbolic constant for direction where Pac Man is heading
	static const unsigned LEFT = 3;
private:
	unsigned m_direction;
	bool m_just_teleported;	// flag for teleporting
};

/**
*	Class for enemies of Pac Man - ghosts, derived from CEntity
*	- driven by given strategies
*/

class CGhost : public CEntity
{
public:
	/// constructor with what the ghost should haunt, color and types of behavior in different modes
	CGhost(CEntity * prey, unsigned color, const CBehavior & chase, const CBehavior & scatter, const CBehavior & frightened);
	/// copy constructor
	CGhost(const CGhost & src);
	/// destructor
	virtual ~CGhost();
	/// move with ghost - ask the logic according to the given mode where to go next
	virtual int move(WINDOW * win, CMap * map, int & mode);
	/// setter for start position
	virtual void setStartPosition(size_t x, size_t y);
	/// draw ghost on the current position ('M' in a proper color)
	virtual void draw(WINDOW * win);
	/// put ghost in the starting state (in starting position and recount routes)
	virtual void reset(WINDOW * win, CMap * map);
	/// change color to the original one
	virtual void changeColor(WINDOW * win);
	/// change mode to frightened and back
	virtual void changeMode(WINDOW * win, CMap * map, int mode);
private:
	unsigned m_color;	// color of ghost
	unsigned m_color_orig;
	CBehavior * m_chase;	// different kinds of behavior
	CBehavior * m_scatter;
	CBehavior * m_frightened;
	CEntity * m_prey;	// what the ghost should haunt
};

#endif // CENTITY_H