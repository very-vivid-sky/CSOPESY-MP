#pragma once
#include "ScreenConsole.h"

void ScreenConsole::display() {}

void ScreenConsole::process() {
    system("cls");
    std::cout << "=== PROCESS SCREEN  ===\n\n";
    std::string inputCommand; 
    bool ScreenConsoleRunning = true;

    /*if (!targetProcess) {
        std::cout << "No process selected.\n";
        return;
    }

    std::lock_guard<std::mutex> lock(targetProcess->mtx);

    std::cout << "Name: " << targetProcess->getName() << "\n";
    std::cout << "PID: " << targetProcess->getPid() << "\n";
    std::cout << "Core: " << targetProcess->getCore() << "\n";
    std::cout << "Executed Commands: " << targetProcess->getNextLine()
        << " / " << targetProcess->getTotalCommands() << "\n";

    std::cout << "\nPress [Enter] to go back...";
    std::cin.get();*/

    //go back to main menu


    const char* header = "Hello You're in the Screen CONSOLE\n Input any command to exit this screen\n";
    // outConsole is a global variable ; check ConsoleGlobals.h
    std::cout << "Process name: " << this->getName() << "\n" << std::endl;
    WriteConsoleA(outConsole, header, strlen(header), nullptr, nullptr);

    while (ScreenConsoleRunning) {
        std::string input = InputManager::getInputWithPrompt("Screen - Enter command");
        int idx = 1;
        Command currCommand = Command(input);

        if (currCommand.getRaw().size() > 0) {
            ScreenConsoleRunning = false;
            ConsoleManager::getInstance()->returnToPreviousConsole();
        }

    }
}

void ScreenConsole::onEnabled() {
    if (this->running == false) {
        running = true;
        ConsoleManager::getInstance()->process();
    }
}