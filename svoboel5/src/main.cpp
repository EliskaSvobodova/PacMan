#include "CMenu.h"
#include "CGame.h"
#include "CSettings.h"

int main(void)
{
	// initialization of the game
	CMenu menu;
	CSettings * settings = new CSettings();;
	CGame * game = new CGame(settings);
	bool play_again = true;
	// game itself
	while(play_again){
		switch(menu.chooseOption()){
			case CMenu::START:		game->startGame();
									delete game;	// reset
									game = new CGame(settings);
									break;
			case CMenu::SETTINGS:	game->getSettings()->getNewSettings();
									break;
			case CMenu::END:		play_again = false; 
									break;
		}
	}

	delete game;
	delete settings;

	return 0;
}