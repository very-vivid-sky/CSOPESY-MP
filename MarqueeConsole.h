#pragma once
#include "AConsole.h"
#include "windows.h"
#include "ConsoleGlobals.h"
#include "CommandHandler.h"
#include "InputManager.h"
#include "ConsoleManager.h"
#include "Scheduler.h"
class MarqueeConsole : public AConsole
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
	MarqueeConsole();
	~MarqueeConsole() = default;

	/*
	* @brief gets the CSOPESY HEADER
	* @return const char* getHeader contents
	*/
	const char* getHeader();

	void displayHeader();


private:


	friend class ConsoleManager;
};