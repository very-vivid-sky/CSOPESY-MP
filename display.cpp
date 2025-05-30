#include <iostream>
#include <string>

/*	This function displays the ASCII art header of the os.
*/
void displayHeader() {
	/*
    _____    ______     ______    ______   _______    ______    __   __  ___   
   //____|  /// ___\   ///___ \  |||___ \  |||____|  /// ___\  |||  | | ||| |  
  ///      ||| |___   |||    | | |||   | | |||____  ||| |__    |||__| | ||| |  
  |||       \\\___ \  |||    | | |||___| | |||____|  \\\___ \  \\\__  | ||| |  
  |||             \ \ |||    | | |||____/  |||             \ \      | | |||_|  
  \\\____  _______/ / |||____| | |||       |||____  _______/ / _____| |  ___   
   \\____| \\\_____/   \\\____/  |||       |||____| \\\_____/  \\\____/ |||_|  
                                                                               
	*/

	// this looks really weird in the code because all backslashes are doubled
	// but i promise this will look right in practice -cy
	std::cout << "    _____    ______     ______    ______   _______    ______    __   __  ___   \n";
	std::cout << "   //____|  /// ___\\   ///___ \\  |||___ \\  |||____|  /// ___\\  |||  | | ||| |  \n";
	std::cout << "  ///      ||| |___   |||    | | |||   | | |||____  ||| |__    |||__| | ||| |  \n";
	std::cout << "  |||       \\\\\\___ \\  |||    | | |||___| | |||____|  \\\\\\___ \\  \\\\\\__  | ||| |  \n";
	std::cout << "  |||             \\ \\ |||    | | |||____/  |||             \\ \\      | | |||_|  \n";
	std::cout << "  \\\\\\____  _______/ / |||____| | |||       |||____  _______/ / _____| |  ___   \n";
	std::cout << "   \\\\____| \\\\\\_____/   \\\\\\____/  |||       |||____| \\\\\\_____/  \\\\\\____/ |||_|  \n";
	std::cout << "\n";
	std::cout << "      Welcome to CSOPESY OS!\n";
	std::cout << "      by Bautista, Cacatian, De Veyra, Yee\n\n";
}

/*	This function refreshes the console.
*/
void refresh() {
	/* safer solution, however technically does not even actually clear the log
	// make sure to include <windows.h> when importing !
	// code fished from my older c project hehe :> -cy
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dword;
	GetConsoleMode(handle, &dword);
	dword |= ENABLE_ECHO_INPUT;
	SetConsoleMode(handle, dword);

	std::cout << "\033[2J\033[H";
	*/

	// using system is unsafe and this command only works in windows, not unix.
	// TODO find a safer solution
	system("cls");
}

/*	This function gets a string input.
*	@return				A string input of 63 characters maximum.
*/
std::string getInput() {
	char temp[64];
	std::cin.getline(temp, 63);
	std::string res = temp;
	return res;
}

/*	This function prompts the user to input a string.
*	@param prompt		A prompt for the user. Any string, will just be printed.
*	@return				A string input of 63 characters maximum.
*/
std::string getInputWithPrompt(std::string prompt) {
	std::cout << prompt;
	std::cout << ": ";
	return getInput();
}