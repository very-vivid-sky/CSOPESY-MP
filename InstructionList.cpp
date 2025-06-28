#include <iostream>
#include <string>
#include <vector>
#include "Instruction.h"
#include "SymbolTable.h"
#include "InstructionList.h"
#include "ForInstruction.h"

using namespace Instructions;

// Create a new Instructionlist
InstructionList::InstructionList() {
	list = std::vector<Instruction*>();
	list.reserve(1000);
	currentLine = -1;
	lineCount = 0;
	lineCountFull = 0;
	locked = false;
};

// Add a single instruction to this list if hasn't been started yet
void InstructionList::pushInstruction(Instruction* inst) {
	if (!locked) {
		list.push_back(inst);
	}
}

// Add a formed list of instructions to this list if hasn't been started yet
void InstructionList::pushInstruction(std::vector<Instruction*> insts) {
	if (!locked) {
		list.reserve(list.size() + insts.size());
		list.insert(list.end(), insts.begin(), insts.end());
	}
}

// Runs the next line of this instruction list
void InstructionList::runNext() {	
	// lock the IL
	lock();

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
	return currentLine >= lineCount;
}

// Resets this InstructionList to 0
void InstructionList::reset() {
	currentLine = 0;
}

// Getter: gets the current line number
int InstructionList::getCurrentLine() { return currentLine; };

// Getter: gets the line count of this InstructionList; locks if not yet locked
int InstructionList::getLineCount() { lock(); return lineCount; };

// Getter: gets the full line count including all for(); locks if not yet locked
int InstructionList::getLineCountFull() { lock();  return lineCountFull; };

// Locks this InstructionList to note that it is final,
// also calculates line counts
bool InstructionList::lock() {
	// no need to do anything if already locked
	if (locked) { return false; }

	// increment to note that this is actually usable now
	currentLine++;

	// update lock list
	lineCount = list.size();
	lineCountFull = list.size();

	// add for() line counts to to lineCountFull
	for (Instruction* i : list) {
		if (i->getType() == forloop) {
			int curr = -1;										// -1 for the for loop itself because...
			curr += ((ForInstruction*) i)->getLineCountFull();	// add line count inside the for instruction
																// this will also lock everything inside the for loop
			lineCountFull += curr;								// merge with official line count now
		}
	}

	locked = true;
	
	return true;
}

// Destructor: mass-destroys all the instructions inside it to prevent memory leaks
InstructionList::~InstructionList() {
	for (Instruction* i : list) {
		delete i;
	}
	list.clear();
}