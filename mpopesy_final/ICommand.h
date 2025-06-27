#pragma once
#include <cstdint>
#include <ctime> 
#include <Windows.h>
#include "TypedefRepo.h"
#include <functional> //for std::function
#include <algorithm>  //for std::generate_n

class ICommand {
public:
	virtual void execute() = 0;
	 ~ICommand() = default;


	//generation of numbers and strings 
	uint16_t generateRandNum() {
		srand(time(0));
		return 0 + (rand() % (UINT16_MAX - 0 + 1));
	}

	uint16_t generateRandNum_higherthan(uint16_t limitval) {
		srand(time(0));
		return limitval + (rand() % (UINT16_MAX - limitval + 1));
	}

	uint16_t generateRandNum_lowerthan(uint16_t limitval) {
		srand(time(0));
		return 0 + (rand() % (limitval - 0 + 1));
	}

	// from: http://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
	constCharString generateRandString()
	{
		size_t length = 20;
		auto randchar = []() -> char
			{
				const char charset[] =
					"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
					"abcdefghijklmnopqrstuvwxyz";
				const size_t max_index = (sizeof(charset) - 1);
				return charset[rand() % max_index];
			};
		std::string str(length, 5);
		std::generate_n(str.begin(), length, randchar);

		constCharString generatedVarName = str.c_str();
		return generatedVarName;
	}
};