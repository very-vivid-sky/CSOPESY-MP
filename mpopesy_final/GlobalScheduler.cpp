//#include <iostream>
//#include <fstream>
//#include <thread>
//#include <queue>
//#include <vector>
//#include <mutex>
//#include <condition_variable>
//#include <atomic>
//#include <chrono>
//#include <ctime>
//#include <iomanip>
//#include <sstream>
//#include <unordered_map>
//#include <algorithm>
//#include <sys/stat.h>
//#include <sys/types.h>
//#include "GlobalScheduler.h"
//#include "TypedefRepo.h"
//#include "Process.h"
////#include <bits/stdc++.h>
//#include <filesystem>
//#include <time.h>
//
//static std::vector<Process*> runningProcesses;
//static std::vector<Process*> finishedProcesses;
//static std::queue<Process*> readyQueue;
//
//static Mutex queueMutex;   //protects readyQueue resource
//static Mutex coreMapMutex; //protects 
//static std::condition_variable cv;
//static std::atomic<bool> schedulerRunning(true);
//static std::atomic<bool> emulatorRunning(true);
//static std::atomic<bool> directoryCreated(false);
//
//// Track which core each process is running on
//static std::unordered_map<Process*, int> processCoreMap;
//
//
//
////GlobalScheduler 
//GlobalScheduler* GlobalScheduler::sharedInstance = nullptr;
//
//
//String getCurrentTimeString() {
//    std::time_t now = std::time(nullptr);
//    std::tm storeNow;
//    char now_c[24];
//    //store time 
//    localtime_s(&storeNow, &now);
//    strftime(now_c, sizeof(now_c), "%m/%d/%Y, %I:%M:%S %p", &storeNow);
//    return std::string(now_c);
//}
//
//// Simulates a CPU core
//static void cpuWorker(int coreId) {
//    while (schedulerRunning) {
//        Process* proc = nullptr;
//
//        //get process from queue
//        {
//            std::unique_lock<Mutex> lock(queueMutex);
//            cv.wait(lock, [] { return !readyQueue.empty() || !schedulerRunning; });
//
//            if (!schedulerRunning) break;
//
//            proc = readyQueue.front();
//            readyQueue.pop();
//        }
//
//        //mark process as running
//        {
//            std::lock_guard<Mutex> lock(proc->mtx);
//            runningProcesses.push_back(proc);
//        }
//
//        //assign core to process
//        {
//            std::lock_guard<Mutex> lock(coreMapMutex);
//            processCoreMap[proc] = coreId;
//            proc->currentCore = coreId;
//        }
//
//        //simulate logging{} 
//        {
//            std::lock_guard<Mutex> lock(proc->mtx);
//            String foldername = "./processes/";
//
//
//            // Creating a directory 
//            if (!directoryCreated) {
//                std::filesystem::create_directories("processes");
//                directoryCreated = true;
//            }
//
//
//            String filename = foldername + proc->name + ".txt";
//            std::ofstream logFile(filename, std::ios::app);
//            if (!logFile.is_open()) {
//                std::cerr << "Failed to open log file: " << filename << "\n";
//                break;
//            }
//            else {
//                // header
//                logFile << "Process name: " + proc->name + "\n";
//                logFile << "Logs:\n" << "\n";
//
//                while (proc->executedCommands < proc->totalCommands)
//                {
//                    String timestamp = getCurrentTimeString();
//                    logFile << "(" << timestamp + ") \tCore: " + std::to_string(coreId) + "\t\"Hello World from " + proc->name + "!\"\n";
//                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
//                    proc->executedCommands++;
//                }
//                logFile.close();
//            }
//
//        }
//
//        //mark process as finished 
//        {
//            std::lock_guard<Mutex> lock(proc->mtx);
//            proc->finished = true;
//            finishedProcesses.push_back(proc);
//            runningProcesses.erase(remove(runningProcesses.begin(), runningProcesses.end(), proc), runningProcesses.end());
//        }
//
//        // remove core assignment
//        {
//            std::lock_guard<Mutex> lock(coreMapMutex);
//            proc->currentCore = -1;
//            processCoreMap.erase(proc);
//        }
//    }
//}
//
//// Creates and schedules all processes in FCFS order
//static void schedulerThread() {
//    for (int i = 0; i < MainScheduler->NUM_PROCESSES; i++) {
//        //create the process
//        auto* proc = new Process;
//        proc->name = "process" + (i < 9 ? "0" + std::to_string(i + 1) : std::to_string(i + 1));
//        proc->creationTime = time(0);
//        proc->totalCommands = MainScheduler->PRINTS_PER_PROCESS;
//        proc->executedCommands = 0;
//        proc->pid = i;
//        proc->finished = false;
//
//        //add the processes to a readyQueue
//        {
//            std::lock_guard<std::mutex> lock(queueMutex); //lock the readyQueue 
//            readyQueue.push(proc);
//        }
//
//        cv.notify_one(); // Notify a CPU core , the next CPU core 
//        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate spacing
//    }
//
//    while (finishedProcesses.size() < MainScheduler->NUM_PROCESSES) {
//        std::this_thread::sleep_for(std::chrono::milliseconds(500)); //run the processes
//    }
//
//    schedulerRunning = false;
//    cv.notify_all();
//}
//
//// Display running/finished processes
///*
//void screen_ls() {
//    cout << "-------------------------------------------------------------------------------------\n";
//    cout << "Running processes:\n";
//    for (auto* proc : runningProcesses) {
//        int coreId = -1;
//        {
//            lock_guard<mutex> lock(coreMapMutex);
//            if (processCoreMap.find(proc) != processCoreMap.end()) {
//                coreId = processCoreMap[proc];
//            }
//        }
//        cout << proc->name << "     (" << getCurrentTimeString() << ")       "
//            << "Core: " << coreId
//            << "         " << proc->executedCommands << " / " << proc->totalCommands << "\n";
//    }
//
//    cout << "\nFinished processes:\n";
//    for (auto* proc : finishedProcesses) {
//        cout << proc->name << "     (" << getCurrentTimeString() << ")       Finished         "
//            << proc->executedCommands << " / " << proc->totalCommands << "\n";
//    }
//    cout << "-------------------------------------------------------------------------------------\n";
//}
//*/
//
//// FUNCTION BLOCK -- EXECUTES scheduler - test
//void GlobalScheduler::runSchedulerTest() {
//    // create a thread scheduler in FCFS order
//    std::thread scheduler(schedulerThread);
//
//    // a vector of CPU cores thread
//    std::vector<std::thread> cpuThreads;
//
//    // start process for running cores
//    for (int i = 0; i < NUM_CORES; i++) {
//        cpuThreads.emplace_back(cpuWorker, i);
//    }
//
//    // lambda : no capture && no params
//    // global variables :
//    //  @schedulerRunning   ,   atomic<bool>
//    //  @readyQueue         ,   queue<Process*>
//    //  @runningProcesses   ,   vector<Process*>
//    // the monitor thread keeps on running the screen_ls()
//    // while the scheduler is running, the readyQueue is not empty
//    // all processes are not done executing
//    std::thread monitor([]() {
//
//        std::string inputCommand;
//        while (schedulerRunning || !readyQueue.empty() || !runningProcesses.empty() ) {
//            //screen_ls();
//
//            std::cout<< "\nEnter command: " ;
//            std::cin>>inputCommand;// >> inputCommand;
//            if(inputCommand == "screen-ls")
//            {
//                //screen_ls();
//            }else{
//                std::cout<< "Doing something" << std::endl;
//            }
//            std::this_thread::sleep_for(std::chrono::milliseconds(500));
//        }
//        });
//       // screen_ls();
//
//
//    //synchronize threads
//    scheduler.join();
//    for(auto& t : cpuThreads) {
//        t.join();   //ensure the CPU cores are done running the processes
//    }
//
//    monitor.join(); // ensures all logging are finished
//    std::cout << "All processes finished execution.\n";
//}
//
//
//
//// Initializes a scheduler
//GlobalScheduler::GlobalScheduler() {
//    // create a thread scheduler in FCFS order
//    scheduler = std::thread(schedulerThread);
//    setAddresses(&runningProcesses, &finishedProcesses, &readyQueue);
//
//}
//
//
//// Sets addresses for global access
//void GlobalScheduler::setAddresses(std::vector<Process*>* addr1, std::vector<Process*>* addr2, std::queue<Process*>* addr3) {
//    addr_runningProcesses = addr1;
//    addr_finishedProcesses = addr2;
//    addr_readyQueue = addr3;
//}
//
//std::vector<Process*>* GlobalScheduler::getRunningProcesses() { return addr_runningProcesses; }
//std::vector<Process*>* GlobalScheduler::getFinishedProcesses() { return addr_finishedProcesses; }
//std::queue<Process*>* GlobalScheduler::getReadyQueue() { return addr_readyQueue; }
//
//// Outputs screen list
//void GlobalScheduler::screenList(bool toFile) {
//    // TODO: toFile implementation for report-util command, toggled by toFile bool
//
//    std::cout << "-------------------------------------------------------------------------------------\n";
//    std::cout << "Running processes:\n";
//    for (auto* proc : runningProcesses) {
//        int coreId = -1;
//        {
//            /*
//            lock_guard<mutex> lock(coreMapMutex);
//            if (processCoreMap.find(proc) != processCoreMap.end()) {
//                coreId = processCoreMap[proc];
//            }
//            */
//            coreId = proc->currentCore;
//        }
//        std::cout << proc->name << "     (" << getCurrentTimeString() << ")       "
//            << "Core: " << std::to_string(coreId)
//            << "         " << proc->executedCommands << " / " << proc->totalCommands << "\n";
//    }
//
//    std::cout << "\nFinished processes:\n";
//    for (auto* proc : finishedProcesses) {
//        std::cout << proc->name << "     (" << getCurrentTimeString() << ")       Finished         "
//            << proc->executedCommands << " / " << proc->totalCommands << "\n";
//    }
//    std::cout << "-------------------------------------------------------------------------------------\n";
//
//}
//
//
//GlobalScheduler* GlobalScheduler::getInstance() {
//    if (sharedInstance == nullptr) {
//        sharedInstance = new GlobalScheduler();
//    }
//
//    return sharedInstance;
//}
//
//void GlobalScheduler::initialize() {
//    sharedInstance = new GlobalScheduler();
//}
//
//void GlobalScheduler::destroy() {
//    delete sharedInstance;
//};
