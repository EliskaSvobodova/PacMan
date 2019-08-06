#include <ncurses.h>
#include <vector>
#include <string>

#include "CMenu.h"

using namespace std;

CMenu::CMenu()
	: m_chosen(0)	// the first one will be chosen
{
	// put options into the menu
	m_options.push_back("START\n");
	m_options.push_back("SETTINGS\n");
	m_options.push_back("END\n");
}

size_t CMenu::chooseOption()
{
	initscr();
	noecho();	// don't show input characters
	cbreak();	// read characters immediately
	keypad(stdscr, true); // treat arrow keys differently
	start_color();
	curs_set(0); // invisible cursor
	init_pair(1, 226, COLOR_BLACK); // pac man, 226 is code for Yellow1

	showMenu(m_chosen);

	while(1){
		int ch = getch();
		switch(ch){
			case KEY_UP:	m_chosen = (m_chosen == 0 ? m_options.size() - 1 : (m_chosen - 1)); // up, or to the last element
							break;
			case KEY_DOWN:	m_chosen = (m_chosen == m_options.size() - 1 ? 0 : (m_chosen + 1)); // down, or to the first element
							break;
			case 10:		clear();	// end
							refresh();
							endwin();
							return m_chosen;
			default:		break;
		}
		showMenu(m_chosen);
	}
}

// draws menu on the screen
void CMenu::showMenu(size_t highlight)
{
	clear();
	attron(COLOR_PAIR(1));
	mvprintw(0, 0, "PAC MAN"); // title will be in yellow
	attroff(COLOR_PAIR(1));

	int x = 1, y = 3;
	for(size_t i = 0; i < m_options.size(); ++i){
		if(highlight == i){ // marks the currently chosen option with *
			mvprintw(y, 0, "*");
			mvprintw(y, x, m_options.at(i).c_str());
			mvprintw(y, x + m_options.at(i).size()-1, "*");
		} else {
			mvprintw(y, x, m_options.at(i).c_str());
		}
		++y;
	}
	
	refresh();
}