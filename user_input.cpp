#include "user_input.h"


std::string User_Input::get_input(std::string message)
{
	char input[128];
	Dialogue::print(message);
	std::cin.getline(input, 128);

	return Dialogue::lowercase(input);
};

bool User_Input::get_bool(std::string message) {
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
