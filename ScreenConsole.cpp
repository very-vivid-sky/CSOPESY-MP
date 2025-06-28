#pragma once
#include "ScreenConsole.h"

void ScreenConsole::display() {}

void ScreenConsole::process() {
    system("cls");
    std::cout << "=== PROCESS  ===\n\n";

    if (!targetProcess) {
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
    std::cin.get();

    //go back to main menu
}

void ScreenConsole::onEnabled() {
    if (this->running == false) {
        running = true;
        ConsoleManager::getInstance()->process();
    }
}