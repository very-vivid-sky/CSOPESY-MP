#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Instruction.h"
#include "InstructionList.h"
#include "SymbolTable.h"

namespace Instructions {

	// For instruction - loops a list of instructions n times
	class ForInstruction : public Instruction {
	public:
		ForInstruction(int i, InstructionList* newIl);
		~ForInstruction();
		InstructionType getType() { return forloop; };
		bool run();

		int getCurrentLine();
		int getLineCount();
		int getLineCountFull();


	private:
		InstructionList* il;
		int iterTimes;
	};

}