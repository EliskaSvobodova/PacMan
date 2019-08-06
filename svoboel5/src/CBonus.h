#ifndef CBONUS_H
#define CBONUS_H

#include <cstddef>
#include <ncurses.h>

/**
*	Abstract class for different kinds of bonuses
*	- it holds the score and returns it, when getScore() is called
*	- has abstract functions for drawing bonus on the screen and copying method
*/

class CBonus
{
public:
	/// constuctor, will be called from derived class with the right value of score
	CBonus(unsigned score);
	/// copy constructor
	CBonus(const CBonus & src);
	/// destructor
	virtual ~CBonus();
	/// draw the right bonus in the given position in the given window
	virtual void drawBonus(size_t y, size_t x, WINDOW * win) = 0;
	/// copy function for polymorphism
	virtual CBonus * copy() = 0;
	/// returns score
	unsigned getScore();
protected:
	/// value of the instance of the bonus
	unsigned m_score;
};

/**
*	Class for Cherry, derived from CBonus
*	- cheries appear randomly in the map and are for more points
*/

class CCherry : public CBonus
{
public:
	/// constuctor
	CCherry();
	/// copy constructor
	CCherry(const CCherry & src);
	/// destructor
	virtual ~CCherry();
	/// draws cherry (red '*') into the map
	virtual void drawBonus(size_t y, size_t x, WINDOW * win);
	/// copy function for polymorphism
	virtual CBonus * copy();
	/// symbolic constat for how much points will user get for picking the bonus up
	static const unsigned CHERRY_POINTS = 100;
};

/**
*	Class for Coin, derived from CBonus
*	- basic type of bonus, player has to pick them all in order to win the game
*/

class CCoin : public CBonus
{
public:
	/// constuctor
	CCoin();
	/// copy constructor
	CCoin(const CCoin & src);
	/// destructor
	virtual ~CCoin();
	/// draws coin (yellow '.') into the map
	virtual void drawBonus(size_t y, size_t x, WINDOW * win);
	/// copy function for polymorphism
	virtual CBonus * copy();
	/// symbolic constat for how much points will user get for picking the bonus up
	static const unsigned COIN_POINTS = 10;
};

/**
*	Class for Shield, derived from CBonus
*	- there is a small number of them in the map in the beggining
*	- when picked, mode changes to frightened and ghosts are vulnerable
*/

class CShield : public CBonus
{
public:
	/// constuctor
	CShield();
	/// copy constructor
	CShield(const CShield & src);
	/// destructor
	virtual ~CShield();
	/// draws shield (red 'o') into the map
	virtual void drawBonus(size_t y, size_t x, WINDOW * win);
	/// copy function for polymorphism
	virtual CBonus * copy();
	/// symbolic constat for how much points will user get for picking the bonus up
	static const unsigned SHIELD_POINTS = 50;
};

#endif // CBONUS_H