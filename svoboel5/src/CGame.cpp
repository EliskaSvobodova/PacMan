#include <ncurses.h>
#include <time.h>
#include <iostream>

#include "CGame.h"

CGame::CGame(CSettings * settings)
	: m_settings(settings)
{
	// create new instance for pac man
	m_entities.push_back(new CPacMan());
	
	// create ghosts and define their modes - chase sccater frightened
	m_entities.push_back(new CGhost(m_entities.at(PACMAN_INDEX), RED_COLOR, CAggresive(), CScatter(CScatter::RIGHT_UP), CRandomOutOfWay())); // red
	m_entities.push_back(new CGhost(m_entities.at(PACMAN_INDEX), PINK_COLOR, CAmbush(), CScatter(CScatter::LEFT_UP), CRandomOutOfWay())); // pink
	m_entities.push_back(new CGhost(m_entities.at(PACMAN_INDEX), BLUE_COLOR, CPatrol(), CScatter(CScatter::RIGHT_DOWN), CRandomOutOfWay())); // blue
	m_entities.push_back(new CGhost(m_entities.at(PACMAN_INDEX), ORANGE_COLOR, CRandomOutOfWay(), CScatter(CScatter::LEFT_DOWN), CRandomOutOfWay())); // orange

	m_score = 0;
	m_mode = SCATTER;
	m_lives = 3;
}

CGame::~CGame()
{
	delwin(m_game_window);
	delwin(m_header_window);
	// don't destroy m_settings, they are just borrowed from main
	endwin();
	for(auto i : m_entities)
		delete i;
}

void CGame::startGame()
{
	if(getReady() != 0)
		return;

	wtimeout(m_game_window, 0);	// don't wait for user to press key
	int start_pacman, start_ghosts, start_mode, start_frightened;
	int prev_mode, tmp;

	start_pacman = start_ghosts = start_mode = clock();

	while(1){
		if(((clock()-start_pacman) / (double)CLOCKS_PER_SEC) > m_settings->getPacManSpeed()){
			if((tmp = pacManMove(prev_mode, start_frightened)) == -1 || tmp == 1){
				delete m_map;
				return;	// win or lose
			}
			else if(tmp == 0)
				continue;	// next try
			start_pacman = clock();	// nothing happend
		}
		if(((clock()-start_ghosts)/(double)CLOCKS_PER_SEC) > m_settings->getGhostSpeed()){
			for(size_t i = 1; i < m_entities.size(); ++i)
				m_entities.at(i)->move(m_game_window, m_map, m_mode);
			if(m_mode == FRIGHTENED){
				frightenedMode(prev_mode, start_frightened);
			} else if(catched() != -1){	
				if(catchedPacMan() == 1)	
					continue;
				else{
					delete m_map;
					return;
				}
			}
			start_ghosts = clock();
		}
		if(m_mode == CGame::SCATTER && ((clock()-start_mode) / (double)CLOCKS_PER_SEC) > m_settings->getScatterTime()){
			start_mode = clock();
			m_mode = CGame::CHASE;
			for(size_t i = 1; i < m_entities.size(); ++i){
				m_entities.at(i)->changeMode(m_game_window, m_map, m_mode);
			}
		}
		if(m_mode == CGame::CHASE && ((clock()-start_mode) / (double)CLOCKS_PER_SEC) > m_settings->getChaseTime()){
			start_mode = clock();
			m_mode = CGame::SCATTER;
			for(size_t i = 1; i < m_entities.size(); ++i){
				m_entities.at(i)->changeMode(m_game_window, m_map, m_mode);
			}
		}
	}
}

int CGame::getReady()
{
	// load the map - the static parts - the maze
	for(int i = 5; i >= 0; --i){
		try{	// check if the file is fine
			m_map = new CMap(m_settings->getMapFile());
		} catch (const FileFailException & e) {
			std::cout << e.message() << std::endl;
			std::cout << "Attempts left before returning to the main menu: " << i << std::endl;
			getchar();
			if(i == 0)
				return 1;
			continue;
		}
		break;
	}

	// handle moving entities - their start positions
	for(auto i : m_map->m_other){
		switch(i.first){
			case '@':	m_entities.at(PACMAN_INDEX)->setStartPosition(i.second.first, i.second.second);	// pac man
						break;
			case 'R':	m_entities.at(RED_GHOST_INDEX)->setStartPosition(i.second.first, i.second.second);	// ghosts
						break;
			case 'P':	m_entities.at(PINK_GHOST_INDEX)->setStartPosition(i.second.first, i.second.second);
						break;
			case 'B':	m_entities.at(BLUE_GHOST_INDEX)->setStartPosition(i.second.first, i.second.second);
						break;
			case 'O':	m_entities.at(ORANGE_GHOST_INDEX)->setStartPosition(i.second.first, i.second.second);
						break;
			default:	break;	// ignor everything else
		}
	}

	initscr();
	clear();
	cbreak();
	keypad(stdscr, true);
	curs_set(0);	// hide cursor
	start_color();

	// definition of colors
	init_pair(PACMAN_COLOR, 226, COLOR_BLACK); // Yellow1 226
	init_pair(WALL_COLOR, COLOR_BLACK, 31); // DeepSkyBlue3
	init_pair(TELEPORT_COLOR, 249, COLOR_BLACK); // Grey11
	init_pair(GATE_COLOR, COLOR_BLACK, 216); // LightSalmon1
	init_pair(RED_COLOR, 196, COLOR_BLACK); // Red1
	init_pair(PINK_COLOR, 205, COLOR_BLACK); // HotPink
	init_pair(BLUE_COLOR, 31, COLOR_BLACK);
	init_pair(ORANGE_COLOR, 214, COLOR_BLACK); // Orange1
	init_pair(FRIGHTENED_COLOR, 21, COLOR_BLACK); // Blue1

	// create windows
	m_game_window = newwin(m_map->getHeight() + 2, m_map->getWidth() + 2, 3, 1);
	keypad(m_game_window, true);
	m_header_window = newwin(1, m_map->getWidth() + 2, 1, 1);

	// draw everything
	m_map->draw(m_game_window);
	for(auto i : m_entities)
		i->draw(m_game_window);
	mvwprintw(m_header_window, 0, 0, "SCORE: 0");
	mvwprintw(m_header_window, 0, 12, "LIVES: 3");
	wrefresh(m_header_window);

	return 0;
}

