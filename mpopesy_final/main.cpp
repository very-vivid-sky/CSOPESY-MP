#include <iostream>
#include "ConsoleManager.h"
#include "MainConsole.h"
#include "ConsoleGlobals.h"


//extern variables store at ConsoleGlobals.h
HANDLE outConsole = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE inConsole = GetStdHandle(STD_INPUT_HANDLE);

int main() {
	//bootstrap
	//initialize
	//start systerm services
	//enter main loop 
	//delete and clear memory


	
	ConsoleManager::initialize();


	bool OS_RUNNING = true;


	while (OS_RUNNING) {

		ConsoleManager::getInstance()->process();    // get first the process 
		ConsoleManager::getInstance()->drawConsole(); // draw the console 

		OS_RUNNING = ConsoleManager::getInstance()->isRunning();
	}


	ConsoleManager::destroy();

}