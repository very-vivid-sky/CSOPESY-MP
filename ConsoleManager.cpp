#include "Process.h"
#include "ConsoleManager.h"
#include "MainConsole.h"
#include "ScreenConsole.h"
#include "MarqueeConsole.h"
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



void ConsoleManager::process() const {

    this->currentConsole->process();

};

void ConsoleManager::switchConsole(String consoleName) {

    // check if the next console exists in the console 
    if (this->consoleTable.contains(consoleName)) {

        system("cls");
        this->previousConsole = this->currentConsole;
        this->currentConsole = this->consoleTable.at(consoleName);
        this->currentConsole->onEnabled();
    }
    else {
        std::cerr << "Console name " << consoleName << "not found. Was it initialized?";
    }

};

void ConsoleManager::returnToPreviousConsole() {
    this->tempConsole = this->currentConsole;       // tempConsole stores currentConsole
    this->currentConsole = this->previousConsole;   // previousConsole becomes currentConsole
    this->previousConsole = this->tempConsole;      // previousConsole stores tempConsole
    system("cls");
    switchConsole(this->currentConsole->getName());

    ConsoleManager::getInstance()->process();    // get first the process 
    ConsoleManager::getInstance()->drawConsole(); // draw the console 
};

void ConsoleManager::exitApplication() {
    std::cout << "Doing something";

};

void ConsoleManager::unregisterScreen() {
    std::cout << "Doing something";

};

bool ConsoleManager::isRunning() const {
    return this->running;
};

void ConsoleManager::setCursorPosition(int posX, int posY) const {

    std::cout << "Doing something";
};


void ConsoleManager::refresh() {
    system("cls");
}


void ConsoleManager::stopRunning() {
    this->running = false;
}


void ConsoleManager::addConsole(String newconsoleName) {
    auto found = this->consoleTable.find(newconsoleName);
    if (found == this->consoleTable.end()) {

        //create the process
        Processes::Process* proc = new Processes::Process(newconsoleName);

        //add the process to list of proceses already 

        //create the console with the process
        const std::shared_ptr<ScreenConsole> consoleNew = std::make_shared<ScreenConsole>(proc);
        this->consoleTable[newconsoleName] = consoleNew;
        this->switchConsole(newconsoleName);
    }

}


void ConsoleManager::closeConsoleAndReturnToPrevious() {
    this->tempConsole = this->currentConsole;       // tempConsole stores currentConsole
    this->currentConsole = this->previousConsole;   // previousConsole becomes currentConsole
    this->previousConsole = this->tempConsole;      // previousConsole stores tempConsole
    system("cls");
    switchConsole(this->currentConsole->getName());
    this->consoleTable.erase(this->tempConsole->getName()); //closes the console

    ConsoleManager::getInstance()->process();    // get first the process 
    ConsoleManager::getInstance()->drawConsole(); // draw the console 
}

//constructor
ConsoleManager::ConsoleManager() {
    this->running = true;

    const std::shared_ptr<MainConsole> mainConsole = std::make_shared<MainConsole>();
    const std::shared_ptr<MarqueeConsole> marqueeConsole = std::make_shared<MarqueeConsole>();
    //const std::shared_ptr<SchedulingConsole> schedulingConsole = std::make_shared<SchedulingConsole>();

    this->consoleTable[MAIN_CONSOLE] = mainConsole;
    this->consoleTable[MARQUEE_CONSOLE] = marqueeConsole;
    //this->consoleTable[SCHEDULING_CONSOLE] = schedulingConsole;

    this->switchConsole(MAIN_CONSOLE); //opens main console

    //cy's implementation
    /*size = s;
    allConsoles = new AConsole * [size];
    activeConsoles = new bool[size];

    // cleanup of garbage data
    for (int i = 0; i < size; i++) {
        activeConsoles[i] = false;
    }

    this->addConsole(new MainConsole());
    mainMenu = allConsoles[0];
    currentConsole = mainMenu;*/
}


bool ConsoleManager::findConsole(std::string consoleName) {
    auto consoleFound = consoleTable.find(consoleName);
    bool found = false; 
    if (consoleFound != consoleTable.end()) {
        found = true;
    }
    return found;
}
