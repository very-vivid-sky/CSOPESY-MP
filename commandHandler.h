#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

// Define the available command types
enum CommandType {
    unknown,
    initialize,
    screen,
    scheduler_test,
    scheduler_stop,
    report_util,
    clear,
    exit_menu
};

class Command {
	public:
		Command(std::string newCommand);
		CommandType getType();
		int getSize();
		std::string getRaw();
		std::string getToken(int idx);
		bool hasFlag(const std::string& flag);

	private:
		std::string raw;
		CommandType type;
		std::vector<std::string> tokens;
		void tokenize();
		void initializeType();
};

void runCommandHandler();

#include "commandhandler.cpp"
#endif