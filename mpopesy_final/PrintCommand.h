#pragma once
#include "ICommand.h"
#include "TypedefRepo.h"
#include "ConsoleGlobals.h"
#include <Windows.h>

class PrintCommand : public ICommand {

public:
	constCharString message;
	void execute() override {
		printMessage();
	}

	//default constructor
	PrintCommand() {
		this->message = generateRandString();
	}

	void setMessage(constCharString message) {
		this->message = message;
	}

private:
	void printMessage() {
		WriteConsoleA(outConsole, this->message, strlen(this->message), nullptr, nullptr);
	}
};