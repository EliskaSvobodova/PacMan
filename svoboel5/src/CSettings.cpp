#include <iostream>
#include <ncurses.h>

#include "CSettings.h"

CSettings::CSettings()
	: m_speed_pac_man(0.2), m_speed_ghost(0.5), m_cherry_prob(1), m_scatter_time(10), m_chase_time(30), m_frightened_time(5), m_map_file("examples/map.txt")
{}

CSettings & CSettings::getNewSettings()
{
	showSettings();

	char answer;
	int number;

	while(scanw(" %c", &answer) == 1){
		if(answer != 'y' && answer != 'Y' && answer != 'n' && answer != 'N'){
			clearLine(12);
			mvprintw(12, 1, "Please enter 'y'('Y') or 'n'('N')");
			clearLine(11);
			mvprintw(11, 1, "Do you want to change something? (y/n) : ");
			continue;
		}
		if(answer == 'n' || answer == 'N')
			break;
		clearLine(12);
		mvprintw(12, 1, "And what? Please enter number of the setting : ");
		refresh();
		while(scanw(" %d", &number) != 1 || number > 7 || number < 1){
			clearLine(13);
			mvprintw(13, 1, "Wrong answer, enter a number between 1 and 7");
			clearLine(12);
			mvprintw(12, 1, "And what? Please enter number of the setting : ");
			refresh();
		}
		clearLine(13);
		refresh();
		switch(number){
			case 1:	changePacManSpeed();
					break;
			case 2: changeGhostSpeed();
					break;
			case 3: changeCherryProb();
					break;
			case 4:	changeScatterTime();
					break;
			case 5:	changeChaseTime();
					break;
			case 6:	changeFrightenedTime();
					break;
			case 7:	changeMapFile();
					break;
		}
		clearLine(11);
		mvprintw(11, 1, "Do you want to change something? (y/n) : ");
		refresh();
	}

	clear();
	refresh();
	endwin();

	return *this;
}

void CSettings::showSettings()
{
	initscr();
	clear();
	echo();	// let user's input to be visible
	start_color();

	init_pair(1, 226, COLOR_BLACK); // Yellow1 226, for heading

	attron(COLOR_PAIR(1));
	mvprintw(1, 1, "SETTINGS");
	attroff(COLOR_PAIR(1));

	mvprintw(3, 1, "1) Speed of Pac Man: %.2lf", m_speed_pac_man);
	mvprintw(4, 1, "2) Speed of ghosts: %.2lf", m_speed_ghost);
	mvprintw(5, 1, "3) Probability of cherry's appearing: %u", m_cherry_prob);
	mvprintw(6, 1, "4) Time of Scatter mode: %u", m_scatter_time);
	mvprintw(7, 1, "5) Time of Chase mode: %u", m_chase_time);
	mvprintw(8, 1, "6) Time of Frightened mode: %u", m_frightened_time);
	mvprintw(9, 1, "7) Name of file from which is loaded the map: %s", m_map_file);

	mvprintw(11, 1, "Do you want to change something? (y/n) : ");

	refresh();
}

double CSettings::getPacManSpeed()
{
	return m_speed_pac_man;
}

double CSettings::getGhostSpeed()
{
	return m_speed_ghost;
}

int CSettings::getCherryProb()
{
	return m_cherry_prob;
}

unsigned CSettings::getScatterTime()
{
	return m_scatter_time;
}

unsigned CSettings::getChaseTime()
{
	return m_chase_time;
}

unsigned CSettings::getFrightenedTime()
{
	return m_frightened_time;
}

char * CSettings::getMapFile()
{
	return m_map_file;
}


void CSettings::changePacManSpeed()
{
	double tmp;
	while(1){
		clearLine(13);
		mvprintw(13, 1, "New speed of Pac Man : ");
		refresh();
		if(scanw(" %lf", &tmp) != 1){
			clearLine(14);
			mvprintw(14, 1, "Please enter a number!");
			clearLine(13);
			mvprintw(13, 1, "New speed of Pac Man : ");
			refresh();
			continue;
		}
		if(tmp <= 0.001 || tmp > 3){
			clearLine(14);
			mvprintw(14, 1, "That isn't a good idea... Try something between 0.001 and 3");
			clearLine(13);
			mvprintw(13, 1, "New speed of Pac Man : ");
			refresh();
			continue;
		}
		break;
	}
	m_speed_pac_man = tmp;
	clearLine(12);
	clearLine(13);
	clearLine(14);
	clearLine(3);
	mvprintw(3, 1, "1) Speed of Pac Man: %.2lf", m_speed_pac_man);
	refresh();
}

void CSettings::changeGhostSpeed()
{
	double tmp;
	while(1){
		clearLine(13);
		mvprintw(13, 1, "New speed of Ghosts : ");
		refresh();
		if(scanw(" %lf", &tmp) != 1){
			clearLine(14);
			mvprintw(14, 1, "Please enter a number!");
			clearLine(13);
			mvprintw(13, 1, "New speed of Ghosts : ");
			refresh();
			continue;
		}
		if(tmp <= 0.001 || tmp > 3){
			clearLine(14);
			mvprintw(14, 1, "That isn't a good idea... Try something between 0.001 and 3");
			clearLine(13);
			mvprintw(13, 1, "New speed of Ghosts : ");
			refresh();
			continue;
		}
		break;
	}
	m_speed_ghost = tmp;
	clearLine(12);
	clearLine(13);
	clearLine(14);
	clearLine(4);
	mvprintw(4, 1, "2) Speed of ghosts: %.2lf", m_speed_ghost);
	refresh();
}

