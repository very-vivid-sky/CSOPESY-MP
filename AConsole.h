#pragma once
#include <iostream>
#include "TypedefRepo.h"

class AConsole {
public:
	AConsole(String name);
	~AConsole() = default;

	friend class ConsoleManager;

	/**
	* @brief Gets the name of of the console
	*
	* @return the name of console 
	*/
	String getName(); 

private:
	String name;

public:
	virtual void onEnabled() = 0;
	virtual void display() = 0;
	virtual void process() = 0;
};
