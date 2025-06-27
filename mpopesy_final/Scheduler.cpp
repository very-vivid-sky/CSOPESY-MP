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
//#include <cassert>
//#include <cstdlib>
//#include <filesystem>
//
////#include <bits/stdc++.h>
//#include <sys/stat.h>
//#include <sys/types.h>
//#include "Scheduler.h"
//
//
//// Sets addresses for global access
//void Scheduler::setAddresses(std::vector<Process*>* addr1, std::vector<Process*>* addr2, std::queue<Process*>* addr3) {
//    addr_runningProcesses = addr1;
//    addr_finishedProcesses = addr2;
//    addr_readyQueue = addr3;
//}
//
//std::vector<Process*>* Scheduler::getRunningProcesses() { return addr_runningProcesses; }
//std::vector<Process*>* Scheduler::getFinishedProcesses() { return addr_finishedProcesses; }
//std::queue<Process*>* Scheduler::getReadyQueue() { return addr_readyQueue; }
//// Track which core each process is running on
//static std::unordered_map<Process*, int> processCoreMap;
//
//String Scheduler::getCurrentTimeString() {
//    std::time_t now = time(0);
//    char now_c[24];
//    std::strftime(now_c, 24, "%m/%d/%Y, %I:%M:%S %p", std::localtime(&now));
//    return std::string(now_c);
//}
//
//// Simulates a CPU core
//void Scheduler::cpuWorker(int coreId) {
//    while (schedulerRunning) {
//        Process* proc = nullptr;
//
//        //get process from queue
//        {
//            std::unique_lock<std::mutex> lock(queueMutex);
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
//            std::lock_guard<std::mutex> lock(proc->mtx);
//            runningProcesses.push_back(proc);
//        }
//
//        //assign core to process
//        {
//            std::lock_guard<std::mutex> lock(coreMapMutex);
//            processCoreMap[proc] = coreId;
//            proc->currentCore = coreId;
//        }
//
//        //simulate logging{} 
//        {
//            std::lock_guard<std::mutex> lock(proc->mtx);
//            std::string foldername = "./processes/";
//
//
//            // Creating a directory
//            if (!directoryCreated) {
//                std::filesystem::create_directory(foldername);
//                directoryCreated = true;
//            }
//
//
//            std::string filename = foldername + proc->name + ".txt";
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
//                    std::string timestamp = getCurrentTimeString();
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
//            std::lock_guard<std::mutex> lock(proc->mtx);
//            proc->finished = true;
//            finishedProcesses.push_back(proc);
//            runningProcesses.erase(remove(runningProcesses.begin(), runningProcesses.end(), proc), runningProcesses.end());
//        }
//
//        // remove core assignment
//        {
//            std::lock_guard<std::mutex> lock(coreMapMutex);
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
//
//void Scheduler::screen_ls() {
//    std::cout << "-------------------------------------------------------------------------------------\n";
//    std::cout << "Running processes:\n";
//    for (auto* proc : runningProcesses) {
//        int coreId = -1;
//        {
//            std::lock_guard<std::mutex> lock(coreMapMutex);
//            if (processCoreMap.find(proc) != processCoreMap.end()) {
//                coreId = processCoreMap[proc];
//            }
//        }
//        std::cout << proc->name << "     (" << getCurrentTimeString() << ")       "
//            << "Core: " << coreId
//            << "         " << proc->executedCommands << " / " << proc->totalCommands << "\n";
//    }
//
//    std::cout << "\nFinished processes:\n";
//    for (auto* proc : finishedProcesses) {
//        std::cout << proc->name << "     (" << getCurrentTimeString() << ")       Finished         "
//            << proc->executedCommands << " / " << proc->totalCommands << "\n";
//    }
//    std::cout << "-------------------------------------------------------------------------------------\n";
//}
//
//
//// FUNCTION BLOCK -- EXECUTES scheduler - test
//void Scheduler::runSchedulerTest() {
//    // create a thread scheduler in FCFS order
//    std::thread scheduler(schedulerThread);
//
//    // a vector of CPU cores thread
//    std::vector<std::thread> cpuThreads;
//
//    // start process for running cores
//    for (int i = 0; i < this->NUM_CORES; i++) {
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
//            if(inputCommand == "screen-ls"){
//                std::cout << "Doing something on screen-ls" << std::endl;
//               // Scheduler::screen_ls();
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
//    for (auto& t : cpuThreads) {
//        t.join();   //ensure the CPU cores are done running the processes
//    }
//
//    monitor.join(); // ensures all logging are finished
//    std::cout << "All processes finished execution.\n";
//}
//
//
//// Initializes a scheduler
//Scheduler::Scheduler() {
//    // create a thread scheduler in FCFS order
//    scheduler = std::thread(schedulerThread);
//    setAddresses(&runningProcesses, &finishedProcesses, &readyQueue);
//}
//
//// Outputs screen list
//void Scheduler::screenList(bool toFile) {
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