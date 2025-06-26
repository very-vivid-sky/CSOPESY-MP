#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include "SymbolTable.h"
#include "Instruction.h"

using namespace Instructions;

// Gets the type of this Instruction
InstructionType Instruction::getType() {
	return type;
}

// Initializes a new generic PrintInstruction
PrintInstruction::PrintInstruction() {
	toPrint = "Hello world!";
	stream = &std::cout;
}

// Initializes a new PrintInstruction using the string to print
PrintInstruction::PrintInstruction(std::string str, std::ostream* streamToUse) {
	toPrint = str;
	stream = streamToUse;
}

// Runs PrintInstruction:
// prints a given string to a certain ostream
void PrintInstruction::run() {
	*stream << toPrint;
}

// Initializes a new DeclareInstruction given a symbol table and symbol name
DeclareInstruction::DeclareInstruction(Symbols::SymbolTable* tableAddr, std::string newName) {
	table = tableAddr;
	name = newName;
	val = 0;
}

// Initializes a new DeclareInstruction given a symbol table, symbol name, and initial value
DeclareInstruction::DeclareInstruction(Symbols::SymbolTable* tableAddr, std::string newName, unsigned int newVal) {
	table = tableAddr;
	name = newName;
	val = newVal;
}

// Runs DeclareInstruction:
// Declares a new variable with a given name
void DeclareInstruction::run() {
	if (!(table->nameExists(name))) {
		table->addSymbol(name, val);
	};
	// else, quietly ignore
}

// Initializes a new AddInstruction given a dest address and two ints or symbol table references
template<typename T1, typename T2>
AddInstruction::AddInstruction(Symbols::SymbolTable* tableAddr, std::string destName, T1 val1Raw, T2 val2Raw) {
	table = tableAddr;
	dest = destName;
	val1 = InstructionValueHolder(val1Raw);
	val2 = InstructionValueHolder(val2Raw);
}

// RunsAddInstruction:
// Adds two values and puts it somewhere in the symbol table
void AddInstruction::run() {
	unsigned int temp;
	temp = val1.get(table) + val2.get(table);
	table->addOrSetVal(dest, temp);
}

// Initializes a new AddInstruction given a dest address and two ints or symbol table references
template<typename T1, typename T2>
SubtractInstruction::SubtractInstruction(Symbols::SymbolTable* tableAddr, std::string destName, T1 val1Raw, T2 val2Raw) {
	table = tableAddr;
	dest = destName;
	val1 = InstructionValueHolder(val1Raw);
	val2 = InstructionValueHolder(val2Raw);
}

// Runs SubtractInstruction:
// Subtracts two values and puts it somewhere in the symbol table
void SubtractInstruction::run() {
	unsigned int temp;
	temp = val1.get(table) - val2.get(table);
	table->addOrSetVal(dest, temp);
}
