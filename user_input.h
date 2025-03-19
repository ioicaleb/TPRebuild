#pragma once
#include "dialogue.h"
#include "input_action.h"

class User_Input
{
public:
	/// <summary>
	/// Prompt user for input and validates input has been received
	/// </summary>
	/// <param name="message">Text prompt</param>
	/// <returns>Input string from user</returns>
	static std::string get_input(const std::string& message);

	/// <summary>
	/// Prompts user for a yes or no response and validates the response is a yes or no
	/// </summary>
	/// <param name="message">Text Prompt</param>
	/// <returns>Bool indicating if player responds with yes</returns>
	static bool get_bool(const std::string& message);

	/// <summary>
	/// If target left blank when required, prompts user for new target
	/// </summary>
	/// <param name="action">Action missing target</param>
	/// <param name="message">Text prompt</param>
	/// <returns>Action with supplied target</returns>
	static Input_Action get_target(Input_Action& action, std::string message);
};
