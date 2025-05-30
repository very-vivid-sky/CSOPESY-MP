#include <stdexcept>
#include <iostream>
#include <string>

#include "./console.h"
#include "./commandHandler.cpp"
#include "./display.cpp"

static ConsoleHandlerClass* ConsoleHandler = new ConsoleHandlerClass(8);

Console::Console() {};
void Console::run() {
	std::cout << "a";
};
Console::~Console() {
	ConsoleHandler->closeConsole(this);
}

std::string Console::getName() { return name; }
void Console::setName(std::string newName) { name = newName; }

ScreenConsole::ScreenConsole(std::string newName) {
	name = newName;
}

void ScreenConsole::run() {
	displayProcesses();
	while (true) {
		std::string input = getInputWithPrompt("Input command");
		Command currCommand = Command(input);

		switch(currCommand.getType()) {
			case screen:
				if (currCommand.hasFlag("-r")) {
					std::cout << "\n";
					displayProcesses();
				}
				else if (currCommand.hasFlag("-s")) {}
				else {
					std::cout << "Unrecognized command.";
				}
				break;

			case exit_menu:
				delete this;
				return;

			default:
				std::cout << "Unrecognized command.\n\n";
				break;
		}
	}
};

void ScreenConsole::displayProcesses() {
	std::cout << "There are processes on:\n" ;
	// placeholder
	time_t temp_time = time(0);
	char temp_time_c[24];
	strftime(temp_time_c, 24, "%m/%d/%Y, %I:%M:%S %p", localtime(&temp_time));
	//std::string temp_time_s = std::string(asctime(localtime(&temp_time)));
	std::cout << " - " << name << " [0/5] [" << std::string(temp_time_c) << "]\n";
};

void MainMenuConsole::run() {
	displayHeader();

	while (true) {
		std::string input = getInputWithPrompt("Input command");
		Command currCommand = Command(input);

		// check command
		switch(currCommand.getType()) {
			case initialize:
				std::cout << "Recognized 'initialize'. Doing something.\n\n"; break;
			case screen:
				if (currCommand.hasFlag("-r")) {
					if (currCommand.getSize() < 3) { std::cout << "Invalid command format.\n"; break; }
					ConsoleHandler->addAndGotoConsole(new ScreenConsole( currCommand.getToken(2) ));
					return;
				}
				else if (currCommand.hasFlag("-s")) {
					if (currCommand.getSize() < 3) { std::cout << "Invalid command format.\n"; break; }
					ConsoleHandler->addAndGotoConsole(new ScreenConsole( currCommand.getToken(2) ));
					return;
				}
				else { std::cout << "Flag not recognized for screen.\n\n"; };
				break;
			case scheduler_test:
				std::cout << "Recognized 'scheduler-test'. Doing something.\n\n"; break;
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