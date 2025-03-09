#include "collections.h"

using namespace std;

set<Room> Rooms = {};

set<Items> All_items = {};

set<Items*> Inventory = {};

map<string, string> Valid_inputs = {};

set<Interactables> All_interactables = {
	Interactables(string("light switch"), string("")),
	Interactables(string("bathtub"), string("")),
	Interactables(string("master bed"), string("")),
	Interactables(string("guest bed"), string("")),
	Interactables(string("buried switch"), string("")),
	Interactables(string("endgame switch"), string("")),
	Interactables(string("cabinet"), string("")),
	Interactables(string("candles"), string("")),
	Interactables(string("chair"), string("")),
	Interactables(string("car"), string("")),
	Interactables(string("chest"), string("")),
	Interactables(string("closet"), string("")),
	Interactables(string("computer"), string("")),
	Interactables(string("couch"), string("")),
	Interactables(string("craft bench"), string("")),
	Interactables(string("desk"), string("")),
	Interactables(string("dresser"), string("")),
	Interactables(string("fridge"), string("")),
	Interactables(string("furnace"), string("")),
	Interactables(string("home gym"), string("")),
	Interactables(string("lawnmower"), string("")),
	Interactables(string("medicine cabinet"), string("")),
	Interactables(string("milk crates"), string("")),
	Interactables(string("night stand"), string("")),
	Interactables(string("belt sander"), string("")),
	Interactables(string("kitchen sink"), string("")),
	Interactables(string("bathroom sink"), string("")),
	Interactables(string("table"), string("")),
	Interactables(string("toilet"), string("")),
	Interactables(string("towel"), string("")),
	Interactables(string("water bowl"), string("")),
	Interactables(string("water main"), string(""))
};

void Collections::add_inventory(Items* item) { Inventory.insert(item); };

bool Collections::verify_input(const string& input) { 
	for (auto pair : Valid_inputs) {
		if (Dialogue::lowercase(pair.first) == input) {
			return true;
		}
	}
	return false;
};

bool verify_item(const string& target) {
	for (Items item : All_items) {
		if (item.Name == target) {
			return true;
		};
	}
	return false;
};

bool verify_interactable(const string& target) {
	for (Interactables interactable : All_interactables) {
		if (interactable.Name == target) {
			return true;
		};
	}
	return false;
};

bool verify_room(const string& target) {
	for (Room room : Rooms) {
		if (room.Name == target) {
			return true;
		};
	}
	return false;
};

bool Collections::verify_inventory(const string& name) {
	for (Items* item : Inventory) {
		if ((*item).Name == name) {
			return true;
		}
	}
	return false;
};

Items* Collections::get_item(const string& name) {
	if (verify_item(name)) {
		for (Items item : All_items)
		{
			if (item.Name == name) {
				return &item;
			};
		};
	}
	return nullptr;
};

Items* Collections::get_inventory_item(const string& name) {
	if (Collections::verify_inventory(name)) {
		for (Items* item : Inventory)
		{
			if ((*item).Name == name) {
				return item;
			};
		};
	};
	return nullptr;
};

Interactables* Collections::get_interactable(const string& name) {
	if (verify_interactable(name)) {
		for (Interactables item : All_interactables) {
			if (item.Name == name) {
				return &item;
			}
		}
	}
	return nullptr;
}

Room* Collections::get_room(const string& name) {
	if (verify_room(name)) {
		for (Room room : rooms) {
			if (room.Name == name) {
				return &room;
			}
		}
	}
	return nullptr;
};

void Collections::remove_item(Items* item) {
	Inventory.erase(item);
};

void create_map() {
	Rooms = {
		Room(string("Attic"), string("The attic hatch is open but out of reach.You see where you could hook a LADDER if you had one."), 0.5, {}, {}),
		Room(string("Backyard"), string(""), 0.1, {}, {}),
		Room(string("Basement"), string(""), 0.1, {}, {}),
		Room(string("Bathroom"), string(""), 0.1, {}, {}),
		Room(string("Dining Room"), string(""), 0.1, {}, {}),
		Room(string("Garage"), string(""), 0.1, {}, {}),
		Room(string("Guest Bedroom"), string(""), 0.1, {}, {}),
		Room(string("Kitchen"), string(""), 0.1, {}, {}),
		Room(string("Living Room"), string(""), 0.1, {}, {}),
		Room(string("Master Bedroom"), string(""), 0.1, {}, {}),
		Room(string("Office"), string(""), 0.1, {}, {}),
		Room(string("Pantry"), string(""), 0.1, {}, {})
	};
};
void add_All_items() {
	All_items = {
		Items(string("tool belt"), string("")),
		Items(string("water bottle"), string("")),
		Items(string("mouthguard"), string("")),
		Items(string("dentures"), string("")),
		Items(string("mints"), string("")),
		Items(string("batteries"), string("")),
		Items(string("camping lantern"), string("")),
		Items(string("hint list"), string("")),
		Items(string("key"), string("")),
		Items(string("knife"), string("")),
		Items(string("ladder"), string("")),
		Items(string("metal detector"), string("")),
		Items(string("shovel"), string(""))
	};
};

void add_Valid_inputs() {
	Valid_inputs["Move"] = "(Room) All done in this room? Move on to the next room, but watch out for potential tootsie pops.";
	Valid_inputs["Lick"] = "The only way to get to the center is to erode the candy coating. Get licking!";
	Valid_inputs["Sugar"] = "Strategy, eh? Well if you're worried about taking that next lick, confirm your sugar level before going for it.";
	Valid_inputs["Map"] = "This house is so big that it's easy to get lost in. Pull out the map to see where to go next.";
	Valid_inputs["Search"] = "You may have missed something you can interact with. Take another look around.";
	Valid_inputs["Check"] = "(Item) You remember that thing you picked up earlier? It might be useful. Check it out just to be sure.";
	Valid_inputs["Use"] = "(Item) Those items in your pack aren't just there to look pretty. Put them to good use";
	Valid_inputs["Get"] = "(Item) Your supplies have been scattered. You must recover them. If you come across one, use this to add it to your tool belt.";
	Valid_inputs["Hint"] = "In the stress and surprise, you may have forgotten your master plan. That's fine. You can scan your mind for bits of the plan.";
	Valid_inputs["Help"] = "It helps to take time to reflect on your options. Help yourself out by stopping for a breather.";
#ifdef DEBUG
	Valid_inputs["Gimme"] = "Shhhh... Debugging is long and hard. Just do it for me.";
#endif
	Valid_inputs["Quit"] = "There are no saves, but you can quit out whenever you feel like it.";
};

void Collections::add_hidden_room() {
	Room hidden_room = Room(string("Hidden Room"), string(""), 0.1, {}, {});
	hidden_room.Boss_defeated = false;
	Rooms.insert(Room(string("Hidden Room"), string(""), 0.1, {}, {}));
};

void Collections::reset_collections() {
	create_map();
	add_All_items();
	Inventory = {};
	add_Valid_inputs();
};
