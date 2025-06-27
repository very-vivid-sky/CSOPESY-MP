#include <iostream>
#include <string>
#include <vector>
#include "Symbol.h"
#include "SymbolTable.h"

using namespace Symbols;

SymbolTable::SymbolTable() {}

/*
* @brief Adds a "new Symbol" (or any symbol address) to the Symbol Table
*/
void SymbolTable::addSymbol(Symbol* newSymbol) {
	// name check
	if (!nameExists(newSymbol->getName())) {
		table.push_back(newSymbol);
	}
};

/*
* @brief Returns a pointer to the value of the requested symbol, which can be dereferenced
*/
void* SymbolTable::getValAddress(std::string name) {
	Symbol* curr = getSymbol(name);
	if (curr != nullptr) {
		return curr->getValAddress();
	} else {
		return nullptr;
	}
}

/*
* @brief Linear-searches through the SymbolTable to return a Symbol* with a given name
*/
Symbol* SymbolTable::getSymbol(std::string name) {
	for (int i = 0; i < table.size(); i++) {
		if (table.at(i)->getName() == name) {
			return table.at(i);
		}
	}
	return nullptr;
};

/*
* @brief Removes a symbol from the table, given itself.
* Intended to only be used in the Symbol deconstructor.
*/
void SymbolTable::removeSymbol(Symbol* newSymbol) {
	// validity check first
	Symbol* curr = nullptr;
	for (int i = 0; i < table.size(); i++) {
		curr = table.at(i);
		if (curr->getName() == newSymbol->getName()) {
			if (newSymbol == curr) {
				table.erase(table.begin() + i);
			}
			// prematurely quit for efficiency if name matches
			// but not everything else
		}
	}
}

/*
* @brief Does a symbol with this name exist?
*/
bool SymbolTable::nameExists(std::string name) {
	return (getSymbol(name) != nullptr);
};

/*
* @brief Destructor - also deletes all Symbols stored within it
*/
SymbolTable::~SymbolTable() {
	for (int i = (int)table.size() - 1; i >= 0; i--) {
		Symbol* curr = table.at(i);
		table.erase(table.begin() + i);
		delete curr;
	}
}