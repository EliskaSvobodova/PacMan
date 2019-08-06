#ifndef CMENU_H
#define CMENU_H

#include <vector>
#include <string>

/**
*	Class for showing a menu
*	- it draws a menu on the screen a marks the curently chosen option
*	- it lets user to choose an option and returns it
*/

class CMenu
{
public:
	/// constructor
	CMenu();
	/// draws menu, marks options as user presses keys and returns the chosen option
	size_t chooseOption();
	/// option of the menu
	static const size_t START = 0;
	/// option of the menu
	static const size_t SETTINGS = 1;
	/// option of the menu
	static const size_t END = 2;
private:
	// draws menu and marks the chosen option
	void showMenu(size_t highlight);

	std::vector<std::string> m_options;	// all options
	size_t m_chosen;	// curently chosen option
};

#endif // CMENU_H