#pragma once
#include "TypedefRepo.h"

struct Process {
    String name;
    Time_t creationTime;
    int totalCommands;
    int executedCommands;
    int pid;
    bool finished;
    Mutex mtx;

    int currentCore;
};