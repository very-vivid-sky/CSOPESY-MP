#ifndef MAINMENU_H
#define MAINMENU_H

#include "../console.h"

class MainMenuConsole : public Console {
	public:
		MainMenuConsole();
		void run();
};

#include "mainMenu.cpp"
#endif