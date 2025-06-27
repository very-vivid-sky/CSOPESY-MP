//#pragma once
//#include <atomic>
//#include <condition_variable>
//#include <queue>
//#include <thread>
//#include <unordered_map>
//#include <vector>
//
//#include "Process.h"
//
//class GlobalScheduler {
//public:
//
//	void runSchedulerTest();
//	void setAddresses(std::vector<Process*>* addr1, std::vector<Process*>* addr2, std::queue<Process*>* addr3);
//	std::vector<Process*>* getRunningProcesses();
//	std::vector<Process*>* getFinishedProcesses();
//	std::queue<Process*>* getReadyQueue();
//
//	const int NUM_CORES = 4;
//	const int NUM_PROCESSES = 10;
//	const int PRINTS_PER_PROCESS = 100;
//
//	void screenList(bool toFile);
//
//	static GlobalScheduler* getInstance();
//	void initialize();
//	void destroy();
//private:
//	std::vector<std::thread> cpuThreads;
//	std::thread scheduler;
//
//	std::vector<Process*>* addr_runningProcesses;
//	std::vector<Process*>* addr_finishedProcesses;
//	std::queue<Process*>* addr_readyQueue;
//
//	// Track which core each process is running on
//	std::unordered_map<Process*, int> processCoreMap;
//
//
//	// 
//	GlobalScheduler();
//	~GlobalScheduler() = default;
//	GlobalScheduler(GlobalScheduler const&) = delete;             //Explicitly deletes the copy constructor for the ConsoleManager  ; prevents copying via constructor
//	GlobalScheduler& operator=(GlobalScheduler const&) = delete; //Explicitly deletes copy assignment operator ; prevents assignment from another instance
//	static GlobalScheduler* sharedInstance;
//
//
//
//};
//
//GlobalScheduler* MainScheduler;