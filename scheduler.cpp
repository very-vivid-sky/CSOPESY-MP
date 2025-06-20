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
#include <config.h>

using namespace std;

static vector<Process*> runningProcesses;
static vector<Process*> finishedProcesses;
static queue<Process*> readyQueue;

static mutex queueMutex;   //protects readyQueue resource
static mutex coreMapMutex; //protects 
static condition_variable cv;
static atomic<bool> schedulerRunning(true);
static atomic<bool> emulatorRunning(true);
static atomic<bool> directoryCreated(false);
static int quantumCycles = Config::get_QUANTUM_CYCLES();
static bool isRoundRobin = (Config::get_SCHEDULER() == SchedulerTypes::rr);

// Track which core each process is running on
static unordered_map<Process*, int> processCoreMap;

string formatTime(time_t time) {
    char time_c[24];
    strftime(time_c, 24, "%m/%d/%Y, %I:%M:%S %p", localtime(&time));
    return std::string(time_c);
}
string getCurrentTimeString() {
    time_t now = time(0);
	return formatTime(now);
}

// Simulates a CPU core
static void cpuWorker(int coreId) {
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
        		proc->creationTime = time(0);
                lock_guard<mutex> lock(proc->mtx);
                runningProcesses.push_back(proc);
            }

            //assign core to process
            {
                lock_guard<mutex> lock(coreMapMutex);
                processCoreMap[proc] = coreId;
				proc->currentCore = coreId;
            }

            //simulate logging{} 
            {
                lock_guard<mutex> lock(proc->mtx);
				string foldername = "./processes/";
                int i = 0;
                
				
				// Creating a directory
				if(!directoryCreated){
					mkdir("processes");
					directoryCreated = true;
				}

				//open	
				string filename = foldername + proc->name + ".txt";

                //for header checking
                std::ifstream infile(filename);
                std::string firstWord;
                infile >> firstWord;
                infile.close();

                //writing
                ofstream logFile(filename, ios::app);
                if (!logFile.is_open()) {
                    std::cerr << "Failed to open log file: " << filename << "\n";
                    break; 
                }else{
					// header
					if (!(firstWord == "Process")) {
                        logFile << "Process name: " + proc->name + "\n";
                        logFile << "Logs:\n\n";
                    }

                    if(isRoundRobin) {
                        while (i < quantumCycles && proc->executedCommands < proc->totalCommands) 
                        {
                            string timestamp = getCurrentTimeString();
                            logFile << "(" << timestamp + ") \tCore: " + to_string(coreId) + "\t\"Hello World from " + proc->name + "!\"\n";
                            this_thread::sleep_for(chrono::milliseconds(200)); //used 125 for testing
                            proc->executedCommands++;
                            i++;
                        }
                    } else {
                        while (proc->executedCommands < proc->totalCommands) 
                        {
                            string timestamp = getCurrentTimeString();
                            logFile << "(" << timestamp + ") \tCore: " + to_string(coreId) + "\t\"Hello World from " + proc->name + "!\"\n";
                            this_thread::sleep_for(chrono::milliseconds(200)); //used 125 for testing
                            proc->executedCommands++;
                        }
                    }
                    logFile.close();
                }

            }
                
            //check if process is finished & mark, otherwise add back to queue 
            {
                lock_guard<mutex> lock(proc->mtx);

                if(proc->executedCommands < proc->totalCommands) {
                    readyQueue.push(proc);
                } else {
                    proc->finished = true;
                    finishedProcesses.push_back(proc);
                }

                runningProcesses.erase(remove(runningProcesses.begin(), runningProcesses.end(), proc), runningProcesses.end());
            }

            // remove core assignment
            {
                lock_guard<mutex> lock(coreMapMutex);
				proc->currentCore = -1;
                processCoreMap.erase(proc);
            }
        }
}

// Creates and schedules all processes in FCFS order
static void schedulerThread() {
    for (int i = 0; i < MainScheduler->NUM_PROCESSES; i++) {
        //create the process
        auto* proc = new Process;
        proc->name = "process" + (i < 9 ? "0" + to_string(i + 1) : to_string(i + 1));
        proc->creationTime = time(0);
        proc->totalCommands = MainScheduler->PRINTS_PER_PROCESS;
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

    while (finishedProcesses.size() < MainScheduler->NUM_PROCESSES) {
        this_thread::sleep_for(chrono::milliseconds(500)); //run the processes
    }

    schedulerRunning = false;
    cv.notify_all();
}

// Initializes a scheduler
Scheduler::Scheduler() {
    // create a thread scheduler in FCFS order
    scheduler = thread(schedulerThread);
	setAddresses(&runningProcesses, &finishedProcesses, &readyQueue);
}

// FUNCTION BLOCK -- EXECUTES scheduler - test
void Scheduler::runSchedulerTest() {
    // For every thread, run a cpuWorker
    for (int i = 0; i < MainScheduler->NUM_CORES; i++) {
        cpuThreads.emplace_back(cpuWorker, i);
    }
}

// Sets addresses for global access
void Scheduler::setAddresses(vector<Process*>* addr1, vector<Process*>* addr2, queue<Process*>* addr3) {
	addr_runningProcesses = addr1;
	addr_finishedProcesses = addr2;
	addr_readyQueue = addr3;
}

vector<Process*>* Scheduler::getRunningProcesses() { return addr_runningProcesses; }
vector<Process*>* Scheduler::getFinishedProcesses() { return addr_finishedProcesses; }
queue<Process*>* Scheduler::getReadyQueue() { return addr_readyQueue; }

// Outputs screen list
void Scheduler::screenList(bool toFile) {
	// TODO: toFile implementation for report-util command, toggled by toFile bool

	cout << "-------------------------------------------------------------------------------------\n";
	cout << "Running processes:\n";
    for (auto* proc : runningProcesses) {
        int coreId = -1;
        {
			/*
            lock_guard<mutex> lock(coreMapMutex);
            if (processCoreMap.find(proc) != processCoreMap.end()) {
                coreId = processCoreMap[proc];
			}
			*/
			coreId = proc->currentCore;
        }
        cout << proc->name << "     (" << formatTime(proc->creationTime) << ")       "
            << "Core: " << to_string(coreId)
            << "         " << proc->executedCommands << " / " << proc->totalCommands << "\n";
    }

    cout << "\nFinished processes:\n";
    for (auto* proc : finishedProcesses) {
        cout << proc->name << "     (" << formatTime(proc->creationTime) << ")       Finished         "
            << proc->executedCommands << " / " << proc->totalCommands << "\n";
    }
    cout << "-------------------------------------------------------------------------------------\n";

}