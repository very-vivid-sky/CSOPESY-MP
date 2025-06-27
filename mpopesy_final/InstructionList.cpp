#include <iostream>
#include <string>
#include <vector>
#include "Instruction.h"
#include "SymbolTable.h"
#include "InstructionList.h"

using namespace Instructions;

// Create a new Instructionlist
InstructionList::InstructionList() {
	list = std::vector<Instruction*>();
	list.reserve(1000);
	currentLine = 0;
};

// Add a single instruction to this list if hasn't been started yet
void InstructionList::pushInstruction(Instruction* inst) {
	if (currentLine == 0) {
		list.push_back(inst);
	}
}

// Add a formed list of instructions to this list if hasn't been started yet
void InstructionList::pushInstruction(std::vector<Instruction*> insts) {
	if (currentLine == 0) {
		list.reserve(list.size() + insts.size());
		list.insert(list.end(), insts.begin(), insts.end());
	}
}

// Runs the next line of this instruction list
void InstructionList::runNext() {	
	// only if we are not yet done
	if (!isFinished()) {
		// bool res determines if we can move on to the next line
		bool res = list.at(currentLine)->run();
		if (res) { currentLine++; }
	}
}

// Returns if this InstructionList has started running
bool InstructionList::hasStarted() {
	return currentLine > 0;
}

// Returns if this InstructionList is finished
bool InstructionList::isFinished() {
	return currentLine >= list.size();
}

// Resets this InstructionList to 0
void InstructionList::reset() {
	currentLine = 0;
}

// Destructor: mass-destroys all the instructions inside it to prevent memory leaks
InstructionList::~InstructionList() {
	for (Instruction* i : list) {
		delete i;
	}
	list.clear();
}