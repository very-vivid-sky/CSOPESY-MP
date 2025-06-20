#include "MainConsole.h"


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
   \\\\____| \\\_____/   \\\____/  |||       |||____| \\\_____/  \\\____/ |||_|  
	)
	\x1B[33mWelcome to CSOPESY OS!\033[0m
	\x1B[32mby Bautista, Cacatian, De Veyra, Yee\033[0m

	)";


	return header;

}




void MainConsole::display() {
	const char* header = this->getHeader();


	// writes directly to the console 
	// outConsole is a global variable ; check ConsoleGlobals.h
	WriteConsoleA(outConsole, header, strlen(header), nullptr, nullptr);

}

void MainConsole::process() {

	//process 
	//display the header 
	const char* header = this->getHeader();
	const char* command = "Enter command: ";
}

void MainConsole::onEnabled() {
	std::cout << "This part is working right now";
};