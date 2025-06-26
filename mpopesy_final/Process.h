#pragma once

#include "TypedefRepo.h"
#include "SymbolTable.h"

namespace Processes {
    class Process {
        public:
            Process(std::string newTime);

            std::string getName();
            std::time_t getCreationTime();
            std::string getFormattedCreationTime();
            int getTotalCommands();
            int getNextLine();
            int getPid();
            int getCore();
            bool isFinished();

            void setCore(int newCore);

            void run();

            Mutex mtx;

        private:
            std::string name;
            std::time_t creationTime;
            int totalCommands;
            int nextLine;
            int pid;
            bool finished;

            Symbols::SymbolTable symbolTable;

            int currentCore;
    };
};