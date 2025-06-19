#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <string>

void displayHeader();
void refresh();
std::string getInput();
std::string getInputWithPrompt(std::string prompt);

#include "display.cpp"
#endif