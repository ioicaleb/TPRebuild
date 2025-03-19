#pragma once
#include "input_action.h"

Input_Action::Input_Action(const std::string& input) {
	auto pos = input.find(" ");
	if (pos != std::string::npos) {
		this->command = input.substr(0, pos);
		while (input.substr(pos, 1) == " ") {
			pos++;
		}
		this->target = input.substr(pos);
	}
	else {
		this->command = input;
		this->target = "";
	}
};
