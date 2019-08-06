#ifndef CMAP_h
#define CMAP_h

#include <vector>
#include <string>

#include "CTile.h"

/**
*	Class for the map of maze
*	- loads map from a file
*	- creates a graph from it
*	- draws the map and takes care of it
*	- symbols for different things in the loaded map:
*		* wall = '#'
*		* shield = 'x'
*		* space = ' ' (without any bonus)
*		* coin = '.'
*		* teleport = 'T'
*		* starting point of ghosts = 'R'(red ghost), 'P'(pink ghost), 'B'(blue ghost), 'O'(orange ghost)
*		* starting point of pacman = '@'
*/

using namespace std;

class CMap
{
public:
	/// constructor, loads map from the given file
	CMap(const char * file_name);
	/// copy constructor
	CMap(const CMap & src);
	/// destructor
	~CMap();
	/// draws the maze to the given window
	void draw(WINDOW * win);
	/// getter for width
	size_t getWidth();
	/// getter for height
	size_t getHeight();
	/// pick a bonus on given position - delete it and return the score
	unsigned grabBonus(size_t x, size_t y, int & mode);
	/// is there a bonus?
	int isBonus(size_t x, size_t y);
	/// put a bonus to the map
	void putBonus(WINDOW * win, size_t x, size_t y, const CCherry & bonus);
	/// look if the entity can go to given position
	bool freeToGo(size_t x, size_t y);
	/// get number of neighbours of the given tile
	unsigned countNeighbours(size_t x, size_t y);
	/// get list of neighbours of the tile
	list<CTile *> getNeighbours(size_t x, size_t y);
	/// get poiter to the element
	CTile * getElement(size_t x, size_t y);
	/// was already all coins picked?
	bool allCoinsPicked();
	/// for entities to get their starting position from a file (while reading it in the constructor) - <symbol, <x, y>>
	vector<pair<char, pair<size_t, size_t>>> m_other;
private:
	vector<vector<CTile *>> m_map;	// 2D array for the maze
	size_t m_width; // size of the maze
	size_t m_height;
	size_t m_num_coins;	// number of remaining coins

	// for adding different types of tile
	CTile * addTile(const CWall & wall);
	CTile * addTile(const CTeleport & teleport);
	CTile * addTile(const CSpace & space);
	// create a graph, connect nodes together
	void connect();
};

class FileFailException
{
public:
	FileFailException(int code)
	{
		switch(code){
			case FILE_OPEN:	m_text = "Cannot open file with the map! Please, check the input file and press any key when ready.";
							break;
			case TELEPORT:	m_text = "Wrong number of teleports in the map! There must be 2 (two 'T' in the map)! Please, check it and press any key when ready.";
							break;
			case WIDTH:		m_text = "Maze in the file has wrong size! All lines has to have the same number of characters. Please, add spaces when needed and press any key when ready.";
							break;
			case ENTITIES:	m_text = "Wrong number of entities in the map! In the maze has to be Pac Man ('@') and four ghosts ('R', 'P', 'B', 'O'). Please, check it and press any key when ready.";
							break;
			default:		m_text = "Unknown error";
							break;
		}
	}
	string message() const
	{
		return m_text;
	}
	static const int FILE_OPEN = 1;
	static const int TELEPORT = 2;
	static const int WIDTH = 3;
	static const int ENTITIES = 4;
private:
	string m_text;
};

#endif // CMAP_H