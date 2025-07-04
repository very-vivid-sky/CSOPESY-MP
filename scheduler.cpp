#include <iostream>
#include <fstream>
#include <thread>
#include <queue>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <unordered_map>
#include <algorithm>

#include <iostream>
#include <ostream>
#include <sys/stat.h>
#include <sys/types.h>

#include "Scheduler.h"
#include "Config.h"
#include "Process.h"

using namespace Scheduler;

std::vector<Processes::Process*> Scheduler::allProcesses;
std::vector<Processes::Process*> Scheduler::runningProcesses;
std::vector<Processes::Process*> Scheduler::finishedProcesses;
std::queue<Processes::Process*> Scheduler::readyQueue;

static std::mutex queueMutex;   //protects readyQueue resource
static std::mutex coreMapMutex; //protects 
static std::mutex rpMutex;      // for runningProcesses
static std::condition_variable cv;
static std::atomic<bool> schedulerRunning(true);
static std::atomic<bool> emulatorRunning(true);
static std::atomic<bool> directoryCreated(false);

// Track which core each process is running on
static std::unordered_map<Processes::Process*, int> processCoreMap;

// Stores the main scheduler to be used throughout the OS lifetime
SchedulerClass* Scheduler::MainScheduler;

// Simulates a CPU core
static void cpuWorker(int coreId) {
    int delays_per_exec = Config::get_DELAY_PER_EXEC(); // cache here

    while (schedulerRunning) {
        Processes::Process* proc = nullptr;

        //get process from queue
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            cv.wait(lock, [] { return !readyQueue.empty(); });

            // are there even processes still?
            // if (readyQueue.empty() <= 0) { schedulerRunning = false; }
            if (!schedulerRunning) { break; };

            proc = readyQueue.front();
            readyQueue.pop();
        }

        //mark process as running
        {
            std::lock_guard<std::mutex> lock(rpMutex);
            runningProcesses.push_back(proc);
        }

        //assign core to process
        {
            std::lock_guard<std::mutex> lock(coreMapMutex);
            processCoreMap[proc] = coreId;
            proc->setCore(coreId);
        }

        // run process
        for (
            int i = 0;
            // is this either FCFS, or still enough quantums if this is RR? is it even active yet?
            ((i < MainScheduler->QUANTUM_CYCLES) || (!MainScheduler->IS_ROUND_ROBIN)) && !(proc->isFinished());
            i++)
        {
            proc->run();
            // sleep based on delays-per-exec. good night!
            // wish i can say that -cy
            std::this_thread::sleep_for(std::chrono::milliseconds(delays_per_exec));
        }

        //check if process is finished & mark, otherwise add back to queue 
        {
            std::lock_guard<std::mutex> lock(rpMutex);

            if (proc->isFinished()) {
                finishedProcesses.push_back(proc);
                std::cout << proc->getName() << "\n";
            } else {
                std::unique_lock<std::mutex> lock(queueMutex);
                readyQueue.push(proc);
            }

            runningProcesses.erase(remove(runningProcesses.begin(), runningProcesses.end(), proc), runningProcesses.end());
        }

        // remove core assignment
        {
            std::lock_guard<std::mutex> lock(coreMapMutex);
            proc->setCore(-1);
            processCoreMap.erase(proc);
        }
    }
}

// Schedules all processes in FCFS order
static void schedulerThread() {
    /*
    for (int i = 0; i < Scheduler::MainScheduler->NUM_PROCESSES; i++) {
        auto* proc = new Process;
        proc->name = "process" + (i < 9 ? "0" + to_string(i + 1) : to_string(i + 1));
        proc->creationTime = time(0);
        proc->totalCommands = MainScheduler->PRINTS_PER_PROCESS;
        proc->nextLine = 0;
        proc->pid = i;
        proc->finished = false;

        //create the process
        Processes::Process* proc = new Processes::Process("process_" + std::to_string(i + 1));

        //add the processes to a readyQueue
        {
            std::lock_guard<std::mutex> lock(queueMutex); //lock the readyQueue 
            readyQueue.push(proc);
        }

        cv.notify_one(); // Notify a CPU core , the next CPU core 
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // simulate spacing
    }
    */

    /*
    if (schedulerRunning == false) {
        schedulerRunning = true;
        while (finishedProcesses.size() < Scheduler::MainScheduler->NUM_PROCESSES) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500)); //run the processes
        }

        schedulerRunning = false;
        cv.notify_all();
    }
    */
}

// Initializes a scheduler
SchedulerClass::SchedulerClass() {
    // create a thread scheduler in FCFS order
    scheduler = std::thread(schedulerThread);
    setAddresses(&runningProcesses, &finishedProcesses, &readyQueue);
}

