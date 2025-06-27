#include <iostream>
#include <string>
#include <vector>
#include "Instruction.h"
#include "SymbolTable.h"
#include "ForInstruction.h"

using namespace Instructions;

ForInstruction::ForInstruction(int i, InstructionList* newIl) {
	il = newIl;
	iterTimes = i;
}

bool ForInstruction::run() {

	// run next inside the loop
	il->runNext();

	// reset and decrement iterTimes if we're done
	if (il->isFinished()) { il->reset(); iterTimes--; };

	// if we're really done, return true
	if (iterTimes == 0) { return true; }
	else { return false; }
}

// Destroys this class: also destroys the il
ForInstruction::~ForInstruction() {
	delete il;
}