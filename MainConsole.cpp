#include "MainConsole.h"
#include "CommandHandler.h"
#include "InputManager.h"
#include "ConsoleManager.h"
#include "Config.h"
#include "ProcessBuilder.h"
#include "Scheduler.h"


MainConsole::MainConsole() : AConsole("MAIN_CONSOLE") {
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
	Welcome to CSOPESY OS!
	by Bautista, Cacatian, De Veyra, Yee

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

	while (ConsoleManager::getInstance()->isRunning()) {
		std::string input = InputManager::getInputWithPrompt("Main - Enter command");
		Command currCommand = Command(input);
		std::string processName;

		// unrecognized command !
		if (currCommand.getType() == unknown) {
			std::cout << "Unrecognized command.\n\n";
			continue;
		}

		// initialize check
		if (!(currCommand.getType() == initialize || currCommand.getType() == exit_menu) && !Config::get_initialization_status()) {
			std::cout << "Cannot perform this action before initialization.\n\n";
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
			processName = currCommand.getToken(2);

			if (currCommand.getSize() < 2) { std::cout << "Invalid command format.\n\n"; break;};
			if (currCommand.hasFlag("-ls")) {
				//MainScheduler->screenList(false);
				std::cout << "\nscreen -ls atm\n\n";
				break;
			}else if (currCommand.hasFlag("-r") || currCommand.hasFlag("-s")) {
				if (currCommand.getSize() < 3) {
					std::cout << "Invalid command format.\n\n";
				};
				//screen is already in the console
				if (ConsoleManager::getInstance()->findConsole(processName)) {
					if (currCommand.hasFlag("-r")) {
						ConsoleManager::getInstance()->switchConsole(processName);
					}
					else if (currCommand.hasFlag("-s")) {
						std::cout << "Process " << processName << " already exists. Can't have multiple processses with the same name\n";
						//ConsoleManager::getInstance()->addConsole(processName);
					}
				}
				else { //screen is not yet in the console
					if (currCommand.hasFlag("-r")) {
						std::cout << "Process " << processName << " can't be loaded. Maybe it's not yet created\n";
					}
					else if (currCommand.hasFlag("-s")) {
						ConsoleManager::getInstance()->addConsole(processName);
					}
				}
			}else { std::cout << "Command not recognized for screen.\n\n"; };
			break;
        
        
		case scheduler_start:
			if (Scheduler::runGenerator) {
				std::cout << "Automatic process generation is already running!\n\n";
			} else {
				std::cout << "Starting automatic process generation.\n\n";
				Scheduler::processBuilder();
			}
			break;
		case scheduler_stop:
			if (Scheduler::runGenerator) {
				std::cout << "Stopping automatic process generation.\n\n";
				Scheduler::runGenerator = false;
			} else {
				std::cout << "Automatic process generation is already off!\n\n";
			}
			break;
		case report_util:
			std::cout << "Recognized 'report-util'. Doing something.\n\n"; break;
		case clear:
			ConsoleManager::refresh();
			this->displayHeader();
			break;
		case exit_menu:
			std::cout << "Exiting OS.\n\n";
			ConsoleManager::getInstance()->stopRunning();
			break;
		case marquee:
			ConsoleManager::getInstance()->switchConsole("MARQUEE_CONSOLE");
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
	if (!this->running) {
		running = true;
	}
};