#pragma once
#include "AConsole.h"
#include "windows.h"
#include "ConsoleGlobals.h"
#include "ConsoleManager.h"
#include "Process.h"
#include <mutex>

class ScreenConsole : public AConsole
{

public:
	ScreenConsole(Processes::Process* target) : AConsole(target->getName()), targetProcess(target) {}

	//virtual functions from AConsole
	void process() override;
	void display() override;
	void onEnabled() override;
	bool running = false;

	//constructor 

	/**
	* @brief NOT FULLY IMPLEMENTED
	*/
	~ScreenConsole() = default;


private:
	Processes::Process* targetProcess;


};