#include <chrono>
#include <thread>
#include "Process.h"
#include "Scheduler.h"

#include "ProcessBuilder.h"

using namespace Scheduler;

// slot for the scheduler
std::thread* Scheduler::processBuilderThread;

// Switch off to end the generateProcesses() thread
bool Scheduler::runGenerator = false;

// Current process number, never should reset
// unless you are running this for longer than you should
unsigned long long Scheduler::currProcessNumber = 0;

// Builds processes automatically for the scheduler per CPU tick
// Meant to be used in a thread
void Scheduler::processBuilderFunc() {
	int perTicks = Config::get_BATCH_PROCESS_FREQ();
	Scheduler::runGenerator = true;

	// loop and create a new thread every perTicks ticks
	while (Scheduler::runGenerator) {
		Scheduler::MainScheduler->addToQueue(new Processes::Process("prc_" + std::to_string(currProcessNumber)));
		currProcessNumber++;
		std::this_thread::sleep_for(std::chrono::milliseconds(perTicks));
	}
}

// Thread wrapper for the processBuilderFunc(); runs the thread
void Scheduler::processBuilder() {
	if (Scheduler::runGenerator == false) {
		Scheduler::processBuilderThread = new Thread(Scheduler::processBuilderFunc);
	}
}