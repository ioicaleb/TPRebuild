#pragma once
#include "dialogue.h"
#include "input_action.h"

class User_Input
{
public:
	static std::string get_input(const std::string& message);

	static bool get_bool(const std::string& message);

	static Input_Action get_action(std::string message);
};
