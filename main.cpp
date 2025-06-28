#include <iostream>
#include "ConsoleManager.h"
#include "MainConsole.h"
#include "ConsoleGlobals.h"

#include "ProcessBuilder.h"
#include "Scheduler.h"
#include "Config.h"

#include "Process.h"


//extern variables store at ConsoleGlobals.h
HANDLE outConsole = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE inConsole = GetStdHandle(STD_INPUT_HANDLE);

bool OS_RUNNING = true;

int main() {


	//bootstrap
	//initialize
	//start systerm services
	//enter main loop 
	//delete and clear memory

	ConsoleManager::initialize();
	Scheduler::MainScheduler = new Scheduler::SchedulerClass();
	Scheduler::MainScheduler->runSchedulerTest();

	while (OS_RUNNING) {
		ConsoleManager::getInstance()->process();    // get first the process 
		ConsoleManager::getInstance()->drawConsole(); // draw the console 

		OS_RUNNING = ConsoleManager::getInstance()->isRunning();
	}

	ConsoleManager::destroy();
	return 0;
}