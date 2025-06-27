#pragma once
#include <cstdint>
#include <cstdlib>
#include <ctime> 
#include <iostream> 
#include <Windows.h>
#include "TypedefRepo.h"
#include <vector>
#include <functional> //for std::function
#include <algorithm>  //for std::generate_n

#include "Config.h"
#include "SymbolTable.h"
#include "Instruction.h"
#include "InstructionList.h"
#include "ForInstruction.h"
#include "InstructionGen.h"

using namespace Instructions;

// Generates a random number.
uint16_t Instructions::generateRandNum() {
	return 0 + (rand() % (UINT16_MAX - 0 + 1));
}

// Generates a random number between [lower, higher)
uint16_t Instructions::generateRandNumBetween(uint16_t lower, uint16_t higher) {
	if (higher > UINT16_MAX) { higher = UINT16_MAX; }
	return lower + (rand() % (higher - lower));
}

// Generates a random number higher than a certain value.
uint16_t Instructions::generateRandNum_higherthan(uint16_t limitval) {
	return limitval + (rand() % (UINT16_MAX - limitval + 1));
}

// Generates a random number lower than a certain value.
uint16_t Instructions::generateRandNum_lowerthan(uint16_t limitval) {
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
	std::srand(std::time(0));
	thisProcess = p;
	lineCount = generateRandNumBetween(Config::get_MIN_INS(), Config::get_MAX_INS() + 1);
	variableCount = generateRandNumBetween(2, 31); // 2-30
	variableNames = generateVariables(variableCount);
}

// Creates an InstructionGenerator instance with a given input number of lines
InstructionGenerator::InstructionGenerator(Processes::Process* p, int num) {
	std::srand(std::time(0));
	thisProcess = p;
	lineCount = num;
	variableCount = generateRandNumBetween(2, 31); // 2-30
	variableNames = generateVariables(variableCount);
}

// Gets a random variable
std::string InstructionGenerator::getRandomVariable() {
	return variableNames.at(generateRandNumBetween(0, variableCount));
};

// Generates a full instruction list
std::vector<Instruction*> InstructionGenerator::generateInstructionList() {
	std::vector<Instruction*> res = std::vector<Instruction*>();
	res.reserve(lineCount);
	for (int i = 0; i < lineCount; i++) {
		res.push_back(generateLine());
	}
	return res;

}

// Generates a single line.
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
	return new DeclareInstruction(thisProcess->getSymbolTable(), getRandomVariable(), generateRandNum());
};

// TODO
AddInstruction* InstructionGenerator::generateLine_add() {
	return new AddInstruction(thisProcess->getSymbolTable(), getRandomVariable(), generateRandNum_lowerthan(32768), generateRandNum_lowerthan(32768));
};

// TODO
SubtractInstruction* InstructionGenerator::generateLine_subtract() {
	uint16_t val1 = generateRandNum();
	uint16_t val2 = generateRandNum_lowerthan(val1);
	return new SubtractInstruction(thisProcess->getSymbolTable(), "hi", 0, 0);
};

// TODO
SleepInstruction* InstructionGenerator::generateLine_sleep() {
	return new SleepInstruction(generateRandNumBetween(1, 256));
};

// TODO
ForInstruction* InstructionGenerator::generateLine_for() {
	return nullptr;
};