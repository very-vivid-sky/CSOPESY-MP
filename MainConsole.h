#pragma once
#include "AConsole.h"
#include "windows.h"
#include "ConsoleGlobals.h"
class MainConsole : public AConsole
{

public:

	//virtual functions from AConsole
	void process() override;
	void display() override;
	void onEnabled() override;
	bool running = false;

	//constructor 

	/**
	* @brief NOT FULLY IMPLEMENTED
	*/
	MainConsole();
	~MainConsole() = default;

	/*
	* @brief gets the CSOPESY HEADER
	* @return const char* getHeader contents
	*/
	const char* getHeader();

	void displayHeader();


private:


};