void CGame::winner()
{
	mvwprintw(m_game_window, m_map->getHeight() / 2 - 1, m_map->getWidth() / 2 - 3 + 1, "        ");
	mvwprintw(m_game_window, m_map->getHeight() / 2, m_map->getWidth() / 2 - 3 + 1, " WINNER ");
	mvwprintw(m_game_window, m_map->getHeight() / 2 + 1, m_map->getWidth() / 2 - 3 + 1, "        ");
	wrefresh(m_game_window);

	while(wgetch(m_game_window) != 10);
}

void CGame::loser()
{
	mvwprintw(m_game_window, m_map->getHeight() / 2 - 1, m_map->getWidth() / 2 - 3 + 1, "       ");
	mvwprintw(m_game_window, m_map->getHeight() / 2, m_map->getWidth() / 2 - 3 + 1, " LOSER ");
	mvwprintw(m_game_window, m_map->getHeight() / 2 + 1, m_map->getWidth() / 2 - 3 + 1, "       ");

	wrefresh(m_game_window);

	while(wgetch(m_game_window) != 10);
}

// returns number of the succesful ghost or -1 if none of them were succesful
int CGame::catched()
{
	for(size_t i = 1; i < m_entities.size(); ++i){
		if(m_entities.at(0)->getX() == m_entities.at(i)->getX() && m_entities.at(0)->getY() == m_entities.at(i)->getY()){
			return i;
		}
	}

	return -1;
}

void CGame::nextTry()
{
	for(auto i : m_entities){
		m_map->getElement(i->getX(), i->getY())->draw(i->getX()+1, i->getY()+1, m_game_window);
		i->reset(m_game_window, m_map);
		i->draw(m_game_window);
	}
	while(wgetch(m_game_window) != 10);
}

void CGame::turnPacMan(int key)
{
	switch(key){
		case KEY_UP:	m_entities.at(PACMAN_INDEX)->changeDirection(CPacMan::UP);
						break;
		case KEY_RIGHT:	m_entities.at(PACMAN_INDEX)->changeDirection(CPacMan::RIGHT);
						break;
		case KEY_DOWN:	m_entities.at(PACMAN_INDEX)->changeDirection(CPacMan::DOWN);
						break;
		case KEY_LEFT:	m_entities.at(PACMAN_INDEX)->changeDirection(CPacMan::LEFT);
						break;
	}
}

void CGame::frightenedMode(int prev_mode, int & start_frightened)
{
	int catched_ghost;

	if(prev_mode != FRIGHTENED){
		for(size_t i = 1; i < m_entities.size(); ++i){
			m_entities.at(i)->changeMode(m_game_window, m_map, m_mode);
		}
		start_frightened = clock();
	}
	if((clock()-start_frightened)/(double)CLOCKS_PER_SEC > m_settings->getFrightenedTime()){
		m_mode = CHASE;
		for(size_t i = 1; i < m_entities.size(); ++i){
			m_entities.at(i)->changeMode(m_game_window, m_map, m_mode);
		}
	}
	if((catched_ghost = catched()) != -1){
		m_entities.at(catched_ghost)->reset(m_game_window, m_map);
		m_score += 100;
	}
}

// returns 1 if user has next try, -1 if game over
int CGame::catchedPacMan()
{
	--m_lives;
	mvwprintw(m_header_window, 0, 19, "%u", m_lives);
	wrefresh(m_header_window);
	if(m_lives > 0){
		nextTry();
		return 1;
	} else {
		loser();
		return -1;
	}
}

void CGame::addCherry()
{
	size_t x = rand() % (m_map->getWidth() - 1);
	size_t y = rand() % (m_map->getHeight() - 1);

	// pick a place where is no bonus and I can put a bonus there
	while(m_map->isBonus(x, y) != 0){
		x = rand() % (m_map->getWidth() - 1);
		y = rand() % (m_map->getHeight() - 1);
	}

	m_map->putBonus(m_game_window, x, y, CCherry());
}

CSettings * CGame::getSettings()
{
	return m_settings;
}

int CGame::pacManMove(int & prev_mode, int & start_frightened)
{
	// change direction of pac man if a key was pressed
	turnPacMan(wgetch(m_game_window));
	// move pac man and add score
	m_score += m_entities.at(PACMAN_INDEX)->move(m_game_window, m_map, m_mode);

	if(m_mode == FRIGHTENED){
		frightenedMode(prev_mode, start_frightened);
	} else if(catched() != -1){
		if(catchedPacMan() == 1)
			return 0; // next_try
		else
			return -1;	// game over
	}
	prev_mode = m_mode;
	mvwprintw(m_header_window, 0, 7, "%u", m_score);	// draw curent score
	wrefresh(m_header_window);
	// done?
	if(m_map->allCoinsPicked()){
		winner();
		return 1;
	}
	// cherry
	if(rand() % 100 <= m_settings->getCherryProb())
		addCherry();

	return 2;
}