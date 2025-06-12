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

#define NUM_CORES 4
#define NUM_PROCESSES 10
#define PRINTS_PER_PROCESS 100

using namespace std;

struct Process {
    string name;
    time_t creationTime;
    int totalCommands;
    int executedCommands;
    int pid;
    bool finished;
    mutex mtx;
};

vector<Process*> runningProcesses;
vector<Process*> finishedProcesses;
queue<Process*> readyQueue;

mutex queueMutex;
mutex coreMapMutex;
condition_variable cv;
atomic<bool> schedulerRunning(true);
atomic<bool> emulatorRunning(true);

// Track which core each process is running on
unordered_map<Process*, int> processCoreMap;

string getCurrentTimeString() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << put_time(ltm, "(%m/%d/%Y %I:%M:%S%p)");
    return ss.str();
}

// Simulates a CPU core
void cpuWorker(int coreId) {
    while (schedulerRunning) {
        Process* proc = nullptr;

        {
            unique_lock<mutex> lock(queueMutex);
            cv.wait(lock, [] { return !readyQueue.empty() || !schedulerRunning; });

            if (!schedulerRunning) break;

            proc = readyQueue.front();
            readyQueue.pop();
        }

        {
            lock_guard<mutex> lock(proc->mtx);
            runningProcesses.push_back(proc);
        }

        {
            lock_guard<mutex> lock(coreMapMutex);
            processCoreMap[proc] = coreId;
        }

        string filename = proc->name + ".txt";
        ofstream logFile(filename, ios::app);

        while (proc->executedCommands < proc->totalCommands) {
            string timestamp = getCurrentTimeString();
            logFile << timestamp << "\tCore: " << coreId << "\t\"Hello World from " << proc->name << "!\"\n";
            this_thread::sleep_for(chrono::milliseconds(10));
            proc->executedCommands++;
        }

        logFile.close();

        {
            lock_guard<mutex> lock(proc->mtx);
            proc->finished = true;
            finishedProcesses.push_back(proc);
            runningProcesses.erase(remove(runningProcesses.begin(), runningProcesses.end(), proc), runningProcesses.end());
        }

        {
            lock_guard<mutex> lock(coreMapMutex);
            processCoreMap.erase(proc);
        }
    }
}

// Schedules all processes in FCFS order
void schedulerThread() {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        auto* proc = new Process;
        proc->name = "process" + (i < 9 ? "0" + to_string(i + 1) : to_string(i + 1));
        proc->creationTime = time(0);
        proc->totalCommands = PRINTS_PER_PROCESS;
        proc->executedCommands = 0;
        proc->pid = i;
        proc->finished = false;

        {
            lock_guard<mutex> lock(queueMutex);
            readyQueue.push(proc);
        }

        cv.notify_one(); // Notify a CPU core
        this_thread::sleep_for(chrono::milliseconds(100)); // simulate spacing
    }

    while (finishedProcesses.size() < NUM_PROCESSES) {
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    schedulerRunning = false;
    cv.notify_all();
}

// Display running/finished processes
void screen_ls() {
    cout << "-------------------------------------------------------------------------------------\n";
    cout << "Running processes:\n";
    for (auto* proc : runningProcesses) {
        int coreId = -1;
        {
            lock_guard<mutex> lock(coreMapMutex);
            if (processCoreMap.find(proc) != processCoreMap.end()) {
                coreId = processCoreMap[proc];
            }
        }
        cout << proc->name << "     " << getCurrentTimeString() << "       "
            << "Core: " << coreId
            << "         " << proc->executedCommands << " / " << proc->totalCommands << "\n";
    }

    cout << "\nFinished processes:\n";
    for (auto* proc : finishedProcesses) {
        cout << proc->name << "     " << getCurrentTimeString() << "       Finished         "
            << proc->executedCommands << " / " << proc->totalCommands << "\n";
    }
    cout << "--------------------------------------------------------------------------------------------\n";
}


    void runSchedulerTest() {
        thread scheduler(schedulerThread);

        vector<thread> cpuThreads;
        for (int i = 0; i < NUM_CORES; i++) {
            cpuThreads.emplace_back(cpuWorker, i);
        }

        scheduler.join();
        for (auto& t : cpuThreads) {
            t.join();
        }

        cout << "All processes finished execution.\n";
    }
