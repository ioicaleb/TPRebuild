#pragma once
#include "room_handler.h"
#include "characters_handler.h"
#include "game_manager.h"
#include "Windows.h"

class Interactable {
	bool operator==(const Interactable& rhs) const {
		return this->Name == rhs.Name;
	}
public:
	std::string Name;
	std::string Description;
	std::string Use_message;

	Interactable(std::string name, std::string description, std::string use_message) {
		Name = name;
		Description = description;
		Use_message = use_message;
	};
};

struct Item {
	bool operator==(const Item* rhs) const {
		return this->Name == rhs->Name;
	};

	std::string Name;
	std::string Description;

	Item(std::string name, std::string description) {
		this->Name = name;
		this->Description = description;
	};
};

struct Stuff_Handler
{
	static int Water_available;

	static std::vector<Item> All_items;
	static std::vector<Interactable> All_interactables;
	static std::vector<Item*> Inventory;

	/// <summary>
	/// Handles use command for items
	/// </summary>
	/// <param name="item_name">Name of item to use</param>
	static void handle_use_item(const std::string& item_name);

	/// <summary>
	/// Handles use command for interactables
	/// </summary>
	/// <param name="item_name">Name of item to use</param>
	static void handle_use_interact(const std::string& item_name);

	/// <summary>
	/// Handles results of getting some items
	/// </summary>
	/// <param name="name">Name of item that is being gotten</param>
	static void handle_get_item(std::string name);

	/// <summary>
	/// Get a pointer to specified item if it exists
	/// </summary>
	/// <param name="item_name">Name of item to get</param>
	/// <returns>Pointer to item or nullptr</returns>
	static Item* get_itemptr(const std::string& item_name);

	/// <summary>
	/// Get a pointer to a specified interactables if it exists
	/// </summary>
	/// <param name="item_name">Name of item to get</param>
	/// <returns>Pointer to interactable or nullptr</returns>
	static Interactable* get_interactptr(const std::string& item_name);

	/// <summary>
	/// Adds item pointer to Inventory
	/// </summary>
	/// <param name="item_name">Name of item to add</param>
	/// <returns>Success or failure of function</returns>
	static bool add_item(const std::string& item_name);

	/// <summary>
	/// Removes item from Inventory and All_items
	/// </summary>
	/// <param name="item_name">Name of item to remove</param>
	static void remove_item(const std::string& item_name);

	/// <summary>
	/// Verify if item is in list of All_items
	/// </summary>
	/// <param name="item_name">Name of item to check</param>
	/// <returns>If item is in All_items</returns>
	static bool verify_item(const std::string& item_name) { return get_itemptr(item_name) != nullptr; };

	/// <summary>
	/// Verify if item is in list of All_interactables
	/// </summary>
	/// <param name="item_name">Name of item to check</param>
	/// <returns>If item is in All_interactables</returns>
	static bool verify_interact(const std::string& item_name) { return get_interactptr(item_name) != nullptr; };

	/// <summary>
	/// Verify if item is in Inventory
	/// </summary>
	/// <param name="item_name">Name of item to check</param>
	/// <returns>If item is in Inventory</returns>
	static bool verify_inventory(const std::string& item_name);

	/// <summary>
	/// Determines type of item and redirects to appropriate use handler
	/// </summary>
	/// <param name="item_name">Name of item to be used</param>
	static void handle_use_switch(const std::string& item_name);

	static void get_all_inventory();
};
