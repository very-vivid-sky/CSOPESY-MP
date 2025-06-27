#include <iostream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include "Symbol.h"

using namespace Symbols;

/*
* @brief Defines a symbol.
*/
Symbol::Symbol(std::string newName, Types newType) {
	name = newName;
	type = newType;
	allocateSpaceForVar();
};

/*
* @brief Defines and sets the value of a symbol at once.
* This function is overloaded based on the requested type
* @param newVal: The new value to insert
*/
Symbol::Symbol(std::string newName, bool newVal) {
	name = newName; type = t_Bool; allocateSpaceForVar(); setVal(newVal);
}

/*
* @brief Defines and sets the value of a symbol at once.
* This function is overloaded based on the requested type
* @param newVal: The new value to insert
*/
Symbol::Symbol(std::string newName, char newVal) {
	name = newName; type = t_Char; allocateSpaceForVar(); setVal(newVal);
}

/*
* @brief Defines and sets the value of a symbol at once.
* This function is overloaded based on the requested type
* @param newVal: The new value to insert
*/
Symbol::Symbol(std::string newName, unsigned char newVal) {
	name = newName; type = t_Char; allocateSpaceForVar(); setVal(newVal);
}

/*
* @brief Defines and sets the value of a symbol at once.
* This function is overloaded based on the requested type
* @param newVal: The new value to insert
*/
Symbol::Symbol(std::string newName, short newVal) {
	name = newName; type = t_Short; allocateSpaceForVar(); setVal(newVal);
}

/*
* @brief Defines and sets the value of a symbol at once.
* This function is overloaded based on the requested type
* @param newVal: The new value to insert
*/
Symbol::Symbol(std::string newName, unsigned short newVal) {
	name = newName; type = t_Char; allocateSpaceForVar(); setVal(newVal);
}

/*
* @brief Defines and sets the value of a symbol at once.
* This function is overloaded based on the requested type
* @param newVal: The new value to insert
*/
Symbol::Symbol(std::string newName, int newVal) {
	name = newName; type = t_Int; allocateSpaceForVar(); setVal(newVal);
}

/*
* @brief Defines and sets the value of a symbol at once.
* This function is overloaded based on the requested type
* @param newVal: The new value to insert
*/
Symbol::Symbol(std::string newName, unsigned int newVal) {
	name = newName; type = t_Char; allocateSpaceForVar(); setVal(newVal);
}

/*
* @brief Defines and sets the value of a symbol at once.
* This function is overloaded based on the requested type
* @param newVal: The new value to insert
*/
Symbol::Symbol(std::string newName, long newVal) {
	name = newName; type = t_Long; allocateSpaceForVar(); setVal(newVal);
}

/*
* @brief Defines and sets the value of a symbol at once.
* This function is overloaded based on the requested type
* @param newVal: The new value to insert
*/
Symbol::Symbol(std::string newName, unsigned long newVal) {
	name = newName; type = t_Char; allocateSpaceForVar(); setVal(newVal);
}

/*
* @brief Defines and sets the value of a symbol at once.
* This function is overloaded based on the requested type
* @param newVal: The new value to insert
*/
Symbol::Symbol(std::string newName, long long newVal) {
	name = newName; type = t_LongLong; allocateSpaceForVar(); setVal(newVal);
}

/*
* @brief Defines and sets the value of a symbol at once.
* This function is overloaded based on the requested type
* @param newVal: The new value to insert
*/
Symbol::Symbol(std::string newName, unsigned long long newVal) {
	name = newName; type = t_Char; allocateSpaceForVar(); setVal(newVal);
}

/*
* @brief Defines and sets the value of a symbol at once.
* This function is overloaded based on the requested type
* @param newVal: The new value to insert
*/
Symbol::Symbol(std::string newName, float newVal) {
	name = newName; type = t_Float; allocateSpaceForVar(); setVal(newVal);
}

/*
* @brief Defines and sets the value of a symbol at once.
* This function is overloaded based on the requested type
* @param newVal: The new value to insert
*/
Symbol::Symbol(std::string newName, double newVal) {
	name = newName; type = t_Double; allocateSpaceForVar(); setVal(newVal);
}

/*
* @brief Initializes and allocates space for the variable.
*/
void Symbol::allocateSpaceForVar() {
	// abort immediately if not null
	if (value != nullptr) { return; }

	// if null, initialize
	switch (type) {
		case t_Bool:		value = new bool; setVal((bool) 0); break;
		case t_Char:		value = new char; setVal((char) 0); break;
		case t_Char_u:		value = new unsigned char; setVal((char) 0); break;
		case t_Short:		value = new short; setVal((short) 0); break;
		case t_Short_u:		value = new unsigned short; setVal((short) 0); break;
		case t_Int:			value = new int; setVal((int) 0); break;
		case t_Int_u:		value = new unsigned int; setVal((int) 0); break;
		case t_Long:		value = new long; setVal((long) 0); break;
		case t_Long_u:		value = new unsigned long; setVal((long) 0); break;
		case t_LongLong:	value = new long long; setVal((long long) 0); break;
		case t_LongLong_u:	value = new unsigned long long; setVal((long long) 0); break;
		case t_Float:		value = new float; setVal((float) 0); break;
		case t_Double:		value = new double; setVal((double) 0); break;
		default:
			return;
	}
}

/*
* @brief Returns the value as a void pointer.
*/
void* Symbol::getValAddress() {
	return value;
}

/*
* @brief Returns the type of this symbol.
*/
Types Symbol::getType() {
	return type;
}

/*
* @brief Returns the name of this symbol.
*/
std::string Symbol::getName() {
	return name;
}

/*
* @brief Overloaded equals operator - are these two objects the same?
*/
bool Symbol::operator == (Symbol &other) {
	if (name == other.getName() && type == other.getType() && value == other.getValAddress()) {
		return true;
	} else {
		return false;
	}
}