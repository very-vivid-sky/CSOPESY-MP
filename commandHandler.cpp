#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdexcept>

#include "commandHandler.h"

Command::Command(std::string newCommand)
    : raw(std::move(newCommand)), type(unknown) {
    tokenize();
    initializeType();
}

CommandType Command::getType() { return type; }
int Command::getSize() { return tokens.size(); }
std::string Command::getRaw() { return raw; }

std::string Command::getToken(int idx) {
    if (idx < 0 || idx >= static_cast<int>(tokens.size())) {
        throw std::out_of_range("Out of range of Command's tokens");
    }
    return tokens[idx];
}

bool Command::hasFlag(const std::string& flag) {
    return std::find(tokens.begin(), tokens.end(), flag) != tokens.end();
}

void Command::tokenize() {
    std::istringstream iss(raw);
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
}

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

void runCommandHandler() {
    bool running = true;

    while (running) {
        std::cout << ">> ";
        std::string input;
        std::getline(std::cin, input);

        Command cmd(input);

        switch (cmd.getType()) {
        case initialize:
            std::cout << "Initialize command not yet implemented.\n";
            break;

        case screen:
            //screen_ls();
            break;

        case scheduler_test: 
            //runSchedulerTest();
            break;

        case scheduler_stop:
            /*
            std::cout << "Stopping scheduler...\n";
            schedulerRunning = false;
            emulatorRunning = false;
            cv.notify_all(); 
            */
            break;

        case report_util:
            std::cout << "Report-util command not yet implemented.\n";
            break;

        case clear:
            system("cls");
            break;

        case exit_menu:
            std::cout << "Exiting...\n";
            running = false;
            break;

        default:
            std::cout << "Unknown command\n";
            break;
        }
    }
}
