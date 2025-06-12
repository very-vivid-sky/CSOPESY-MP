#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <condition_variable>
#include <atomic>

void screen_ls();
void runSchedulerTest();

extern std::condition_variable cv;
extern std::atomic<bool> schedulerRunning;
extern std::atomic<bool> emulatorRunning;

#include "scheduler.cpp"

#endif
