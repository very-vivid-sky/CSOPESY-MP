#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include <ctime>

enum ConsoleType { c_Undefined, c_MainMenu, c_Screen };

class Console {
	public:
		Console();
		Console(std::string newName);
		virtual void run();
		~Console();

		std::string getName();
		ConsoleType getType();
		void setName(std::string newName);

	protected:
		std::string name;
		ConsoleType type;
};

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

class MainMenuConsole : public Console {
	public:
		MainMenuConsole();
		void run();
};

class ScreenConsole : public Console {
	public:
		ScreenConsole(std::string newName);
		void run();
		void setTimestampToNow();
		void displayProcesses();
	private:
		std::string timestamp;
};

#endif