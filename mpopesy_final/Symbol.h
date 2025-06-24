#pragma once
#include <map>
#include <string>
#include <type_traits>

namespace Symbols {
	/*
	* @brief Typedef for all available types that can be used in Symbol
	*/
	enum Types {
		t_Bool,
		t_Char, t_Char_u,
		t_Short, t_Short_u,
		t_Int, t_Int_u,
		t_Long, t_Long_u,
		t_LongLong, t_LongLong_u,
		t_Float,
		t_Double,
	};

	/*
	* @brief Definition of a single symbol object
	*/
	class Symbol {
		public:
			Symbol(std::string newName, Types newType);
			Symbol(std::string newName, bool newVal);
			Symbol(std::string newName, char newVal);
			Symbol(std::string newName, short newVal);
			Symbol(std::string newName, int newVal);
			Symbol(std::string newName, long newVal);
			Symbol(std::string newName, long long newVal);
			Symbol(std::string newName, float newVal);
			Symbol(std::string newName, double newVal);
			template<typename T> bool setVal(T newVal);
			template<typename T> T getVal();
			void* getValAddress();
			std::string getName();
			Types getType();
			bool operator == (Symbol &other);

		private:
			std::string name;
			void* value;
			Types type;
			void allocateSpaceForVar();
			void* inTable;
	};

	/*
	* @brief Sets the value of this symbol.
	*/
	template<typename T> bool Symbol::setVal(T newVal) {
		// switch based on value of symbol, and compare against T
		switch (type) {
		case t_Bool:
			if (std::is_convertible<T, bool>())					{ *(bool*)value = (bool)newVal;								return true; } break;
		case t_Char:
			if (std::is_convertible<T, char>())					{ *(char*)value = (char)newVal;								return true; } break;
		case t_Char_u:
			if (std::is_convertible<T, unsigned char>())		{ *(unsigned char*)value = (unsigned char)newVal;			return true; } break;
		case t_Short:
			if (std::is_convertible<T, short>())				{ *(short*)value = (short)newVal;							return true; } break;
		case t_Short_u:
			if (std::is_convertible<T, unsigned short>())		{ *(unsigned short*)value = (unsigned short)newVal;			return true; } break;
		case t_Int:
			if (std::is_convertible<T, int>())					{ *(int*)value = (int)newVal;								return true; } break;
		case t_Int_u:
			if (std::is_convertible<T, unsigned int>())			{ *(unsigned int*)value = (unsigned int)newVal;				return true; } break;
		case t_Long:
			if (std::is_convertible<T, long>())					{ *(long*)value = (long)newVal;								return true; } break;
		case t_Long_u:
			if (std::is_convertible<T, unsigned long>())		{ *(unsigned long*)value = (unsigned long)newVal;			return true; } break;
		case t_LongLong:
			if (std::is_convertible<T, long long>())			{ *(long long*)value = (long long)newVal;					return true; } break;
		case t_LongLong_u:
			if (std::is_convertible<T, unsigned long long>())	{ *(unsigned long long*)value = (unsigned long long)newVal;	return true; } break;
		case t_Float:
			if (std::is_convertible<T, float>())				{ *(float*)value = (float)newVal;							return true; } break;
		case t_Double:
			if (std::is_convertible<T, double>())				{ *(double*)value = (double)newVal;							return true; } break;
		default:
			return false;
		}
		return false;
	}

	/*
	* @brief Returns the value of this symbol, cast into a given type
	*/
	template<typename T>
	T Symbol::getVal() {
		T curr;
		switch (type) {
		case t_Bool:		curr = (T)(*(bool*)value); break;
		case t_Char:		curr = (T)(*(char*)value); break;
		case t_Char_u:		curr = (T)(*(unsigned char*)value); break;
		case t_Short:		curr = (T)(*(short*)value); break;
		case t_Short_u:		curr = (T)(*(unsigned short*)value); break;
		case t_Int:			curr = (T)(*(int*)value); break;
		case t_Int_u:		curr = (T)(*(unsigned int*)value); break;
		case t_Long:		curr = (T)(*(long*)value); break;
		case t_Long_u:		curr = (T)(*(unsigned long*)value); break;
		case t_LongLong:	curr = (T)(*(long long*)value); break;
		case t_LongLong_u:	curr = (T)(*(unsigned long long*)value); break;
		case t_Float:		curr = (T)(*(float*)value); break;
		case t_Double:		curr = (T)(*(double*)value); break;
		}
		return curr;
	}

};