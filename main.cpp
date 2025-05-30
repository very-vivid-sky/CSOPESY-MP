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
}