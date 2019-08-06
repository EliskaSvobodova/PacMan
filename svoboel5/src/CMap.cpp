#include <ncurses.h>
#include <fstream>
#include <sstream>
#include <vector>

#include "CMap.h"
#include "CGame.h"

CMap::CMap(const char * file_name)
{
	ifstream map_file;
	map_file.open(file_name, ios::in);

	if(map_file.fail()){
		throw FileFailException(FileFailException::FILE_OPEN);
	}

	vector<CTile *> tmp;	// for temporary saving created tiles from one line
	string line;
	size_t i, j, width = 0;
	size_t cntr = 0;
	size_t num_of_teleports = 0;
	size_t t_x, t_y, t2_x, t2_y;	// to remember where was the first teleport
	bool pac_man, red, pink, blue, orange;
	pac_man = red = pink = blue = orange = false;

	for(i = 0; getline(map_file, line); ++i){	// for each line in the file
		if(width == 0){
			width = line.size();	// to get the width of the maze
		} else if(line.size() != width){
			map_file.close();
			throw FileFailException(FileFailException::WIDTH);
		}
		for(j=0; j < line.size(); ++j){
			switch(line.at(j)){
				case '#': tmp.push_back(addTile(CWall(j, i)));
						  break;
				case 'x': tmp.push_back(addTile(CSpace(j, i, CShield())));
						  break;
				case '.': tmp.push_back(addTile(CSpace(j, i, CCoin())));
						  ++cntr;
						  break;
				case ' ': tmp.push_back(addTile(CSpace(j, i)));
						  break;
				case 'T': tmp.push_back(addTile(CTeleport(j, i)));
						  if(num_of_teleports == 0){
						  	t_x = j;
						  	t_y = i;
						  	++num_of_teleports;
						  } else if(num_of_teleports == 1){
						  	t2_x = j;
						  	t2_y = i;
						  	++num_of_teleports;
						  }
						  break;
				case '@': pac_man = true;
						  tmp.push_back(addTile(CSpace(j, i)));	// for other symbols
						  m_other.push_back(make_pair(line.at(j), make_pair(j, i)));
						  break;
				case 'R': red = true;
						  tmp.push_back(addTile(CSpace(j, i)));	// for other symbols
						  m_other.push_back(make_pair(line.at(j), make_pair(j, i)));
						  break;
				case 'B': blue = true;
						  tmp.push_back(addTile(CSpace(j, i)));	// for other symbols
						  m_other.push_back(make_pair(line.at(j), make_pair(j, i)));
						  break;
				case 'P': pink = true;
						  tmp.push_back(addTile(CSpace(j, i)));	// for other symbols
						  m_other.push_back(make_pair(line.at(j), make_pair(j, i)));
						  break;
				case 'O': orange = true;
						  tmp.push_back(addTile(CSpace(j, i)));	// for other symbols
						  m_other.push_back(make_pair(line.at(j), make_pair(j, i)));
						  break;
				default:  break;
			}
		}
		m_map.push_back(tmp);	// save the line
		tmp.clear();
	}

	map_file.close();

	if(num_of_teleports != 2){
		throw FileFailException(FileFailException::TELEPORT);
	}

	if(!pac_man || !red || !pink || !blue || !orange){
		throw FileFailException(FileFailException::ENTITIES);
	}

	m_map.at(t_y).at(t_x)->validateTeleports(t2_x, t2_y);
	m_map.at(t2_y).at(t2_x)->validateTeleports(t_x, t_y);

	m_map.at(t_y).at(t_x)->addNeighbour(m_map.at(t2_y).at(t2_x));
	m_map.at(t2_y).at(t2_x)->addNeighbour(m_map.at(t_y).at(t_x));

	m_height = m_map.size();
	m_width = width;
	m_num_coins = cntr;

	connect();
}

