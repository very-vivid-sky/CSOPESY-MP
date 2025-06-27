#pragma once
#include <cstdint>
#include <ctime> 
#include <iostream> 
#include <Windows.h>
#include "TypedefRepo.h"
#include <vector>
#include <functional> //for std::function
#include <algorithm>  //for std::generate_n

#include "Config.h"
#include "Instruction.h"
#include "InstructionList.h"
#include "ForInstruction.h"
#include "InstructionGen.h"

using namespace Instructions;

// Generates a random number.
uint16_t Instructions::generateRandNum() {
	srand(time(0));
	return 0 + (rand() % (UINT16_MAX - 0 + 1));
}

// Generates a random number between [lower, higher)
uint16_t Instructions::generateRandNumBetween(uint16_t lower, uint16_t higher) {
	srand(time(0));
	if (higher > UINT16_MAX) { higher = UINT16_MAX; }
	return lower + (rand() % (higher - lower));
}

// Generates a random number higher than a certain value.
uint16_t Instructions::generateRandNum_higherthan(uint16_t limitval) {
	srand(time(0));
	return limitval + (rand() % (UINT16_MAX - limitval + 1));
}

// Generates a random number lower than a certain value.
uint16_t Instructions::generateRandNum_lowerthan(uint16_t limitval) {
	srand(time(0));
	return 0 + (rand() % (limitval - 0 + 1));
}

// Generates a set of generic variable names that can be used by the SymbolTable.
std::vector<std::string> Instructions::generateVariables(int num) {
	std::vector<std::string> res = std::vector<std::string>();
	res.reserve(num);
	for (int i = 0; i < num; i++) {
		res.emplace_back("var" + std::to_string(i));
	}

	return res;
}


// Creates an InstructionGenerator instance
InstructionGenerator::InstructionGenerator(Processes::Process* p) {
	thisProcess = p;
	lineCount = generateRandNumBetween(Config::get_MIN_INS(), Config::get_MAX_INS() + 1);
}

// Creates an InstructionGenerator instance with a given input number of lines
InstructionGenerator::InstructionGenerator(Processes::Process* p, int num) {
	thisProcess = p;
	lineCount = num;
}

// TODO
Instruction* InstructionGenerator::generateLine() {
	int currType;
	if (allowFor) { currType = generateRandNumBetween(0, 5); }
	else { currType = generateRandNumBetween(0, 5); }
	
	// generate new line
	switch (currType) {
		case 0: // print
			return generateLine_print();

		case 1: // declare
			return generateLine_declare();

		case 2: // add
			return generateLine_add();

		case 3: // subtract
			return generateLine_subtract();

		case 4: // sleep
			return generateLine_sleep();

		case 5: // for
			return generateLine_for();
	}
};

// TODO
PrintInstruction* InstructionGenerator::generateLine_print() {
	return new PrintInstruction(&std::cout, "Hello world from " + thisProcess->getName());
};

// TODO
DeclareInstruction* InstructionGenerator::generateLine_declare() {
	return nullptr;
};

// TODO
AddInstruction* InstructionGenerator::generateLine_add() {
	return nullptr;
};

// TODO
SubtractInstruction* InstructionGenerator::generateLine_subtract() {
	return nullptr;
};

// TODO
SleepInstruction* InstructionGenerator::generateLine_sleep() {
	return nullptr;
};

// TODO
ForInstruction* InstructionGenerator::generateLine_for() {
	return nullptr;
};