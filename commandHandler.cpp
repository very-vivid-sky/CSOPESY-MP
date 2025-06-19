#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdexcept>

#include "commandHandler.h"

// Initializes, parses, and tokenizes command from string interpretation
Command::Command(std::string newCommand)
    : raw(std::move(newCommand)), type(unknown) {
    tokenize();
    initializeType();
}

// Getter for command type
CommandType Command::getType() { return type; }
// Getter for size of this command (number of tokens)
int Command::getSize() { return tokens.size(); }
// Getter for raw string interpretation of this command
std::string Command::getRaw() { return raw; }

// Gets token by index
std::string Command::getToken(int idx) {
    if (idx < 0 || idx >= static_cast<int>(tokens.size())) {
        throw std::out_of_range("Out of range of Command's tokens");
    }
    return tokens[idx];
}

// Checks if this command has a certain flag or matches a string exactly
// flag is a string, e.g. "-ls"
bool Command::hasFlag(const std::string& flag) {
    return std::find(tokens.begin(), tokens.end(), flag) != tokens.end();
}

// Tokenizes this command by splitting it by spaces; places it to the tokens vector
void Command::tokenize() {
    std::istringstream iss(raw);
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
}

// Determines and initializes the type of this command via the first argument
void Command::initializeType() {
    if (tokens.empty()) {
        type = unknown;
        return;
    }

    const std::string& command = tokens[0];
    if (command == "initialize") type = initialize;
    else if (command == "screen") type = screen;
    else if (command == "scheduler-test") type = scheduler_test;
    else if (command == "scheduler-stop") type = scheduler_stop;
    else if (command == "report-util") type = report_util;
    else if (command == "clear") type = clear;
    else if (command == "exit") type = exit_menu;
    else type = unknown;
}