#include "CommandHandler.h"


CommandType Command::getType() const {
    return this->type;
}

int Command::getSize() const {
    return this->tokens.size();
}

String Command::getRaw() const {
    return this->raw;
}

String Command::getToken(int idx) const {

    if (idx < 0 || idx >= static_cast<int>(this->tokens.size())) {
        throw std::out_of_range("Out of range of Command's tokens");
    }
    return this->tokens[idx];
}

bool Command::hasFlag(const std::string& flag) const {
    return std::find(this->tokens.begin(), this->tokens.end(), flag) != this->tokens.end();
}

void Command::runCommandHandler() {
    bool running = true;

    while (running) {
        std::cout << ">> ";
        std::string input;
        std::getline(std::cin, input);

        Command cmd(input);

        switch (cmd.getType()) {
        case initialize:
            std::cout << "Initialize command not yet implemented.\n";
            break;

        case screen:
            //screen_ls();
            break;

        case scheduler_test:
            //runSchedulerTest();
            break;

        case scheduler_stop:
            /*
            std::cout << "Stopping scheduler...\n";
            schedulerRunning = false;
            emulatorRunning = false;
            cv.notify_all();
            */
            break;

        case report_util:
            std::cout << "Report-util command not yet implemented.\n";
            break;

        case clear:
            system("cls");
            break;

        case exit_menu:
            std::cout << "Exiting...\n";
            running = false;
            break;

        default:
            std::cout << "Unknown command\n";
            break;
        }
    }
}
