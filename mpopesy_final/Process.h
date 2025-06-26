#pragma once
#include "TypedefRepo.h"
#include "SymbolTable.h"

/**
    Process might need to be a class because 
    it will 
*/
class Process{
    String name;
    Time_t creationTime;
    int totalCommands;
    int executedCommands;
    int pid;
    bool finished;
    Mutex mtx;
    Symbols::SymbolTable symbolTable;

    int currentCore;
};