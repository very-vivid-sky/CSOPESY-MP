#include "MarqueeConsole.h"

MarqueeConsole::MarqueeConsole() : AConsole("MarqueeConsole") {
}


void MarqueeConsole::displayHeader() {
	const char* header = "Hello you're in marquee console right now \n MARQUEEE\n\n";

	WriteConsoleA(outConsole, header, strlen(header), nullptr, nullptr);
}


/*NOT USED YET*/
void MarqueeConsole::display() {}


/*
* Current implementation:
	- drawConsole implementation is part of the process
	- getting input is still dependent on std::cin
*
*
* TODO: 1 Migrate drawConsole implementation to display
* TODO: 1 Change the input management from std::cin to more threadsafe implementation
*/
void MarqueeConsole::process() {

	//process 
	//display the header 

	this->displayHeader();

	while (true) {
		std::string input = InputManager::getInputWithPrompt("Marquee - Enter command ");
		std::string processName;
		//int idx;
		Command currCommand = Command(input);

		// check command
		switch (currCommand.getType()) {
		case exit_marquee: {
			this->~MarqueeConsole();
			ConsoleManager::getInstance()->returnToPreviousConsole();
			break;
		}
		default:
			std::cout << input << std::endl;

		}
	}

}


/*
* This function should do the following:
* - enable the symbol table speficic to that console
*	- eg., marquee console only has clear and exit as
*	- actionable commands, rest are just displayed in the console
*/
void MarqueeConsole::onEnabled() {
	if (!this->running) {
		std::cout << "MarqueeConsole onEnabled()" << std::endl;
		ConsoleManager::getInstance()->process();
		ConsoleManager::getInstance()->drawConsole();
		running = true;
	}
};