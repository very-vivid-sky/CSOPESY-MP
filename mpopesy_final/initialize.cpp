/*
* 
* Process: 
* - reads the config text 
* - start generating dumy processes 
* - run scheduler test
*/
#include "config.h"
#include <iostream>


void intialize() {

	std::cout << "You've entered initialization\n\n";
	Config::initConfig("config.txt");
}

