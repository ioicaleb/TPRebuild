#pragma once
#include "dialogue.h"
#include "user_input.h"
#include "input_handler.h"

struct Game_Manager
{
	static void start_game();

	static void lose_game();

	static void win_game();

	static void quit_game();
};