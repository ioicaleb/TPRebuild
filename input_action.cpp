#include <string>

class Input_Action {
public:
	Input_Action(std::string input) {
		auto pos = input.find(" ");
		if (pos != std::string::npos) {
			this->command = input.substr(0, pos);
			while (input.substr(pos, 1) == " ") {
				pos++;
			}
			this->target = input.substr(pos + 1);
		}
		else {
			this->command = input;
		}
	};

	std::string command;
	std::string target;
};