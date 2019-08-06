#ifndef CGAME_H
#define CGAME_H

#include "CSettings.h"
#include "CMap.h"
#include "CEntity.h"
#include "CBehavior.h"

class CEntity; // forward declaration

class CGame
{
public:
	/// constructor getting settings for the game
	CGame(CSettings * settings);
	/// destructor
	~CGame();
	/// starts the game and keeps it playing
	void startGame();
	/// getter for settings, returns pointer to settings
	CSettings * getSettings();
	/// symbolic constatnt for modes
	static const int CHASE = 0;
	/// symbolic constatnt for modes
	static const int SCATTER = 1;
	/// symbolic constatnt for modes
	static const int FRIGHTENED = 2;
	/// symbolic constant for colors
	static const unsigned PACMAN_COLOR = 1;
	/// symbolic constant for colors
	static const unsigned WALL_COLOR = 2;
	/// symbolic constant for colors
	static const unsigned TELEPORT_COLOR = 3;
	/// symbolic constant for colors
	static const unsigned GATE_COLOR = 4;
	/// symbolic constant for colors
	static const unsigned RED_COLOR = 5;
	/// symbolic constant for colors
	static const unsigned PINK_COLOR = 6;
	/// symbolic constant for colors
	static const unsigned BLUE_COLOR = 7;
	/// symbolic constant for colors
	static const unsigned ORANGE_COLOR = 8;
	/// symbolic constant for colors
	static const unsigned FRIGHTENED_COLOR = 9;
	/// symbolic constant for colors
private:
	// constants for entities
	const int PACMAN_INDEX = 0;
	const int RED_GHOST_INDEX = 1;
	const int PINK_GHOST_INDEX = 2;
	const int BLUE_GHOST_INDEX = 3;
	const int ORANGE_GHOST_INDEX = 4;

	WINDOW *m_game_window;	// for the maze
	WINDOW *m_header_window;	// for score
	int m_mode; // current mode of the game - chase / scatter / frightened
	unsigned m_score; // current score
	int m_lives; // number of remaining lives, 0 -> game over
	CSettings * m_settings; // concrete settings for this game
	CMap * m_map;	// map for the game
	vector<CEntity *> m_entities;

	// change direction of pac man
	void turnPacMan(int key);
	// draws map, coins, cherries, entities
	int getReady();
	// handle frightened mode
	void frightenedMode(int prev_mode, int & start_frightened);
	// if pac man was catched, what next?
	int catchedPacMan();
	// add cherry to a random place
	void addCherry();
	// checks whether player is catched by ghosts
	int catched();
	// when player wins the game
	void winner();
	// player lost
	void loser();
	// player has lost one life
	void nextTry();
	// handle pac man's moving
	int pacManMove(int & prev_mode, int & start_frightened);
};

#endif // CGAME_H