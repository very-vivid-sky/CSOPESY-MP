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
    WriteConsoleA(outConsole, header, strlen(header), nullptr, nullptr);  

    while (ScreenConsoleRunning) {

        std::cout << "Process name: " << this->getName() << "\n" << std::endl;
        std::cout << "ID: " << this->targetProcess->getPid() << "\n" << std::endl;
        std::cout << "Logs: " << this->targetProcess->getPid() << "\n" << std::endl;
        std::cout << "\tINSERT SAMPLE RUNNING OF PROGRAMS " << this->targetProcess->getPid() << "\n" << std::endl;
        std::cout << "\nCurrent instruction line: " << "BRUTE FORCE, NO VALUE YET" << "\n" << std::endl;
        std::cout << "\nLines of code: " << this->targetProcess->getTotalCommands() << "\n" << std::endl;

        std::string input = InputManager::getInputWithPrompt("Screen - Enter command");
        int idx = 1;
        Command currCommand = Command(input);

        if (currCommand.getRaw().compare("process-smi")==0) {
            std::cout << "display current processes";
            continue;
        }
        else if(currCommand.getRaw().compare("exit")==0){
            ScreenConsoleRunning = false;

            ConsoleManager::getInstance()->closeConsoleAndReturnToPrevious();

        }
        else {
            std::cout << "Command not recognized. \n" << std::endl;
        }

    }
}

void ScreenConsole::onEnabled() {
    if (this->running == false) {
        running = true;
        ConsoleManager::getInstance()->process();
    }
}