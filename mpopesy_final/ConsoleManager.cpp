#include "ConsoleManager.h"
#include "MainConsole.h"
//#include "MarqueeConsole.h"
//#include "MemorySimulationConsole.h"
//#include "SchedulingConsole.h"

ConsoleManager* ConsoleManager::sharedInstance = nullptr;


ConsoleManager* ConsoleManager::getInstance() {
    if (sharedInstance == nullptr) {
        sharedInstance = new ConsoleManager();
    }

    return sharedInstance;
};


void ConsoleManager::initialize() {

    sharedInstance = new ConsoleManager();
};


void ConsoleManager::destroy() {
    delete sharedInstance;
};



/* This functiion draws the console

    is it the windows sizes and everything? or is this where
    the display header and everything goes?
*/
void ConsoleManager::drawConsole() const {

    this->currentConsole->display();
};



// IGNORE THIS RIGHT NOW HEHE
//char* ConsoleManager::readLine() {
//    const DWORD bufferSize = 1024;
//    char buffer[bufferSize];
//    DWORD charsRead;
//
//    // Read input from the console
//    if (!ReadConsoleA(this->inConsole, buffer, bufferSize, &charsRead, NULL)) {
//        std::cerr << "Failed to read from console.\n";
//        return '\0';
//    }
//
//    // Remove carriage return and newline
//    std::string input(buffer, charsRead);
//    if (!input.empty() && input.back() == '\n') input.pop_back();
//    if (!input.empty() && input.back() == '\r') input.pop_back();
//
//
//    std::vector<char> bufferVector(input.begin(), input.end());
//    input.push_back('\0'); // ensure null-terminated
//
//    char* toReturn = bufferVector.data(); // char* version
//
//    return toReturn;
//}


void ConsoleManager::process() const {

    this->currentConsole->process();

};

void ConsoleManager::switchConsole(String consoleName) {
    this->currentConsole = this->consoleTable[consoleName];

 
   
    // check if the next console exists in the console 
    if (this->consoleTable.contains(consoleName)){

        system("cls");
        this->previousConsole = this->currentConsole; 
        this->currentConsole = this->consoleTable[consoleName];
        this->currentConsole->onEnabled();
    
    }else {
        std::cerr << "Console name " << consoleName << "not found. Was it initialized?"; 
    }



};

void ConsoleManager::returnToPreviousConsole() {
    std::cout << "Doing something";
};

void ConsoleManager::exitApplication() {
    std::cout << "Doing something";

};
void ConsoleManager::unregisterScreen() {
    std::cout << "Doing something";

};

bool ConsoleManager::isRunning() const {
    if (mainConsole == nullptr) { return false; }
    return this->running;
};

void ConsoleManager::setCursorPosition(int posX, int posY) const {

    std::cout << "Doing something";
};


void ConsoleManager::refresh() {
  
        /* safer solution, however technically does not even actually clear the log
        // make sure to include <windows.h> when importing !
        // code fished from my older c project hehe :> -cy
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dword;
        GetConsoleMode(handle, &dword);
        dword |= ENABLE_ECHO_INPUT;
        SetConsoleMode(handle, dword);

        std::cout << "\033[2J\033[H";
        */

        // using system is unsafe and this command only works in windows, not unix.
        // TODO find a safer solution

    system("cls");
   
}





//constructor
ConsoleManager::ConsoleManager() {


    this->running = true;

    mainConsole = std::make_shared<MainConsole>();
    //const std::shared_ptr<MarqueeConsole> marqueeConsole = std::make_shared<MarqueeConsole>();
    //const std::shared_ptr<SchedulingConsole> schedulingConsole = std::make_shared<SchedulingConsole>();
    //const std::shared_ptr<MemorySimulationConsole> memoryConsole = std::make_shared<MemorySimulationConsole>();

    this->consoleTable[MAIN_CONSOLE] = mainConsole;
    //this->consoleTable[MARQUEE_CONSOLE] = marqueeConsole;
    //this->consoleTable[SCHEDULING_CONSOLE] = schedulingConsole;
    //this->consoleTable[MEMORY_CONSOLE] = memoryConsole;

    this->switchConsole(MAIN_CONSOLE);
}


