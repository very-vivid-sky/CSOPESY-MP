#include <iostream>
#include <string>

#include "config.h"
#include "scheduler.h"
#include "console.h"

int main() {
    // Configures global variables from the config.txt file
    ConfigVariables::initConfig("config.txt");

    // MainScheduler = new Scheduler();
    // MainScheduler->runSchedulerTest();

    displayHeader();

    while (ConsoleHandler->isRunning()) {
        ConsoleHandler->run();
    }

    return 0;
}
