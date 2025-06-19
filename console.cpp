#include <stdexcept>
#include <iostream>
#include <string>

#include "./console.h"
#include "./consoleHandler.h"
#include "./display.h"
#include "./scheduler.h" 

Console::Console() {};
void Console::run() {
	std::cout << "a";
};
Console::~Console() {
	ConsoleHandler->closeConsole(this);
}
ConsoleType Console::getType() {
	return type;
}

std::string Console::getName() { return name; }
void Console::setName(std::string newName) { name = newName; }


ScreenConsole::ScreenConsole(std::string newName) {
	type = c_Screen;
	name = newName;
	setTimestampToNow();
};
void ScreenConsole::setTimestampToNow() {
	time_t temp_time = time(0);
	char temp_time_c[24];
	strftime(temp_time_c, 24, "%m/%d/%Y, %I:%M:%S %p", localtime(&temp_time));
	timestamp = std::string(temp_time_c);
}
void ScreenConsole::run() {
	std::cout << "\n";
	displayProcesses();
	while (true) {
		std::string input = getInputWithPrompt("Input command");
		Command currCommand = Command(input);

		switch(currCommand.getType()) {
			case exit_menu:
				ConsoleHandler->gotoMainMenu();
				std::cout << "Exiting menu!\n\n";
				return;

			default:
				std::cout << "Unrecognized command.\n\n";
				break;
		}
	}
};

void ScreenConsole::displayProcesses() {
	std::cout << "There are processes on:\n" ;
	//std::string temp_time_s = std::string(asctime(localtime(&temp_time)));
	std::cout << " - " << name << " [0/5] [" << timestamp << "]\n";
};

ConsoleHandlerClass::ConsoleHandlerClass(int s) {
	size = s;
	allConsoles = new Console*[size];
	activeConsoles = new bool[size];

	// cleanup of garbage data
	for (int i = 0; i < size; i++) {
		activeConsoles[i] = false;
	}

	addConsole(new MainMenuConsole());
	mainMenu = allConsoles[0];
	currentConsole = mainMenu;
};