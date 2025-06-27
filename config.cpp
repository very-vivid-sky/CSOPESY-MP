#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "./Config.h"

// anonymous namespace for private functions
namespace {
	// Returns a tokenized form of a given string str
	std::vector<std::string> tokenize(std::string str) {
		std::vector<std::string> tokens;

		std::istringstream iss(str);
		std::string token;
		while (iss >> token) {
			tokens.push_back(token);
		}
		return tokens;
	};

	// Static constants not to be modified outside of this cpp file
	static bool has_initialized = false;
	static int NUM_CPU;
	static SchedulerTypes SCHEDULER;
	static int QUANTUM_CYCLES;
	static int BATCH_PROCESS_FREQ;
	static int MIN_INS;
	static int MAX_INS;
	static int DELAY_PER_EXEC;
};



// Initializes all variables
void Config::initConfig(std::string filePath) {
	std::ifstream configFile(filePath, std::ios::in);
	// no file?
	// TODO generic config file generation?
	if (!configFile.is_open()) {
		throw std::logic_error("config.txt does not exist");
		return;
	}

	// scan and analyze config file
	std::string currLine;
	std::vector<std::string> currTokenized;
	while (std::getline(configFile, currLine)) {
		currTokenized = ::tokenize(currLine);
		// if-chain for the correct token's value
		if (currTokenized[0] == "num-cpu") {
			NUM_CPU = std::stoi(currTokenized[1]);
		} else if (currTokenized[0] == "scheduler") {
			if (currTokenized[1] == "\"rr\"") {
				SCHEDULER = rr;
			} else if (currTokenized[1] == "rr") {
				SCHEDULER = rr;
			} else {
				SCHEDULER == fcfs;
			}
		} else if (currTokenized[0] == "quantum-cycles") {
			QUANTUM_CYCLES = std::stoi(currTokenized[1]);
		} else if (currTokenized[0] == "batch-process-freq") {
			BATCH_PROCESS_FREQ = std::stoi(currTokenized[1]);
		} else if (currTokenized[0] == "min-ins") {
			MIN_INS = std::stoi(currTokenized[1]);
		} else if (currTokenized[0] == "max-ins") {
			MAX_INS = std::stoi(currTokenized[1]);
		} else if (currTokenized[0] == "delay-per-exec") {
			DELAY_PER_EXEC = std::stoi(currTokenized[1]);
		}
	}

	// flip bit and close!
	has_initialized = true;
	configFile.close();
};

// Getters for the relevant constants
// Since these are all the ConfigVariables namespace, they have to be located through that, ex:
// cout << ConfigVariables::get_NUM_CPU();

// Getter for the constant NUM_CPU
int Config::get_NUM_CPU() { return NUM_CPU; }
// Getter for the constant QUANTUM_CYCLES
int Config::get_QUANTUM_CYCLES() { return QUANTUM_CYCLES; }
// Getter for the constant BATCH_PROCESS_FREQ
int Config::get_BATCH_PROCESS_FREQ() { return BATCH_PROCESS_FREQ; }
// Getter for the constant MIN_INS
int Config::get_MIN_INS() { return MIN_INS; }
// Getter for the constant MAX_INS
int Config::get_MAX_INS() { return MAX_INS; }
// Getter for the constant DELAY_PER_EXEC
int Config::get_DELAY_PER_EXEC() { return DELAY_PER_EXEC; }
// Getter for the constant SCHEDULER
SchedulerTypes Config::get_SCHEDULER() { return SCHEDULER; }
// Has the OS already ran initConfig?
bool Config::get_initialization_status() { return has_initialized; }