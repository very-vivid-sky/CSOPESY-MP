#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include <ctime>

class Console {
	public:
		Console();
		virtual void run();
		~Console();

		std::string getName();
		void setName(std::string newName);

	protected:
		std::string name;
};

class ConsoleHandlerClass {
	public:
		ConsoleHandlerClass(int s);
		bool isRunning();
		void runConsole();
		void addConsole(Console* c);
		void addAndGotoConsole(Console* c);
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

class MainMenuConsole : public Console {
	public:
		void run();
};

class ScreenConsole : public Console {
	public:
		ScreenConsole(std::string newName);
		void run();
		void displayProcesses();
};

#endif