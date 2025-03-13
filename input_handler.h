#pragma once
#include "game_manager.h"
#include "input_action.h"
#include "characters_handler.h"
#include "room_handler.h"
#include "hints.h"
#ifdef _DEBUG
#include "cheat.h"
#endif
#include <algorithm>
#include <string>

struct Input_Handler {
	Input_Handler() {};

	static void handle_action(const Input_Action& action);
	static void create_send_action(const char* action);
};
