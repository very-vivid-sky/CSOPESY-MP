//#pragma once
//#include <atomic>
//#include <condition_variable>
//#include <queue>
//#include <thread>
//#include <unordered_map>
//#include <vector>
//#include "Process.h"
//#include "ConsoleGlobals.h"
//
//static std:: vector<Process*> runningProcesses;
//static std::vector<Process*> finishedProcesses;
//static std::queue<Process*> readyQueue;
//
//static std::mutex queueMutex;   //protects readyQueue resource
//static std::mutex coreMapMutex; //protects 
//static std::condition_variable cv;
//static std::atomic<bool> schedulerRunning(true);
//static std::atomic<bool> emulatorRunning(true);
//static std::atomic<bool> directoryCreated(false);
//
//
//class Scheduler {
//public:
//	Scheduler();
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
//public: 
//	void screen_ls();
//	void cpuWorker(int coreId);
//	String getCurrentTimeString();
//
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
//};
//
//Scheduler* MainScheduler;
