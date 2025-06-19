#include <stdexcept>
#include <iostream>
#include <string>

#include "./mainMenu.h"

#include "../config.h"
#include "../console.h"
#include "../commandHandler.h"
#include "../consoleHandler.h"
#include "../display.h"
#include "../scheduler.h" 

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

		// block all non-initializations during startup
		if (currCommand.getType() != initialize && !Config::get_initialization_status()) {
			std::cout << "Cannot perform this action before initialization.\n";
			break;
		}

		// check command
		switch(currCommand.getType()) {
			case initialize:
				// message
				if (Config::get_initialization_status()) { std::cout << "Re-initializing system.\n\n"; }
				else { std::cout << "Initializing system.\n\n"; }

				Config::initConfig("./config.txt");
				break;

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