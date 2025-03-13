#pragma once
#include <string>
#include <algorithm>

struct Input_Action {
	std::string command;
	std::string target;

	Input_Action(const std::string& input);
};
