#pragma once
#include "ICommand.h"
#include "TypedefRepo.h"
#include <Windows.h>

class SleepCommand : public ICommand {

public:
	uint16_t sleepDuration;

	void execute() override {
		sleep();
	}

	//default constructor
	SleepCommand(){
		this->sleepDuration = generateRandNum();
	}

private:
	void sleep() {
		//std::cout << "Sleep Command not yet implemented" << std::endl;

		/*possible implementation*/
		Sleep((DWORD)sleepDuration);
	}
};