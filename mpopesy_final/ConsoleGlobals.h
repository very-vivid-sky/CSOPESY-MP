#pragma once
#ifndef CONSOLE_GLOBALS_H
#define CONSOLE_GLOBALS_H

#include <Windows.h>

extern HANDLE outConsole;
extern HANDLE inConsole;
extern bool OS_RUNNING;

extern int NUM_CORES;
extern int NUM_PROCESSES;
extern int PRINTS_PER_PROCESS;

#endif // CONSOLE_GLOBALS_H
