#pragma once
#include "dialogue.h"
#include "characters_handler.h"
#include "user_input.h"
#include "map_handler.h"
#include <string>
#include <set>

struct Room_Handler
{
	static Map_Handler Map;

	/// <summary>
	/// Returns name of current room
	/// </summary>
	/// <returns></returns>
	static std::string get_current_location();

	/// <summary>
	/// Changes current location and rolls for encounter
	/// </summary>
	/// <param name="target"></param>
	/// <param name="combat"></param>
	/// <returns>Whether to spawn enemy</returns>
	static bool change_room(const std::string& target, bool& combat);

	/// <summary>
	/// Returns list of room names with current room marked
	/// </summary>
	static void view_rooms();

	/// <summary>
	/// Returns list of interactable items in room
	/// </summary>
	/// <param name="combat">Only needed in Pantry to determine if enemy already exists</param>
	static void search_room(bool& combat);
};
