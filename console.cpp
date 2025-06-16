#include <stdexcept>
#include <iostream>
#include <string>

#include "./console.h"
#include "./commandHandler.cpp"
#include "./display.cpp"
#include "./scheduler.h" 

static ConsoleHandlerClass* ConsoleHandler = new ConsoleHandlerClass(8);

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

MainMenuConsole::MainMenuConsole() {
	name = "__MAIN_MENU__";
	type = c_MainMenu;
};
void MainMenuConsole::run() {

	while (true) {
		std::string input = getInputWithPrompt("Input command");
		std::string processName;
		int idx;
		Command currCommand = Command(input);

		// check command
		switch(currCommand.getType()) {
			case initialize:
				std::cout << "Recognized 'initialize'. Doing something.\n\n"; break;
			case screen:
				if (currCommand.getSize() < 2) { std::cout << "Invalid command format.\n"; break; };
				if (currCommand.hasFlag("-ls")) {
					MainScheduler->screenList(false);
					break;
				}

				idx = ConsoleHandler->searchForConsole(processName);
				// exists?
				if (idx >= 0) {
					if (currCommand.getSize() < 3) { std::cout << "Invalid command format.\n"; break; };
					processName = currCommand.getToken(2);

					// is this a screen?
					if (ConsoleHandler->getConsole(idx)->getType() == c_Screen) {
						if (currCommand.hasFlag("-r")) {
							std::cout << "Reloading screen!\n";
							ConsoleHandler->setCurrentConsole(idx);
							((ScreenConsole*) (ConsoleHandler->getCurrentConsole()))->setTimestampToNow();
							return;
						}
						else if (currCommand.hasFlag("-s")) {
							ConsoleHandler->setCurrentConsole(idx);
							return;
						}
					} else {
						std::cout << "Provided screen name is invalid.\n";
					}
				}
				// doesn't exist yet
				else {
					if (currCommand.hasFlag("-r") || currCommand.hasFlag("-s")) {
						ConsoleHandler->addAndGotoConsole(new ScreenConsole(processName));
						return;
					}
				}
				/*
				if (currCommand.hasFlag("-r")) {
					ConsoleHandler->addAndGotoConsole(new ScreenConsole( processName ));
					return;
				}
				else if (currCommand.hasFlag("-s")) {
					ConsoleHandler->addAndGotoConsole(new ScreenConsole( processName ));
					return;
				}
				else { std::cout << "Command not recognized for screen.\n\n"; };
				*/
				break;
			case scheduler_test:
				std::cout << "Recognized 'scheduler-test'. Doing something.\n\n"; break;
				// runSchedulerTest();
				// screen_ls();
				break;
			case scheduler_stop:
				std::cout << "Recognized 'scheduler-stop'. Doing something.\n\n"; break;
			case report_util:
				std::cout << "Recognized 'report-util'. Doing something.\n\n"; break;
			case clear:
				refresh();
				displayHeader();
				break;
			case exit_menu:
				std::cout << "Exiting OS.\n\n";
				delete this;
				return;
			default:
				std::cout << "Unrecognized command.\n\n";
				break;
		}
	}
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

bool ConsoleHandlerClass::isRunning() {
	return (activeConsoles[0] == true);
}

void ConsoleHandlerClass::runConsole() {
	currentConsole->run();
};

void ConsoleHandlerClass::addConsole(Console* c) {
	for (int i = 0; i < size; i++) {
		if ((activeConsoles[i]) == false) {
			activeConsoles[i] = true;
			allConsoles[i] = c;
			return;
		}
	}
	throw std::range_error("Tried to add a new console to an already full console handler");
};

void ConsoleHandlerClass::addAndGotoConsole(Console* c) {
	addConsole(c);
	currentConsole = c;
};

int ConsoleHandlerClass::searchForConsole(std::string consoleName) {
	for (int i = 0; i < size; i++) {
		if (activeConsoles[i] == true) {
			if (consoleName == allConsoles[i]->getName()) {
				return i;
			}
		}
	}
	return -1;
};
Console* ConsoleHandlerClass::getConsole(int i) {
	return allConsoles[i];
}
Console* ConsoleHandlerClass::getCurrentConsole() {
	return currentConsole;
}
void ConsoleHandlerClass::setCurrentConsole(int i) {
	if (activeConsoles[i] == true) {
		currentConsole = allConsoles[i];
	}
}

void ConsoleHandlerClass::gotoMainMenu() {
	currentConsole = mainMenu;
};

void ConsoleHandlerClass::run() {
	currentConsole->run();
};

void ConsoleHandlerClass::closeConsole(Console* c) {
	for (int i = 0; i < size; i++) {
		if (activeConsoles[i] == true && c == allConsoles[i]) {
			gotoMainMenu();
			activeConsoles[i] = false;
			break;
		}
	}
};