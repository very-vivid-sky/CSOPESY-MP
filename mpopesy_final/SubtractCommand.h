#pragma once
#include "ICommand.h"
#include "TypedefRepo.h"

class SubtractCommand : public ICommand {

public:
	uint16_t result;
	uint16_t n1 = 0;
	uint16_t n2 = 0;

	void execute() override {
		subtract();
	}

	//default constructor
	SubtractCommand() {
		this->n1 = generateRandNum();
		this->n2 = generateRandNum_lowerthan(this->n1);
	}


private:
	void subtract() {
		this->result = this->n2 - this->n1;
	}
};