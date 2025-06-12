#include <iostream>
#include <string>

#include "console.cpp"

int main() {
    displayHeader();

    while (ConsoleHandler->isRunning()) {
        ConsoleHandler->run();
    }

    return 0;
}
