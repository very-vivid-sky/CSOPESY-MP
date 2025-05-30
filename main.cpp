#include <iostream>
#include <string>

#include "./console.cpp"
//#include "./display.cpp"
//#include "./commandHandler.cpp"

/*	The main screen for the operating system.
	@return				Should always return zero.
*/

int main() {
	while (ConsoleHandler->isRunning()) {
		ConsoleHandler->run();
	}

	return 0;

	/*
	int OS_RUNNING = 1;

	refresh();
	while (OS_RUNNING) {
		std::string input = getInputWithPrompt("Input command");
		Command currCommand = Command(input);

		// check command
		switch(currCommand.getType()) {
			case initialize:
				std::cout << "Recognized 'initialize'. Doing something.\n\n"; break;
			case screen:
				if (currCommand.hasFlag("-r")) {
					std::cout << "Recognized 'screen -r'. Doing something.\n\n";
				}
				else if (currCommand.hasFlag("-s")) {
					std::cout << "Recognized 'screen -s'. Doing something.\n\n";
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
				break;
			case exit_os:
				std::cout << "Exiting OS.\n\n";
				OS_RUNNING = 0;
				break;
			default:
				std::cout << "Unrecognized command.\n\n";
				break;
		}
	}

	return 0;
	*/
}