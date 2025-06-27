#pragma once

#include "TypedefRepo.h"
#include "InstructionList.h"
#include "SymbolTable.h"

namespace Processes {
    enum processState {
        newly,      // process is created
        ready,      // process is waiting to be assigned to a processor (in a ReadyQueue)
        waiting,    // waiting for an event (I/O or event completion)
        running,    // process is being executed
        terminated, // process has finished executing
    };

    class Process {
        public:
            Process(std::string newName);

            std::string getName();
            std::time_t getCreationTime();
            std::string getFormattedCreationTime();
            int getTotalCommands();
            int getNextLine();
            int getPid();
            int getCore();
            bool isFinished();
            Instructions::InstructionList* getInstructionList();
            Symbols::SymbolTable* getSymbolTable();

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

            Instructions::InstructionList instructionList;
            Symbols::SymbolTable symbolTable;


            int currentCore;
    };
};