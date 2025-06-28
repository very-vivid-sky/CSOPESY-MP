#pragma once
#include <ostream>
#include <string>
#include <vector>
#include "SymbolTable.h"

namespace Instructions {

	// Anonymous namespace - only to be used within here
	namespace {

		// Holds either a uint16 or reference to a symbol table symbol holding one
		struct InstructionValueHolder {
			InstructionValueHolder() {
				isStr = false; valueStr = ""; valueInt = 0;
			}
			InstructionValueHolder(std::string val) {
				isStr = true; valueStr = val; valueInt = 0;
			}
			InstructionValueHolder(unsigned int val) {
				isStr = false; valueInt = val; valueStr = "";
			}

			bool isStr;
			std::string valueStr;
			unsigned int valueInt;

			// gets the requested value either directly or via a symbol table
			const unsigned int get(Symbols::SymbolTable* fromTable) {
				if (isStr) {
					if (fromTable->nameExists(valueStr)) { return fromTable->getVal<unsigned int>(valueStr); }
					else { return 0; }
				}
				else { return valueInt; }
			}
		};
	}

	enum InstructionType {
		unknown,
		print,
		declare,
		add,
		subtract,
		sleep,
		forloop
	};

	// Generic class for instructions.
	class Instruction {
		public:
			virtual bool run() { return true; };
			virtual InstructionType getType() { return unknown; };
	};

	// Print instruction - prints a given string
	class PrintInstruction : public Instruction {
		public:
			PrintInstruction();
			PrintInstruction(std::ostream* streamToUse, std::string str);
			InstructionType getType() { return print; };
			bool run();
		private:
			std::string toPrint;
			std::ostream* stream;
	};

	// Declare instruction - declares a new variable
	class DeclareInstruction : public Instruction {
		public:
			DeclareInstruction(Symbols::SymbolTable* tableAddr, std::string newName);
			DeclareInstruction(Symbols::SymbolTable* tableAddr, std::string newName, unsigned int newVal);
			InstructionType getType() { return declare; };
			bool run();
		private:
			Symbols::SymbolTable* table;
			std::string name;
			unsigned int val;
	};

	// Add instruction - adds two variables / values together and puts the result in a third
	class AddInstruction : public Instruction {
		public:

			// Initializes a new AddInstruction given a dest address and two ints or symbol table references
			template<typename T1, typename T2>
			AddInstruction(Symbols::SymbolTable* tableAddr, std::string destName, T1 val1Raw, T2 val2Raw) {
				table = tableAddr;
				dest = destName;
				val1 = InstructionValueHolder(val1Raw);
				val2 = InstructionValueHolder(val2Raw);
			}

			InstructionType getType() { return add; };
			bool run();
		private:
			Symbols::SymbolTable* table;
			std::string dest;
			InstructionValueHolder val1;
			InstructionValueHolder val2;
	};


	// Subtract instruction - subtracts two variables / values together and puts the result in a third
	class SubtractInstruction : public Instruction {
		public:
			
			// Initializes a new AddInstruction given a dest address and two ints or symbol table references
			template<typename T1, typename T2>
			SubtractInstruction(Symbols::SymbolTable* tableAddr, std::string destName, T1 val1Raw, T2 val2Raw) {
				table = tableAddr;
				dest = destName;
				val1 = InstructionValueHolder(val1Raw);
				val2 = InstructionValueHolder(val2Raw);
			}

			InstructionType getType() { return subtract; };
			bool run();
		private:
			Symbols::SymbolTable* table;
			std::string dest;
			InstructionValueHolder val1;
			InstructionValueHolder val2;
	};

	// Sleep instruction - sleeps for n cpu ticks
	class SleepInstruction : public Instruction {
		public:
			SleepInstruction(int timeToSleep);
			InstructionType getType() { return sleep; };
			bool run();
		private:
			int time;
	};


}