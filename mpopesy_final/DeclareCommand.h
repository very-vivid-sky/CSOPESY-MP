#pragma once
#include "ICommand.h"
#include "TypedefRepo.h"

class DeclareCommand : public ICommand{
public:
	constCharString variableName;
	uint16_t value;

	void execute() override {
		this->declare();
	}

	
private:
	void declare() {
		this->variableName = "var1";
		this->value = generateRandNum();
	}
};