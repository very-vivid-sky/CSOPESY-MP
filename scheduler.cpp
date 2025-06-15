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

#include <bits/stdc++.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>

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


mutex queueMutex;   //protects readyQueue resource
mutex coreMapMutex; //protects 
condition_variable cv;
atomic<bool> schedulerRunning(true);
atomic<bool> emulatorRunning(true);
atomic<bool> directoryCreated(false);



// Track which core each process is running on
unordered_map<Process*, int> processCoreMap;

string getCurrentTimeString() {
    time_t now = time(0);
    char now_c[24];
    strftime(now_c, 24, "%m/%d/%Y, %I:%M:%S %p", localtime(&now));
    return std::string(now_c);
}

// Simulates a CPU core
void cpuWorker(int coreId) {
        while (schedulerRunning) {
            Process* proc = nullptr;

            //get process from queue
            {
                unique_lock<mutex> lock(queueMutex);
                cv.wait(lock, [] { return !readyQueue.empty() || !schedulerRunning; });

                if (!schedulerRunning) break;

                proc = readyQueue.front();
                readyQueue.pop();
            }

            //mark process as running
            {
                lock_guard<mutex> lock(proc->mtx);
                runningProcesses.push_back(proc);
            }

            //assign core to process
            {
                lock_guard<mutex> lock(coreMapMutex);
                processCoreMap[proc] = coreId;
            }

            //simulate logging{} 
            {
                lock_guard<mutex> lock(proc->mtx);
				string foldername = "./processes/";
                
				
				// Creating a directory
				if(!directoryCreated){
					mkdir("processes");
					directoryCreated = true;
				}

					
				string filename = foldername + proc->name + ".txt";
                ofstream logFile(filename, ios::app);
                if (!logFile.is_open()) {
                    std::cerr << "Failed to open log file: " << filename << std::endl;
                    break; 
                }else{
                    while (proc->executedCommands < proc->totalCommands) 
                    {
                        string timestamp = getCurrentTimeString();
                        logFile << timestamp + "\tCore: " + to_string(coreId) + "\t\"Hello World from " + proc->name + "!\"\n";
                        this_thread::sleep_for(chrono::milliseconds(50));
                        proc->executedCommands++;
                    }
                    logFile.close();
                }

            }
                
            //mark process as finished 
            {
                lock_guard<mutex> lock(proc->mtx);
                proc->finished = true;
                finishedProcesses.push_back(proc);
                runningProcesses.erase(remove(runningProcesses.begin(), runningProcesses.end(), proc), runningProcesses.end());
            }

            // remove core assignment
            {
                lock_guard<mutex> lock(coreMapMutex);
                processCoreMap.erase(proc);
            }
        }
}

// Creates and schedules all processes in FCFS order
void schedulerThread() {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        //create the process
        auto* proc = new Process;
        proc->name = "process" + (i < 9 ? "0" + to_string(i + 1) : to_string(i + 1));
        proc->creationTime = time(0);
        proc->totalCommands = PRINTS_PER_PROCESS;
        proc->executedCommands = 0;
        proc->pid = i;
        proc->finished = false;

        //add the processes to a readyQueue
        {
            lock_guard<mutex> lock(queueMutex); //lock the readyQueue 
            readyQueue.push(proc);
        }

        cv.notify_one(); // Notify a CPU core , the next CPU core 
        this_thread::sleep_for(chrono::milliseconds(500)); // simulate spacing
    }

    while (finishedProcesses.size() < NUM_PROCESSES) {
        this_thread::sleep_for(chrono::milliseconds(500)); //run the processes
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
        cout << proc->name << "     (" << getCurrentTimeString() << ")       "
            << "Core: " << coreId
            << "         " << proc->executedCommands << " / " << proc->totalCommands << "\n";
    }

    cout << "\nFinished processes:\n";
    for (auto* proc : finishedProcesses) {
        cout << proc->name << "     (" << getCurrentTimeString() << ")       Finished         "
            << proc->executedCommands << " / " << proc->totalCommands << "\n";
    }
    cout << "-------------------------------------------------------------------------------------\n";
}

// FUNCTION BLOCK -- EXECUTES scheduler - test
void runSchedulerTest() {
    // create a thread scheduler in FCFS order
    thread scheduler(schedulerThread); 

    // a vector of CPU cores thread
    vector<thread> cpuThreads;

    // start process for running cores
    for (int i = 0; i < NUM_CORES; i++) {
        cpuThreads.emplace_back(cpuWorker, i);
    }

    // lambda : no capture && no params 
    // global variables : 
    //  @schedulerRunning   ,   atomic<bool> 
    //  @readyQueue         ,   queue<Process*>
    //  @runningProcesses   ,   vector<Process*> 
    // the monitor thread keeps on running the screen_ls() 
    // while the scheduler is running, the readyQueue is not empty 
    // all processes are not done executing
    thread monitor([]() {

        std::string inputCommand; 
        while (schedulerRunning || !readyQueue.empty() || !runningProcesses.empty() ) {
            //screen_ls();

            std::cout<< "\nEnter command: " ;
            cin>>inputCommand;// >> inputCommand; 
            if(inputCommand == "screen-ls")
            {
                screen_ls();
            }else{
                cout<< "Doing something" << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(500));
        }
        });
       // screen_ls();
    
        
    //synchronize threads
    scheduler.join();
    for (auto& t : cpuThreads) {
        t.join();   //ensure the CPU cores are done running the processes
    }

    monitor.join(); // ensures all logging are finished
    cout << "All processes finished execution.\n";
}
