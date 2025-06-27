#pragma once
#include "ICommand.h"
#include "TypedefRepo.h"
#include <iostream>

class ForCommand : public ICommand {

public:
	uint16_t sleepDuration;
	std::vector <ICommand> instructions;
	int totalInstructions = 0;
	int currLine = 0;

	void execute() override {
		forLoopCommand();
	}

	//default constructor
	ForCommand() {
		//generate random commands 
	}

	/* get the total number of instructions*/
	int getSize() { return this->totalInstructions; }

	/* get the current line of instruction executing*/
	int getcurrLine() { return this->currLine; }

	


private:
	void forLoopCommand() {
		for (this->currLine; this->currLine < this->totalInstructions; this->currLine++) {
			std::cout << "ForLoopCommand Executing : " << currLine << std::endl;
		}
		
	}
};