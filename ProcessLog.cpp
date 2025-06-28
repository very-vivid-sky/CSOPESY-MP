#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include "ProcessLog.h"

using namespace Processes;

// Creates a new ProcessLog
ProcessLog::ProcessLog(std::string newMessage) {
	message = newMessage;
	timestamp = std::time(0);
}

// Gets formatted creation time
std::string ProcessLog::getFormattedCreationTime() {
	char time_c[24];
	struct tm buf;
	localtime_s(&buf, &timestamp);
	strftime(time_c, 24, "%m/%d/%Y %I:%M:%S %p", &buf);
	return std::string(time_c);
}