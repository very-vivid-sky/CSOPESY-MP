#include "InputManager.h"


/*	This function gets a string input.
*	@return				A string input of 63 characters maximum.
*/
String InputManager::getInput() {
	char temp[64];
	std::cin.getline(temp, 63);
	String res = temp;


	return res;
}


/*	This function prompts the user to input a string.
*	@param prompt		A prompt for the user. Any string, will just be printed.
*	@return				A string input of 63 characters maximum.
*/
String InputManager::getInputWithPrompt(String prompt) {
	std::cout << prompt;
	std::cout << ": ";
	return getInput();
}