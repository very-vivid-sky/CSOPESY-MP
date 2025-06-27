#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Instruction.h"
#include "SymbolTable.h"

namespace Instructions {
	class InstructionList {
		public:
			InstructionList();
			~InstructionList();
			void pushInstruction(Instruction* inst);
			void pushInstruction(std::vector<Instruction*> insts);
			void runNext();
			bool hasStarted();
			bool isFinished();
			void reset();

		private:
			int currentLine;
			std::vector<Instruction*> list;
			Symbols::SymbolTable table;
	};
}