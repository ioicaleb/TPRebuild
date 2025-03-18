#pragma once
#include "collections.h"
#include "room_handler.h"
#include "characters_handler.h"
#include "game_manager.h"
#include "Windows.h"

struct Item_Handler
{
	static void handle_use_item(Item item);
	static void handle_use_item(Interactables item);

	static void handle_get_item(std::string name);
};
