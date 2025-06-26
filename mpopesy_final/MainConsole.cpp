#include "MainConsole.h"
#include "CommandHandler.h"
#include "InputManager.h"
#include "ConsoleManager.h"
#include "Config.h"
#include "Scheduler.h"


MainConsole::MainConsole() : AConsole("MainConsole") {
}


/* IGNORE THE \x1B it's supposed to change the color of the character but
	currently not working because it's currently a raw string
*/
const char* MainConsole::getHeader() {
	/*
		_____    ______     ______    ______   _______    ______    __   __  ___
	   //____|  /// ___\   ///___ \  |||___ \  |||____|  /// ___\  |||  | | ||| |
	  ///      ||| |___   |||    | | |||   | | |||____  ||| |__    |||__| | ||| |
	  |||       \\\___ \  |||    | | |||___| | |||____|  \\\___ \  \\\__  | ||| |
	  |||             \ \ |||    | | |||____/  |||             \ \      | | |||_|
	  \\\____  _______/ / |||____| | |||       |||____  _______/ / _____| |  ___
	   \\____| \\\_____/   \\\____/  |||       |||____| \\\_____/  \\\____/ |||_|

		*/

	const char* header = R"(    _____    ______     ______    ______   _______    ______    __   __  ___   
   //____|  /// ___\   ///___ \  |||___ \  |||____|  /// ___\  |||  | | ||| |  
  ///      ||| |___   |||    | | |||   | | |||____  ||| |__    |||__| | ||| |  
  |||       \\\___ \  |||    | | |||___| | |||____|  \\\___ \  \\\__  | ||| |  
  |||             \ \ |||    | | |||____/  |||             \ \      | | |||_|  
  \\\____  _______/ / |||____| | |||       |||____  _______/ / _____| |  ___   
   \\\___| \\\_____/   \\\____/  |||       |||____| \\\_____/  \\\____/ |||_|  
	)
	\x1B[33mWelcome to CSOPESY OS!\033[0m
	\x1B[32mby Bautista, Cacatian, De Veyra, Yee\033[0m

)";

	return header;
}



void MainConsole::displayHeader() {
	const char* header = this->getHeader();
	WriteConsoleA(outConsole, header, strlen(header), nullptr, nullptr);
}


/*NOT USED YET*/
void MainConsole::display() {}
	

/*
* Current implementation: 
	- drawConsole implementation is part of the process
	- getting input is still dependent on std::cin
* 
* 
* TODO: 1 Migrate drawConsole implementation to display 
* TODO: 1 Change the input management from std::cin to more threadsafe implementation
*/
void MainConsole::process() {

	//process 
	//display the header 

	// writes directly to the console 
	const char* header = this->getHeader();
	// outConsole is a global variable ; check ConsoleGlobals.h
	WriteConsoleA(outConsole, header, strlen(header), nullptr, nullptr);

	while (true) {
		std::string input = InputManager::getInputWithPrompt("Enter command");
		std::string processName;
		//int idx;
		Command currCommand = Command(input);

		// unrecognized command !
		if (currCommand.getType() == unknown) {
			std::cout << "Unrecognized command.\n\n";
			continue;
		}

		// initialize check
		if (!(currCommand.getType() == initialize || currCommand.getType() == exit_menu) && !Config::get_initialization_status()) {
			std::cout << "Cannot perform this action before initialization.\n";
			continue;
		}

		// check command
		switch (currCommand.getType()) {
		case initialize:
			// message
			if (Config::get_initialization_status()) { std::cout << "System has already been initialized!\n\n"; return; }
			else {
				std::cout << "Initializing system.\n\n";
				Config::initConfig("./config.txt");
				Scheduler::MainScheduler = new Scheduler::SchedulerClass();
				Scheduler::MainScheduler->runSchedulerTest();
			}

			break;

		case screen:
			std::cout << "Recognized 'screen'. Doing something.\n\n"; break;
			/*
			if (currCommand.getSize() < 2) { std::cout << "Invalid command format.\n"; break; };
			if (currCommand.hasFlag("-ls")) {
				//MainScheduler->screenList(false);
				std::cout << "Screen -ls atm ";
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
						((ScreenConsole*)(ConsoleHandler->getCurrentConsole()))->setTimestampToNow();
						return;
					}
					else if (currCommand.hasFlag("-s")) {
						ConsoleHandler->setCurrentConsole(idx);
						return;
					}
				}
				else {
					std::cout << "Provided screen name is invalid.\n";
				}
			
			}else {
				if (currCommand.hasFlag("-r") || currCommand.hasFlag("-s")) {
					ConsoleHandler->addAndGotoConsole(new ScreenConsole(processName));
					return;
				}
			}*/
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
			ConsoleManager::refresh();
			this->displayHeader();
			break;
		case exit_menu:
			std::cout << "Exiting OS.\n\n";
			// delete this;
			return;
		default:
			std::cout << "Unrecognized command.\n\n";
			break;
		}
	}

}


/*
* This function should do the following: 
* - enable the symbol table speficic to that console 
*	- eg., marquee console only has clear and exit as 
*	- actionable commands, rest are just displayed in the console
*/
void MainConsole::onEnabled() {
	// std::cout << "onEnabled() is not working right now" << std::endl;
};