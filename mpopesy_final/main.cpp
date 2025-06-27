#include <iostream>
#include "ConsoleManager.h"
#include "MainConsole.h"
#include "ConsoleGlobals.h"

#include "Scheduler.h"
#include "Config.h"

#include "InstructionList.h"
#include "ForInstruction.h"


//extern variables store at ConsoleGlobals.h
HANDLE outConsole = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE inConsole = GetStdHandle(STD_INPUT_HANDLE);

int main() {
	/*
	// CY: scheduler debug
	Config::initConfig("config.txt");
	Scheduler::MainScheduler = new Scheduler::SchedulerClass();
	Scheduler::MainScheduler->runSchedulerTest();
	Scheduler::MainScheduler->addToQueue(new Processes::Process("HelloWorld0"));
	Scheduler::MainScheduler->addToQueue(new Processes::Process("HelloWorld1"));
	Scheduler::MainScheduler->addToQueue(new Processes::Process("HelloWorld2"));
	Scheduler::MainScheduler->addToQueue(new Processes::Process("HelloWorld3"));
	Scheduler::MainScheduler->addToQueue(new Processes::Process("HelloWorld4"));
	Scheduler::MainScheduler->addToQueue(new Processes::Process("HelloWorld5"));
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	Scheduler::MainScheduler->screenList(&std::cout);
	while (true) {};
	*/

	//bootstrap
	//initialize
	//start systerm services
	//enter main loop 
	//delete and clear memory

	/*
	ConsoleManager::initialize();
	bool OS_RUNNING = true;

	while (OS_RUNNING) {
		ConsoleManager::getInstance()->process();    // get first the process 
		ConsoleManager::getInstance()->drawConsole(); // draw the console 

		OS_RUNNING = ConsoleManager::getInstance()->isRunning();
	}

	ConsoleManager::destroy();
	return 0;
	*/
}