#include <iostream>
#include <string>

#include "./display.cpp"

enum CommandType { unknown, initialize, screen, scheduler_test, scheduler_stop, report_util, clear, exit_os };
CommandType getCommandType(std::string command) {
	// get substring
	int idx = command.find_first_of(' ');
	std::string cmdFirst = command.substr(0, idx);

	// figure out which command this is
	if (command.compare("initialize") == 0) { return initialize; }
	else if (command.compare("screen") == 0) { return screen; }
	else if (command.compare("scheduler-test") == 0) { return scheduler_test; }
	else if (command.compare("scheduler-stop") == 0) { return scheduler_stop; }
	else if (command.compare("report-util") == 0) { return report_util; }
	else if (command.compare("clear") == 0) { return clear; }
	else if (command.compare("exit") == 0) { return exit_os; }
	else { return unknown; }
}

/*	The main screen for the operating system.
	@return				Should always return zero.
*/
int main() {
	int OS_RUNNING = 1;

	refresh();
	while (OS_RUNNING) {
		std::string input = getInputWithPrompt("Input command");

		// check command
		switch(getCommandType(input)) {
			case initialize:
				std::cout << "Recognized 'initialize'. Doing something.\n\n"; break;
			case screen:
				std::cout << "Recognized 'screen'. Doing something.\n\n"; break;
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
}