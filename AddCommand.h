#pragma once
#include "ICommand.h"
#include "TypedefRepo.h"
#include "ConsoleGlobals.h"


class AddCommand : public ICommand {

public:
	uint16_t result;
	uint16_t n1 = 0;
	uint16_t n2 = 0;

	void execute() override {
		add();
	}

	//default constructor
	AddCommand() {
		this->n1 = generateRandNum();
		this->n2 = generateRandNum();
	}

private:
	void add() {
		this->result = this->n1 + this->n2;
	}
};