#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

enum CommandType { unknown, initialize, screen, scheduler_test, scheduler_stop, report_util, clear, exit_menu };

class Command {
	public:
		// constructor
		Command(std::string newCommand) {
			raw = newCommand;
			initializeSize();
			tokenize();
			initializeType();
		};

		CommandType getType() { return type; };
		int getSize() { return size; };
		std::string getRaw() { return raw; };
		std::string* getTokens() { return tokens; };
		std::string getToken(int idx) {
			if (0 > idx || idx >= size) {
				throw std::out_of_range("Out of range of Command's tokens");
			} else {
				return tokens[idx];
			}
		}

		// Bool, checks if has flag or text in its tokens
		bool hasFlag(std::string flag) {
			for (int i = 0; i < size; i++) {
				if (tokens[i] == flag) {
					return true;
				}
			}
			return false;
		};
	
	private:
		std::string raw;
		CommandType type;
		int size;
		std::string* tokens;

		// Gets the command type
		CommandType initializeType() {
			std::string command = tokens[0];

			// figure out which command this is
			if (command == "initialize") { type = initialize; }
			else if (command == "screen") { type = screen; }
			else if (command == "scheduler-test") { type = scheduler_test; }
			else if (command == "scheduler-stop") { type = scheduler_stop; }
			else if (command == "report-util") { type = report_util; }
			else if (command == "clear") { type = clear; }
			else if (command == "exit") { type = exit_menu; }
			else { type = unknown; }
			
			return type;
		}

		// gets size via number of spaces
		int initializeSize() {
			int res = 1;
			for (int i = 0; i < raw.size(); i++) {
				if (raw[i] == ' ') { res++; };
			}
			size = res;
			return res;
		}

		// tokenizes this command from size
		int tokenize() {
			tokens = new std::string[size];
			std::string curr = raw;
			for (int i = 0; i < size; i++) {
				int idx = curr.find_first_of(' ');
				tokens[i] = curr.substr(0, idx);
				curr = curr.substr(idx+1);
			}
		}
		
};