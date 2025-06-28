#pragma once
#include <cstdint>
#include <ctime> 
#include <Windows.h>
#include "TypedefRepo.h"
#include <functional> //for std::function
#include <algorithm>  //for std::generate_n

#include "Process.h"
#include "Instruction.h"
#include "InstructionList.h"
#include "ForInstruction.h"

namespace Instructions {
	//generation of numbers and strings 
	uint16_t generateRandNum();
	uint16_t generateRandNumBetween(uint16_t lower, uint16_t higher);
	uint16_t generateRandNum_higherthan(uint16_t limitval);
	uint16_t generateRandNum_lowerthan(uint16_t limitval);
	std::vector<std::string> generateVariables(int num);

	class InstructionGenerator {
		public:
			InstructionGenerator(Processes::Process* p);
			InstructionGenerator(Processes::Process* p, int count);
			std::vector<Instruction*> generateInstructionList();
			
			// togglable
			bool allowFor = false;

		private:
			Processes::Process* thisProcess;
			int lineCount;
			int variableCount;
			std::vector<std::string> variableNames;

			std::string getRandomVariable();
			Instruction* generateLine();
			PrintInstruction* generateLine_print();
			DeclareInstruction* generateLine_declare();
			AddInstruction* generateLine_add();
			SubtractInstruction* generateLine_subtract();
			SleepInstruction* generateLine_sleep();
			ForInstruction* generateLine_for();
	};
};