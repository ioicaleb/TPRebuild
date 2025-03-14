#pragma once
#include <string>
#include <set>
#include <functional>

class Room
{
private:
	void add_gettable_item(std::set<std::string> items);
	void add_interactable(std::set<std::string> items);
	void add_useable_item(std::set<std::string> items);

public:
	Room() { Name = ""; };
	Room(std::string name, std::string description, double encounter_chance, std::set<std::string> getItems, std::set<std::string> interactables);
	bool roll_encounter();

	std::string Name;
	std::string Description;
	bool Boss_defeated = true;
	bool Locked = false;

	virtual std::string defeat_boss() {};

	std::set<std::string> Get_items{};

	std::set<std::string> Usable_items{
		"tool belt",
		"water bottle",
		"mouthguard",
		"dentures",
		"mints",
		"batteries" };

	std::set<std::string> Room_interactables{ "light switch" };
};
