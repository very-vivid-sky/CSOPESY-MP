#pragma once
#include <string>
#include <vector>

enum SchedulerTypes {
	fcfs, rr
};

namespace Config {
	void initConfig(std::string filePath);
	int get_NUM_CPU();
	SchedulerTypes get_SCHEDULER();
	int get_QUANTUM_CYCLES();
	int get_BATCH_PROCESS_FREQ();
	int get_MIN_INS();
	int get_MAX_INS();
	int get_DELAY_PER_EXEC();
	bool get_initialization_status();
};