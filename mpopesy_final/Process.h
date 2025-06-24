#pragma once
#include "TypedefRepo.h"

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

    int currentCore;
};