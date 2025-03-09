#pragma once
#include "input_action.cpp"
#include "dialogue.h"
#include "game_manager.h"
#include "collections.h"
#include "characters_handler.h"
#include "room_handler.h"
#include "hints.cpp"
#ifdef _DEBUG
#include "cheat.cpp"
#endif

struct Input_Handler
{
	static bool combat;
	static void handle_action(Input_Action action);
};

