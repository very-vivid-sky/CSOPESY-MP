#include <chrono>
#include <iostream>
#include <ostream>
#include <string>
#include <thread>
#include <vector>
#include "SymbolTable.h"
#include "Instruction.h"

using namespace Instructions;

// Initializes a new generic PrintInstruction
PrintInstruction::PrintInstruction() {
	toPrint = "Hello world!";
	stream = &std::cout;
}

// Initializes a new PrintInstruction using the string to print
PrintInstruction::PrintInstruction(std::ostream* streamToUse, std::string str) {
	toPrint = str;
	stream = streamToUse;
}

// Runs PrintInstruction:
// prints a given string to a certain ostream
bool PrintInstruction::run() {
	*stream << toPrint;
	return true;
}

// Initializes a new DeclareInstruction given a symbol table and symbol name
DeclareInstruction::DeclareInstruction(Symbols::SymbolTable* tableAddr, std::string newName) {
	table = tableAddr;
	name = newName;
	val = 0;
}

// Initializes a new DeclareInstruction given a symbol table, symbol name, and initial value
DeclareInstruction::DeclareInstruction(Symbols::SymbolTable* tableAddr, std::string newName, unsigned int newVal) {
	table = tableAddr;
	name = newName;
	val = newVal;
}

// Runs DeclareInstruction:
// Declares a new variable with a given name
bool DeclareInstruction::run() {
	if (!(table->nameExists(name))) {
		table->addSymbol(name, val);
	} else {
		table->setVal(name, val);
	}
	return true;
}

// RunsAddInstruction:
// Adds two values and puts it somewhere in the symbol table
bool AddInstruction::run() {
	unsigned int temp;
	temp = val1.get(table) + val2.get(table);
	table->addOrSetVal(dest, temp);
	return true;
}

// Runs SubtractInstruction:
// Subtracts two values and puts it somewhere in the symbol table
bool SubtractInstruction::run() {
	unsigned int temp;
	temp = val1.get(table) - val2.get(table);
	table->addOrSetVal(dest, temp);
	return true;
}

// Initializes a new Sleepinstruction given a length of time to sleep
SleepInstruction::SleepInstruction(int timeToSleep) {
	time = timeToSleep;
}

// Runs SleepInstruction:
// Sleeps the process for n cpu ticks
bool SleepInstruction::run() {
	std::this_thread::sleep_for(std::chrono::milliseconds(time));
	return true;
}