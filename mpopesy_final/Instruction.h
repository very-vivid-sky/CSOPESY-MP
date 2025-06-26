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
			virtual void run();
			InstructionType getType();
		private:
			InstructionType type;
	};

	// Print instruction - prints a given string
	class PrintInstruction {
		public:
			PrintInstruction();
			PrintInstruction(std::string str, std::ostream* streamToUse);
			void run();
		private:
			std::string toPrint;
			std::ostream* stream;
			const InstructionType type = print;
	};

	// Declare instruction - declares a new variable
	class DeclareInstruction {
		public:
			DeclareInstruction(Symbols::SymbolTable* tableAddr, std::string newName);
			DeclareInstruction(Symbols::SymbolTable* tableAddr, std::string newName, unsigned int newVal);
			void run();
		private:
			Symbols::SymbolTable* table;
			std::string name;
			unsigned int val;
			const InstructionType type = declare;
	};

	// Add instruction - adds two variables / values together and puts the result in a third
	class AddInstruction {
		public:
			template<typename T1, typename T2> AddInstruction(Symbols::SymbolTable* tableAddr, std::string destName, T1 val1Raw, T2 val2Raw);
			void run();
		private:
			Symbols::SymbolTable* table;
			std::string dest;
			InstructionValueHolder val1;
			InstructionValueHolder val2;

			const InstructionType type = add;
	};


	// Subtract instruction - subtracts two variables / values together and puts the result in a third
	class SubtractInstruction {
	public:
		template<typename T1, typename T2> SubtractInstruction(Symbols::SymbolTable* tableAddr, std::string destName, T1 val1Raw, T2 val2Raw);
		void run();
	private:
		Symbols::SymbolTable* table;
		std::string dest;
		InstructionValueHolder val1;
		InstructionValueHolder val2;

		const InstructionType type = subtract;
	};
}