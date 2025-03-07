#include "user_input.h"
#include "dialogue.h"
#include "input_action.cpp"
#include <iostream>

std::string user_input::get_input(std::string message)
{
	char input[128];
	print(message);
	std::cin.getline(input, 128);

	return input;
};

bool user_input::get_bool(std::string message) {
	std::string input;
	bool valid = false;
	while (!valid) {
		print(message);
		std::cin >> input;
		if (input == "yes" || input == "y") {
			return true;
		}
		else if (input == "no" || input == "n") {
			return false;
		}
		else {
			print_line("Invalid input. Please enter 'yes' or 'no'.");
		}
	}
};

Input_Action user_input::get_action(std::string message) { return Input_Action(user_input::get_input(message)); };
