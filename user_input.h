#pragma once
#include <string>
#include "input_action.cpp"

class user_input
{
public:
	static std::string get_input(std::string message);

	static bool get_bool(std::string message);

	static Input_Action get_action(std::string message);
};