void CSettings::changeCherryProb()
{
	unsigned tmp;
	
	while(1){
		clearLine(13);
		mvprintw(13, 1, "New probability of cherry appearing : ");
		refresh();
		if(scanw(" %u", &tmp) != 1){
			clearLine(14);
			mvprintw(14, 1, "Please enter a number!");
			clearLine(13);
			mvprintw(13, 1, "New probability of cherry appearing : ");
			refresh();
			continue;
		}
		if(tmp < 0 || tmp > 10){
			clearLine(14);
			mvprintw(14, 1, "That isn't a good idea... Try something between 0 and 10");
			clearLine(13);
			mvprintw(13, 1, "New probability of cherry appearing : ");
			refresh();
			continue;
		}
		break;
	}
	m_cherry_prob = tmp;
	clearLine(12);
	clearLine(13);
	clearLine(14);
	clearLine(5);
	mvprintw(5, 1, "3) Probability of cherry's appearing: %u", m_cherry_prob);
	refresh();
}

void CSettings::changeScatterTime()
{
	unsigned tmp;
	
	while(1){
		clearLine(13);
		mvprintw(13, 1, "New time of Scatter mode : ");
		refresh();
		if(scanw(" %u", &tmp) != 1){
			clearLine(14);
			mvprintw(14, 1, "Please enter a number!");
			clearLine(13);
			mvprintw(13, 1, "New time of Scatter mode : ");
			refresh();
			continue;
		}
		if(tmp < 0 || tmp > 1000){
			clearLine(14);
			mvprintw(14, 1, "That isn't a good idea... Try something between 0 and 1000");
			clearLine(13);
			mvprintw(13, 1, "New time of Scatter mode : ");
			refresh();
			continue;
		}
		break;
	}
	m_scatter_time = tmp;
	clearLine(12);
	clearLine(13);
	clearLine(14);
	clearLine(6);
	mvprintw(6, 1, "4) Time of Scatter mode: %u", m_scatter_time);
	refresh();
}

void CSettings::changeChaseTime()
{
	unsigned tmp;
	
	while(1){
		clearLine(13);
		mvprintw(13, 1, "New time of Chase mode : ");
		refresh();
		if(scanw(" %u", &tmp) != 1){
			clearLine(14);
			mvprintw(14, 1, "Please enter a number!");
			clearLine(13);
			mvprintw(13, 1, "New time of Chase mode : ");
			refresh();
			continue;
		}
		if(tmp < 0 || tmp > 1000){
			clearLine(14);
			mvprintw(14, 1, "That isn't a good idea... Try something between 0 and 1000");
			clearLine(13);
			mvprintw(13, 1, "New time of Chase mode : ");
			refresh();
			continue;
		}
		break;
	}
	m_chase_time = tmp;
	clearLine(12);
	clearLine(13);
	clearLine(14);
	clearLine(7);
	mvprintw(7, 1, "5) Time of Chase mode: %u", m_chase_time);
	refresh();
}

void CSettings::changeFrightenedTime()
{
	unsigned tmp;
	
	while(1){
		clearLine(13);
		mvprintw(13, 1, "New time of Frightened mode : ");
		refresh();
		if(scanw(" %u", &tmp) != 1){
			clearLine(14);
			mvprintw(14, 1, "Please enter a number!");
			clearLine(13);
			mvprintw(13, 1, "New time of Frightened mode : ");
			refresh();
			continue;
		}
		if(tmp < 0 || tmp > 1000){
			clearLine(14);
			mvprintw(14, 1, "That isn't a good idea... Try something between 0 and 1000");
			clearLine(13);
			mvprintw(13, 1, "New time of Frightened mode : ");
			refresh();
			continue;
		}
		break;
	}
	m_frightened_time = tmp;
	clearLine(12);
	clearLine(13);
	clearLine(14);
	clearLine(8);
	mvprintw(8, 1, "6) Time of Frightened mode: %u", m_frightened_time);
	refresh();
}

void CSettings::changeMapFile()
{	
	while(1){
		clearLine(13);
		mvprintw(13, 1, "New file with the map : ");
		refresh();
		if(scanw(" %30s", m_map_file) != 1){
			clearLine(14);
			mvprintw(14, 1, "Please enter a name of file!");
			clearLine(13);
			mvprintw(13, 1, "New file with the map : ");
			refresh();
			continue;
		}
		break;
	}

	clearLine(12);
	clearLine(13);
	clearLine(14);
	clearLine(9);
	mvprintw(9, 1, "7) Name of file from which is loaded the map: %s", m_map_file);
	refresh();
}

void CSettings::clearLine(int line)
{
	move(line, 0);
	clrtoeol();	// clear to end of line
}