// FUNCTION BLOCK -- EXECUTES scheduler - test
void SchedulerClass::runSchedulerTest() {
     // For every thread, run a cpuWorker
     for (int i = 0; i < Scheduler::MainScheduler->NUM_CORES; i++) {
         cpuThreads.emplace_back(cpuWorker, i);
     }
}

// Sets addresses for global access
void SchedulerClass::setAddresses(std::vector<Processes::Process*>* addr1, std::vector<Processes::Process*>* addr2, std::queue<Processes::Process*>* addr3) {
    addr_runningProcesses = addr1;
    addr_finishedProcesses = addr2;
    addr_readyQueue = addr3;
}

// Adds a new process to the queue
void SchedulerClass::addToQueue(Processes::Process* p) {
    // resize allProcesses vector by 1000 units before hitting the limit, if necessary
    if (allProcesses.capacity() < allProcesses.size() + 5) {
        allProcesses.reserve(allProcesses.capacity() + 1000);
    }

    std::unique_lock<std::mutex> lock(queueMutex);
    readyQueue.push(p);
    allProcesses.push_back(p);

    cv.notify_all();
}

// Linear searches allProcesses to see if this name exists in allProcesses
bool SchedulerClass::processExists(std::string name) {
    for (Processes::Process* p : allProcesses) {
        if (p->getName() == name) { return true; }
    }
    return false;
}

// Linear searches and gets a process
Processes::Process* SchedulerClass::getProcess(std::string name) {
    for (Processes::Process* p : allProcesses) {
        if (p->getName() == name) { return p; }
    }
    return nullptr;
}

/*
std::vector<Processes::Process*>* SchedulerClass::getRunningProcesses() { return addr_runningProcesses; }
std::vector<Processes::Process*>* SchedulerClass::getFinishedProcesses() { return addr_finishedProcesses; }
std::queue<Processes::Process*>* SchedulerClass::getReadyQueue() { return addr_readyQueue; }
*/

// Outputs screen list
/*
void SchedulerClass::screenList(bool toFile) {
    // TODO: toFile implementation for report-util command, toggled by toFile bool

    std::cout << "-------------------------------------------------------------------------------------\n";
    std::cout << "Running processes:\n";
    for (auto* proc : runningProcesses) {
        int coreId = -1;
        {
            //lock_guard<mutex> lock(coreMapMutex);
            //if (processCoreMap.find(proc) != processCoreMap.end()) {
            //    coreId = processCoreMap[proc];
            //}
            coreId = proc->currentCore;
        }
        std::cout << proc->name << "     (" << formatTime(proc->creationTime) << ")       "
            << "Core: " << to_string(coreId)
            << "         " << proc->nextLine << " / " << proc->totalCommands << "\n";
    }

    std::cout << "\nFinished processes:\n";
    for (auto* proc : finishedProcesses) {
        std::cout << proc->name << "     (" << formatTime(proc->creationTime) << ")       Finished         "
            << proc->nextLine << " / " << proc->totalCommands << "\n";
    }
    std::cout << "-------------------------------------------------------------------------------------\n";

}
*/

void SchedulerClass::screenList(std::ostream *stream) {
    *stream << "-------------------------------------------------------------------------------------\n\n";
    {
        std::lock_guard<std::mutex> lock(coreMapMutex);

        int cores_used = runningProcesses.size();
        int cores_avail = Config::get_NUM_CPU() - cores_used;
        float cpu_util = cores_used / Config::get_NUM_CPU();
        *stream << "CPU utilization: " << (int)(cpu_util*100) << "%\n";
        *stream << "Cores being used: " << cores_used << "\n";
        *stream << "Cores available: " << cores_avail << "\n\n";

        *stream << "Running processes:\n";
        for (Processes::Process* proc : runningProcesses) {
            *stream
                << proc->getName()
                << " (" << proc->getFormattedCreationTime()
                << ") Core: " << proc->getCore() << " Progress: ("
                << proc->getCurrentLine() << "/" << proc->getTotalCommands()
                << ")\n";
        };
        *stream << "\nFinished processes:\n";
        for (Processes::Process* proc : finishedProcesses) {
            *stream
                << proc->getName()
                << " (" << proc->getFormattedCreationTime()
                << ") Progress: ("
                << proc->getCurrentLine() << "/" << proc->getTotalCommands()
                << ")\n";
        };
    }
    *stream << "\n-------------------------------------------------------------------------------------\n";
}

void SchedulerClass::writeReport() {
    std::ofstream logFile("csopesy_log.txt", std::ios::trunc);
    screenList(&logFile);
    logFile.close();
}