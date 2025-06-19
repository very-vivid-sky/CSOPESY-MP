#ifndef CONSOLEHANDLER_H
#define CONSOLEHANDLER_H

#include "./console.h"

class ConsoleHandlerClass {
	public:
		ConsoleHandlerClass(int s);
		bool isRunning();
		void runConsole();
		void addConsole(Console* c);
		void addAndGotoConsole(Console* c);
		int searchForConsole(std::string consoleName);
		Console* getConsole(int i);
		Console* getCurrentConsole();
		void setCurrentConsole(int i);
		void gotoMainMenu();
		void run();
		void closeConsole(Console* c);

	private:
		int size;
		Console* mainMenu;
		Console* currentConsole;
		Console** allConsoles;
		bool* activeConsoles;
};

ConsoleHandlerClass* ConsoleHandler = new ConsoleHandlerClass(8);

#include "./consolehandler.cpp"
#endif