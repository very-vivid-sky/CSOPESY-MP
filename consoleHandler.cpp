#include <stdexcept>
#include <iostream>
#include <string>

#include "./console.h"
#include "./consoleHandler.h"
#include "./menus/mainMenu.h"
#include "./commandHandler.h"
#include "./display.h"

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