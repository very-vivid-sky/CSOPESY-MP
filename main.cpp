#include <iostream>
#include <string>

#include "scheduler.h"
#include "console.h"

int main() {
    MainScheduler = new Scheduler();
    MainScheduler->runSchedulerTest();

    displayHeader();

    while (ConsoleHandler->isRunning()) {
        ConsoleHandler->run();
    }

    return 0;
}
