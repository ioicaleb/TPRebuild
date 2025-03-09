#pragma once
#include "room.h"
#include "items.h"
#include "interactables.h"
#include <set>
#include <map>
#include <algorithm>

struct Collections
{
	static std::map<std::string, std::string> Valid_inputs;
	static std::set<Room> rooms;

	static void reset_collections();
	static bool verify_input(const std::string& input);
	static Items* get_item(const std::string& target);
	static Items* get_inventory_item(const std::string& target);
	static Interactables* get_interactable(const std::string& target);
	static Room* get_room(const std::string& target);
	static bool verify_inventory(const std::string& name);
	static void remove_item(Items* item);
	static void add_hidden_room();
	static void add_inventory(Items* item);
};

