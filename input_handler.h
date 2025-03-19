#pragma once
#include <algorithm>
#include <string>
#include "game_manager.h"
#include "input_action.h"
#include "characters_handler.h"
#include "room_handler.h"
#include "stuff_handler.h"
#include "hints.h"
#ifdef _DEBUG
#include "cheat.h"
#endif

struct Input_Handler {
	/// <summary>
	/// Sends command to appropriate handler
	/// </summary>
	/// <param name="action"></param>
	static void handle_action(const Input_Action& action);

#ifdef _DEBUG
	/// <summary>
	/// Allows cheat to send commands without waiting for user input
	/// </summary>
	/// <param name="action"></param>
	static void create_send_action(const char* action);
#endif
};
