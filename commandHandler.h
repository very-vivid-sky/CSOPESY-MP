#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include "TypedefRepo.h"


// Define the available command types
enum CommandType {
    unknown,
    initialize,
    screen,
    scheduler_test,
    scheduler_stop,
    report_util,
    clear,
    exit_marquee,
    marquee,
    exit_menu
};

class Command {
public:
    Command(std::string newCommand)
        : raw(std::move(newCommand)), type(unknown) {
        tokenize();
        initializeType();
    }


    /*
    * @brief Returns the type of command :
    *   - init, screen, scheduler_test,clear,exit,etc.,
    *
    * @return enum <CommandType>
    */
    CommandType getType() const;

    /*
    * @brief Returns the size of the token
    *
    * TODO: 4 Are we using this?
    */
    int getSize() const;

    /*
    * @brief Gets the raw string of command
    * @return String
    */
    String getRaw() const;


    /*
    * @brief Gets the token
    *
    * TODO 4: What and which token is this? Kindly rename, thank you
    */
    String getToken(int idx) const;


    /*
    * @brief Checks if token is empty or not
    * @return boolean true or false
    * TODO 4: What's the hasFlag for? Tama ba yung brief? Kindly add description, thank you
    */
    bool hasFlag(const std::string& flag) const;



    /*
    * TODO: 4 Where does this function fit in? Can I delete this?
    */
    void runCommandHandler();

private:
    std::string raw;
    CommandType type;
    std::vector<std::string> tokens;



    void tokenize() {
        std::istringstream iss(raw);
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }
    }

    /*
    * TODO 3: Kindly add description thank you.
    */
    void initializeType() {
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
        else if (command == "exit_marquee") type = exit_marquee;
        else if (command == "marquee") type = marquee;
        else type = unknown;
    }
};
