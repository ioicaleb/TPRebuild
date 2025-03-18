#pragma once
#include "room.h"
#include "interactables.cpp"
#include "items.cpp"
#include <map>

struct Collections
{
	static std::map<std::string, std::string> Valid_inputs;
	static std::vector<Room> Rooms;

	static void reset_collections();
	static bool verify_input(const std::string& input);
	static bool verify_inventory(const std::string& name);
	static void add_hidden_room();
	static Interactables get_interactable(const std::string& target);
	static Room get_room(const std::string& target);
	static Item get_inventory_item(const std::string& target);
	static Item get_item(const std::string& target);
	static void remove_item(Item item);
	static bool add_item(Item item);
	static void get_all_inventory();
};
