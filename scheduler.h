#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <atomic>
#include <condition_variable>
#include <queue>
#include <thread>
#include <unordered_map>
#include <vector>

using namespace std;

struct Process {
    string name;
    time_t creationTime;
    int totalCommands;
    int executedCommands;
    int pid;
    bool finished;
    mutex mtx;
	
	int currentCore;
};

class Scheduler {
	public:
		Scheduler();
		void runSchedulerTest();
		void setAddresses(vector<Process*>* addr1, vector<Process*>* addr2, queue<Process*>* addr3);
		vector<Process*>* getRunningProcesses();
		vector<Process*>* getFinishedProcesses();
		queue<Process*>* getReadyQueue();

		const int NUM_CORES = 4;
		const int NUM_PROCESSES = 10;
		const int PRINTS_PER_PROCESS = 100;

		void screenList(bool toFile);

	private:
		vector<thread> cpuThreads;
		thread scheduler;

		vector<Process*>* addr_runningProcesses;
		vector<Process*>* addr_finishedProcesses;
		queue<Process*>* addr_readyQueue;

		// Track which core each process is running on
		unordered_map<Process*, int> processCoreMap;
};

Scheduler* MainScheduler;

#include "scheduler.cpp"

#endif