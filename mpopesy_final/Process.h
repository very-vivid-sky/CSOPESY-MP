#pragma once
#include "TypedefRepo.h"
#include "ICommand.h"
#include "AConsole.h"

/**
    Process might need to be a class because 
    it will 
*/



/*
* @brief Represents the state of a process 
*/
enum processState {
    newly,          /**< process is created */
    ready,          /**< process is waiting to be assigned to a processor {in a readyQeueu}*/
    waiting,        /**< waiting for an event {I/O or event completion}*/
    running,        /**< process is being executed*/
    terminated      /**< process has finished executing*/

};


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


//
//
//
//class Process : AConsole{
//public:
//
//    Process(const AConsole& num) : AConsole(num) {}
//    typedef std::vector<std::shared_ptr<ICommand>> CommandList;
//
//    int pid;
//    String name;
//    Time_t creationTime;
//    int totalCommands = 0;
//    int executedCommands =0;
//    bool finished;
//    Mutex mtx;
//    int currentCore; //aka cpuCoreId
//
//    int commandCounter;
//    CommandList commandList; // list of commands {print, add, etc} the process has
//    processState currentState; // current state of the process
//
//
//public: 
//
//    //virtual functions from AConsole
//    void process() override;
//    void display() override;
//    void onEnabled() override;
//    bool running = false;
//
//    //constructor 
//
//    /**
//    * @brief NOT FULLY IMPLEMENTED
//    */
//
//    /*
//    * @brief gets the CSOPESY HEADER
//    * @return const char* getHeader contents
//    */
//    const char* getHeader();
//
//    void displayHeader();
//
//
//private:
//
//};