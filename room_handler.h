#pragma once
#include "dialogue.h"
#include "collections.h"
#include "characters_handler.h"
#include "user_input.h"
#include "room.h"

struct Room_Handler
{
	static std::string get_current_location();

	static bool change_room(Room target, bool& combat);

	static void view_rooms();

	static void search_room(bool& combat);

	static void defeat_boss();

	static std::string unlock();
};
