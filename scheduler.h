#pragma once

#include <atomic>
#include <condition_variable>
#include <ostream>
#include <queue>
#include <thread>
#include <unordered_map>
#include <vector>

#include "Config.h"
#include "Process.h"

namespace Scheduler {
	class SchedulerClass {
	public:
		SchedulerClass();
		void runSchedulerTest();
		void setAddresses(std::vector<Processes::Process*>* addr1, std::vector<Processes::Process*>* addr2, std::queue<Processes::Process*>* addr3);
		void addToQueue(Processes::Process* p);
		// std::vector<Processes::Process*>* getRunningProcesses();
		// std::vector<Processes::Process*>* getFinishedProcesses();
		// std::queue<Processes::Process*>* getReadyQueue();

		const int NUM_CORES = Config::get_NUM_CPU();
		const int QUANTUM_CYCLES = Config::get_QUANTUM_CYCLES();
		const bool IS_ROUND_ROBIN = (Config::get_SCHEDULER() == SchedulerTypes::rr);

		const int NUM_PROCESSES = 10;
		const int PRINTS_PER_PROCESS = 100;

		void screenList(std::ostream* stream);

	private:
		std::vector<std::thread> cpuThreads;
		std::thread scheduler;

		std::vector<Processes::Process*>* addr_runningProcesses;
		std::vector<Processes::Process*>* addr_finishedProcesses;
		std::queue<Processes::Process*>* addr_readyQueue;

		// Track which core each process is running on
		std::unordered_map<Processes::Process*, int> processCoreMap;
	};

	extern SchedulerClass* MainScheduler;
	extern std::vector<Processes::Process*> runningProcesses;
	extern std::vector<Processes::Process*> finishedProcesses;
	extern std::queue<Processes::Process*> readyQueue;

};