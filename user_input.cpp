#include "user_input.h"

std::string User_Input::get_input(const std::string& message)
{
	std::string input = "";
	Dialogue::print(message);
	while (input == "") {
		std::getline(std::cin, input);
	}

	return Dialogue::lowercase(input);
};

bool User_Input::get_bool(const std::string& message) {
	std::string input;
	bool valid = false;
	while (!valid) {
		Dialogue::print(message);
		std::cin >> input;
		input = Dialogue::lowercase(input);
		if (input == "yes" || input == "y") {
			return true;
		}
		else if (input == "no" || input == "n") {
			return false;
		}
		else {
			Dialogue::print_line("Invalid input. Please enter 'yes' or 'no'.");
		}
	}
};

Input_Action User_Input::get_action(std::string message) { return Input_Action(User_Input::get_input(message)); };
