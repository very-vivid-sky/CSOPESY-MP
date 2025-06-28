#pragma once
#include <ctime>
#include <string>
#include <vector>

namespace Processes {
    struct ProcessLog {
        ProcessLog(std::string newMessage);
        std::string message;
        std::time_t timestamp;
        std::string getFormattedCreationTime();
    };
}