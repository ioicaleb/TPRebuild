#pragma once
#include "items.h"
#include "interactables.h"
#include <set>
#include <string>

using namespace std;

class Room
{
private:
	void add_gettable_item(set<string> items);
	void add_interactable(set<string> items);
	void add_useable_item(set<string> items);

public:
	Room();
	Room(string name, string description, double encounter_chance, set<string> getItems, set<string> interactables);
	bool roll_encounter();

	string Name;
	string Description;
	bool Boss_defeated = true;
	bool Locked = false;

	virtual void defeat_boss() {};

	set<string> Get_items{};

	set<string> Usable_items{
		"tool belt",
		"water bottle",
		"mouthguard",
		"dentures",
		"mints",
		"batteries" };

	set<string> Room_interactables{ "light switch" };
};