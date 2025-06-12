#include <iostream>
#include <string>

#include "console.cpp"
#include "scheduler.h" 

int main() {
    displayHeader();

    while (ConsoleHandler->isRunning()) {
        ConsoleHandler->run();

        runSchedulerTest();
        screen_ls();
    }

    return 0;
}
