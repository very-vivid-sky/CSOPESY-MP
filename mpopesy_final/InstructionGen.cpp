#pragma once
#include <cstdint>
#include <ctime> 
#include <Windows.h>
#include "TypedefRepo.h"
#include <vector>
#include <functional> //for std::function
#include <algorithm>  //for std::generate_n

#include "Instruction.h"
#include "InstructionGen.h"

using namespace Instructions;

uint16_t Instructions::generateRandNum() {
	srand(time(0));
	return 0 + (rand() % (UINT16_MAX - 0 + 1));
}

uint16_t Instructions::generateRandNum_higherthan(uint16_t limitval) {
	srand(time(0));
	return limitval + (rand() % (UINT16_MAX - limitval + 1));
}

uint16_t Instructions::generateRandNum_lowerthan(uint16_t limitval) {
	srand(time(0));
	return 0 + (rand() % (limitval - 0 + 1));
}

std::vector<std::string> Instructions::generateVariables(int num) {
	std::vector<std::string> res = std::vector<std::string>();
	res.reserve(num);
	for (int i = 0; i < num; i++) {
		res.emplace_back("var" + std::to_string(i));
	}

	return res;
}