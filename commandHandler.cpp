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
