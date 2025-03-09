#pragma once
#include "input_action.cpp"
#include "dialogue.h"
#include <iostream>
#include <string>

class User_Input
{
public:
	static std::string get_input(std::string message);

	static bool get_bool(std::string message);

	static Input_Action get_action(std::string message);
};

