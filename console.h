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

class ScreenConsole : public Console {
	public:
		ScreenConsole(std::string newName);
		void run();
		void setTimestampToNow();
		void displayProcesses();
	private:
		std::string timestamp;
};

#include "console.cpp"

#endif