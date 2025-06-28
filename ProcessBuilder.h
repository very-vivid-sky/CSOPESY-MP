#pragma once
#include <thread>

namespace Scheduler {
	extern std::thread* processBuilderThread;
	extern bool runGenerator;
	extern unsigned long long currProcessNumber;

	void processBuilderFunc();
	void processBuilder();
}