CMap::CMap(const CMap & src)
	: m_width(src.m_width), m_height(src.m_height), m_num_coins(src.m_num_coins)
{
	size_t i, j;
	for(i = 0; i < m_map.size(); ++i){
		for(j = 0; j < m_map.at(i).size(); ++j)
			delete m_map.at(i).at(j);
		m_map.clear();
	}
	m_map.clear();

	vector<CTile *> tmp;
	for(i = 0; i < src.m_map.size(); ++i){
		for(j = 0; j < src.m_map.size(); ++j){
			tmp.push_back(src.m_map.at(i).at(j)->copy());
		}
		m_map.push_back(tmp);
		tmp.clear();
	}
}

CMap::~CMap()
{
	for(size_t i = 0; i < m_map.size(); ++i){
		for(size_t j = 0; j < m_map.at(i).size(); ++j){
			delete m_map.at(i).at(j);
		}
	}
}

bool CMap::freeToGo(size_t x, size_t y)
{
	if(x >= m_width || y >= m_height)
		return false;
	return m_map.at(y).at(x)->freeToGo();
}

size_t CMap::getWidth()
{
	return m_width;
}

size_t CMap::getHeight()
{
	return m_height;
}

void CMap::draw(WINDOW * win)
{
	box(win, 0, 0);
	for(size_t i = 0; i < m_map.size(); ++i){
		for(size_t j = 0; j < m_map.at(i).size(); ++j){
			m_map.at(i).at(j)->draw(j+1, i+1, win);	// draw all Tiles
		}
	}
	wrefresh(win);
}

void CMap::connect()
{
	for(size_t i = 0; i < m_map.size(); ++i){
		for(size_t j = 0; j < m_map.at(i).size(); ++j){
			// is current node connectable?
			if(m_map.at(i).at(j)->freeToGo()){
				// if there is some place to go from the current tile, add it to the list of neighbours
				// up
				if(i != 0 && m_map.at(i-1).at(j)->freeToGo())
					m_map.at(i).at(j)->addNeighbour(m_map.at(i-1).at(j));
				// down
				if(i != m_height - 1 && m_map.at(i+1).at(j)->freeToGo())
					m_map.at(i).at(j)->addNeighbour(m_map.at(i+1).at(j));
				// left
				if(j != 0 && m_map.at(i).at(j-1)->freeToGo())
					m_map.at(i).at(j)->addNeighbour(m_map.at(i).at(j-1));
				// right
				if(j != m_width - 1 && m_map.at(i).at(j+1)->freeToGo())
					m_map.at(i).at(j)->addNeighbour(m_map.at(i).at(j+1));
			}
		}
	}
}

CTile * CMap::addTile(const CWall & wall)
{
	CTile * tmp = new CWall(wall);
	return tmp;
}

CTile * CMap::addTile(const CTeleport & teleport)
{
	CTile * tmp = new CTeleport(teleport);
	return tmp;
}

CTile * CMap::addTile(const CSpace & space)
{
	CTile * tmp = new CSpace(space);
	return tmp;
}

unsigned CMap::grabBonus(size_t x, size_t y, int & mode)
{
	unsigned score = m_map.at(y).at(x)->pickAndGetScore();
	if(score == CCoin::COIN_POINTS)
		--m_num_coins;
	if(score == CShield::SHIELD_POINTS)
		mode = CGame::FRIGHTENED;
	return score;
}

unsigned CMap::countNeighbours(size_t x, size_t y)
{
	return m_map.at(y).at(x)->getNumNeighbours();
}

CTile * CMap::getElement(size_t x, size_t y)
{
	return m_map.at(y).at(x);
}

list<CTile *> CMap::getNeighbours(size_t x, size_t y)
{
	return m_map.at(y).at(x)->getListOfNeighbours();
}

bool CMap::allCoinsPicked()
{
	return (m_num_coins == 0) ? true : false;
}

int CMap::isBonus(size_t x, size_t y)
{
	return m_map.at(y).at(x)->isBonus();
}

void CMap::putBonus(WINDOW * win, size_t x, size_t y, const CCherry & bonus)
{
	m_map.at(y).at(x)->putBonus(bonus);
	m_map.at(y).at(x)->draw(x+1, y+1, win);
}