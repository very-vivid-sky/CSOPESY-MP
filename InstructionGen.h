#pragma once
#include <cstdint>
#include <ctime> 
#include <Windows.h>
#include "TypedefRepo.h"
#include <functional> //for std::function
#include <algorithm>  //for std::generate_n

namespace Instructions {
	//generation of numbers and strings 
	uint16_t generateRandNum();
	uint16_t generateRandNum_higherthan(uint16_t limitval);
	uint16_t generateRandNum_lowerthan(uint16_t limitval);
	std::vector<std::string> generateVariables(int num);
}