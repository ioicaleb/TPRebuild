#pragma once
#include <string>
#include <algorithm>

struct Input_Action {
	std::string command;
	std::string target;

	/// <summary>
	/// Constructor for Input_Action
	/// </summary>
	/// <param name="input"></param>
	Input_Action(const std::string& input);
};
