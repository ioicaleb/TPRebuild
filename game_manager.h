#pragma once
#include "dialogue.h"
#include "user_input.h"
#include "input_handler.h"

struct Game_Manager
{
	/// <summary>
	/// Begin game
	/// </summary>
	static void start_game();

	/// <summary>
	/// If player sugar level reaches 100, display defeat text and end game
	/// </summary>
	static void lose_game();

	/// <summary>
	/// If player pushes endgame button, display victory text and ends game
	/// </summary>
	static void win_game();

	/// <summary>
	/// Close game if player chooses to
	/// </summary>
	static void quit_game();
};