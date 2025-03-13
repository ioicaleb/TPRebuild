#pragma once
#include "room.h"
#include "interactables.h"
#include "items.h"
#include <map>

struct Collections
{
	static std::map<std::string, std::string> Valid_inputs;
	static std::vector<Room*> Rooms;

	static void reset_collections();
	static bool verify_input(const std::string& input);
	static bool verify_inventory(const std::string& name);
	static void add_hidden_room();
	static Interactables& get_interactable(const std::string& target);
	static Room& get_room(const std::string& target);
	static Items& get_inventory_item(const std::string& target);
	static Items& get_item(const std::string& target);
	static void remove_item(Items& item);
	static void add_item(Items& item);
};
