#pragma once
#include <set>
#include <string>

class Room
{
private:
	double Encounter_chance;

public:
	/// <summary>
	/// Multiply room encounter chance by random number to determine if enemy spawns
	/// </summary>
	/// <returns>Whether or not to spawn enemy</returns>
	bool roll_encounter();

	std::string Name;
	std::string Description;

	std::set<std::string> Get_items{};

	std::set<std::string> Useable_items{
		"toolbelt",
		"water bottle",
		"mouthguard",
		"dentures",
		"mints",
		"batteries" };

	std::set<std::string> Interactables{ "light switch" };

	Room(std::string name, std::string description, double encounter_chance, std::set<std::string> get_items, std::set<std::string> interactable_items, std::set<std::string> usable_items);
};

struct Map_Handler
{
	/// <summary>
	/// Adds the Hidden room to rooms list
	/// </summary>
	void add_hidden_room();

	bool Locked_Garage = true;
	bool Locked_Attic = true;
	bool Locked_Basement = true;
	bool Hidden_room_hidden = true;
	bool Bishop_defeated = false;
	bool Rook_defeated = false;
	bool Knight_defeated = false;
	bool King_defeated = false;

	/// <summary>
	/// Return if Room boss has been defeated
	/// </summary>
	/// <param name="room_name"></param>
	/// <returns></returns>
	bool verify_boss(const std::string& room_name);

	/// <summary>
	/// Return if Room is locked
	/// </summary>
	/// <param name="room_name"></param>
	/// <returns></returns>
	bool verify_locked(const std::string& room_name);

	/// <summary>
	/// Set boss to be defeated and handle results of victory
	/// </summary>
	/// <param name="room_name"></param>
	/// <returns></returns>
	std::string defeat_boss(std::string room_name);

	/// <summary>
	/// Unlock room and handle results of unlocking
	/// </summary>
	/// <param name="room_name"></param>
	/// <returns></returns>
	std::string unlock(std::string room_name);

	/// <summary>
	/// Return pointer to room
	/// </summary>
	/// <param name="room_name"></param>
	/// <returns></returns>
	Room* get_room(const std::string& room_name);

	/// <summary>
	/// Adds list of strings to gettable items for room
	/// </summary>
	/// <param name="room_name"></param>
	/// <param name="items"></param>
	void add_get_item(const std::string& room_name, std::set<std::string> items);

	/// <summary>
	/// Removes list of strings from gettable items for room
	/// </summary>
	/// <param name="room_name"></param>
	/// <param name="items"></param>
	void remove_get_item(const std::string& room_name, std::set<std::string> items);

	/// <summary>
	/// Adds list of strings to useable items for room
	/// </summary>
	/// <param name="room_name"></param>
	/// <param name="items"></param>
	void add_use_item(const std::string& room_name, std::set<std::string> items);

	/// <summary>
	/// Removes list of strings from useable items for room
	/// </summary>
	/// <param name="room_name"></param>
	/// <param name="items"></param>
	void remove_use_item(const std::string& room_name, std::set<std::string> items);

	/// <summary>
	/// Adds list of strings to interactable items for room
	/// </summary>
	/// <param name="room_name"></param>
	/// <param name="items"></param>
	void add_interactable(const std::string& room_name, std::set<std::string> items);

	/// <summary>
	/// Removes list of strings from interactable items for room
	/// </summary>
	/// <param name="room_name"></param>
	/// <param name="items"></param>
	void remove_interactable(const std::string& room_name, std::set<std::string> items);

	bool verify_room_item(const std::string& item_name, const std::string& command);

	/// <summary>
	/// Returns list of room names with current room marked
	/// </summary>
	void view_rooms();
};
