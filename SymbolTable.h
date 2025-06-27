#pragma once
#include <string>
#include <vector>
#include "Symbol.h"

namespace Symbols {
	class SymbolTable {
		public:
			SymbolTable();
			void addSymbol(Symbol* newSymbol);
			template<typename T> void addSymbol(std::string name, T newVal);
			template<typename T> void setVal(std::string name, T newVal);
			template<typename T> void addOrSetVal(std::string name, T newVal);
			template<typename T> T getVal(std::string name);
			void* getValAddress(std::string name);
			void removeSymbol(Symbol* newSymbol);
			bool nameExists(std::string name);
			~SymbolTable();

		private:
			std::vector<Symbol*> table;
			Symbol* getSymbol(std::string name);
	};

	/*
* @brief Adds a "new Symbol" manually, using the symbol name and the value
*/
	template<typename T>
	void SymbolTable::addSymbol(std::string name, T newVal) {
		// name check
		if (!nameExists(name)) {
			Symbol* curr = new Symbol(name, newVal);
			table.push_back(curr);
		}
	};

	/*
	* @brief Sets the value of a symbol with a given name.
	* Technically can be done manually since getVal provides a changeable reference,
	* but this is safer to use code
	*/
	template<typename T>
	void SymbolTable::setVal(std::string name, T newVal) {
		Symbol* curr = getSymbol(name);
		if (curr != nullptr) {
			curr->setVal(newVal);
		};
	};

	/*
	* @brief Adds or sets a value, depending on whichever is appropriate
	* depending on the name's existence in the SymbolTable
	*/
	template<typename T>
	void SymbolTable::addOrSetVal(std::string name, T newVal) {
		if (nameExists(name)) {
			setVal(name, newVal);
		}
		else {
			addSymbol(name, newVal);
		}
	};

	/*
	* @brief Returns the value of the requested symbol, typecast to a given type
	*/
	template<typename T>
	T SymbolTable::getVal(std::string name) {
		Symbol* curr = getSymbol(name);
		if (curr != nullptr) {
			return curr->getVal<T>();
		}
		else {
			return 0;
		}
	};

};