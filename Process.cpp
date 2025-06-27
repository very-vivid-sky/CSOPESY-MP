#include <iostream>
#include <string>
#include <ctime>
#include "Process.h"

using namespace Processes;

Process::Process(std::string newName) {
	name = newName;
	creationTime = std::time(0);
	totalCommands = 10;
	nextLine = 0;
	pid = 0;
	finished = false;
	currentCore = -1;
	symbolTable = Symbols::SymbolTable();
}

// Getter: gets name
std::string Process::getName() { return name; };

// Getter: gets creation time
std::time_t Process::getCreationTime() { return creationTime; };

// Getter: gets formatted creation time
std::string Process::getFormattedCreationTime() {
	char time_c[24];
	struct tm buf;
	localtime_s(&buf, &creationTime);
	strftime(time_c, 24, "%m/%d/%Y %I:%M:%S %p", &buf);
	return std::string(time_c);
};

// Getter: gets total commands
int Process::getTotalCommands() { return totalCommands; };

// Getter: gets next line int
int Process::getNextLine() { return nextLine; };

// Getter: gets pid
int Process::getPid() { return pid; };

// Getter: gets finished bool
bool Process::isFinished() { return finished; };

// Getter: gets address to this process's instruction list
Instructions::InstructionList* Process::getInstructionList() {
	return &instructionList;
};

// Getter: gets address to this process's symbol table
Symbols::SymbolTable* Process::getSymbolTable() {
	return &symbolTable;
};

// Getter: gets current core
int Process::getCore() { return currentCore; };

// Setter: sets new core
void Process::setCore(int newCore) { currentCore = newCore; }

// Runs the next line of this process
void Process::run() {
	// TODO: run here !
	std::cout << "Hello world from " + name + "! | Iter " + std::to_string(nextLine) + "\n";

	// incrementations
	nextLine++;
	if (nextLine >= totalCommands) {
		finished = true;
	}
}
