#ifndef CSETTINGS_H
#define CSETTINGS_H

#include "CMap.h"

/**
*	Class with all setting
*	- shows settings, gets the input from the user and saves new values
*	- user can choose speed of Pac Man and ghosts and how much probable will be appearing of a cherry
*/

class CSettings
{
public:
	/// constructor, sets default values
	CSettings();
	/// shows settings and gets input from the user
	CSettings & getNewSettings();
	/// getter for Pac Man's speed
	double getPacManSpeed();
	/// getter for ghost's speed
	double getGhostSpeed();
	/// getter for probability of cherry appearing
	int getCherryProb();
	/// getter for time of scatter mode
	unsigned getScatterTime();
	/// getter for time of chase mode
	unsigned getChaseTime();
	/// getter for time of frightened mode
	unsigned getFrightenedTime();
	/// getter for file with the map
	char * getMapFile();
private:
	double m_speed_pac_man;
	double m_speed_ghost;
	unsigned m_cherry_prob;	// default = 1%
	unsigned m_scatter_time;
	unsigned m_chase_time;
	unsigned m_frightened_time;
	char m_map_file[31];

	// draws menu for changing settings
	void showSettings();
	// handlers for getting new values
	void changePacManSpeed();
	void changeGhostSpeed();
	void changeCherryProb();
	void changeScatterTime();
	void changeChaseTime();
	void changeFrightenedTime();
	void changeMapFile();
	// help function that will clear the line
	void clearLine(int line);
};

#endif // CSETTINGS_H