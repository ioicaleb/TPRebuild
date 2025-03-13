#include "collections.h"

using namespace std;

vector<Room*> Collections::Rooms = {};

vector<Items*> All_items = {};

vector<Items*> Inventory = {};

map<string, string> Collections::Valid_inputs = {};
map<string, string> *valid_inputs = (&Collections::Valid_inputs);

vector<Interactables*> All_interactables = {};

bool Collections::verify_input(const string& input) {
	for (auto pair : Valid_inputs) {
		if (Dialogue::lowercase(pair.first) == input) {
			return true;
		}
	}
	return false;
};

bool Collections::verify_inventory(const string& name) { 
	for (auto i = Inventory.begin(); i != Inventory.end(); i++) {
		auto item = Inventory[distance(Inventory.begin(), i)];
		if ((*item).Name == name) {
			return true;
		}
	};
	return false;
};

Items& Collections::get_item(const string& name) {
	for (auto i = All_items.begin(); i != All_items.end(); i++)
	{
		auto item = All_items[distance(All_items.begin(), i)];
		if ((*item).Name == name) {
			return *item;
		};
	};
	return *(new Items());
};

Items& Collections::get_inventory_item(const string& name) {
	for (auto i = Inventory.begin(); i != Inventory.end(); i++)
	{
		auto item = Inventory[distance(Inventory.begin(), i)];
		if ((*item).Name == name) {
			return (*item);
		};
	};
	return *(new Items());
};

Interactables& Collections::get_interactable(const string& name) {
	for (auto i = All_interactables.begin(); i != All_interactables.end(); i++)
	{
		Interactables* item = All_interactables[distance(All_interactables.begin(), i)];
		if ((*item).Name == name) {
			return (*item);
		};
	};
	return *(new Interactables());
};

Room& Collections::get_room(const string& name) {
	for (auto i = Rooms.begin(); i != Rooms.end(); i++)
	{
		Room* room = Rooms[distance(Rooms.begin(), i)];
		if ((*room).Name == name) {
			return (*room);
		};
	};
	return *(new Room());
};

void Collections::remove_item(Items& item) {
	Inventory.erase(find(Inventory.begin(), Inventory.end(), &item));
};

void Collections::add_item(Items& item) {
	if (!Collections::verify_inventory(item.Name)) {
		Inventory.push_back(&item);
	}
	else {
		Dialogue::print_line(format("You already have a {}. CHECK your TOOL BELT.", item.Name));
	}
};

void create_map() {
	Room attic = Room(string("Attic"), string("The attic hatch is open but out of reach.You see where you could hook a LADDER if you had one."), 0.5, {}, {});
	Room backyard = Room(string("Backyard"), string(""), 0.1, {}, {});
	Room basement = Room(string("Basement"), string(""), 0.1, {}, {});
	Room bathroom = Room(string("Bathroom"), string(""), 0.1, {}, {});
	Room dining = Room(string("Dining Room"), string(""), 0.1, {}, {});
	Room garage = Room(string("Garage"), string(""), 0.1, {}, {});
	Room guest = Room(string("Guest Bedroom"), string(""), 0.1, {}, {});
	Room kitchen = Room(string("Kitchen"), string(""), 0.1, {}, {});
	Room living = Room(string("Living Room"), string(""), 0.1, {}, {});
	Room master = Room(string("Master Bedroom"), string(""), 0.1, {}, {});
	Room office = Room(string("Office"), string(""), 0.1, {}, {});
	Room pantry = Room(string("Pantry"), string(""), 0.1, {}, {});
	Collections::Rooms.push_back(&attic);
	Collections::Rooms.push_back(&backyard);
	Collections::Rooms.push_back(&basement);
};

void add_all_items() {
	Items tool_belt = Items("tool belt", "");
	/*
	Items bottle = Items("water bottle", "");
	Items mouthguard = Items("mouthguard", "");
	Items dentures = Items(string("dentures"), string(""));
	Items mints = Items(string("mints"), string(""));
	Items batteries = Items(string("batteries"), string(""));
	Items lantern = Items(string("camping lantern"), string(""));
	Items hints = Items(string("hint list"), string(""));
	Items key = Items(string("key"), string(""));
	Items knife = Items(string("knife"), string(""));
	Items ladder = Items(string("ladder"), string(""));
	Items detector = Items(string("metal detector"), string(""));
	Items shovel = Items(string("shovel"), string(""));
	All_items.push_back(&tool_belt);*/
};

void add_all_interactables() {
	Interactables light = Interactables(string("light switch"), string(""));
	Interactables bathtub = Interactables(string("bathtub"), string(""));
	Interactables master_bed = Interactables(string("master bed"), string(""));
	Interactables guest_bed = Interactables(string("guest bed"), string(""));
	Interactables buried = Interactables(string("buried switch"), string(""));
	Interactables endgame = Interactables(string("endgame switch"), string(""));
	Interactables cabinet = Interactables(string("cabinet"), string(""));
	Interactables candles = Interactables(string("candles"), string(""));
	Interactables chair = Interactables(string("chair"), string(""));
	Interactables car = Interactables(string("car"), string(""));
	Interactables chest = Interactables(string("chest"), string(""));
	Interactables closet = Interactables(string("closet"), string(""));
	Interactables computer = Interactables(string("computer"), string(""));
	Interactables couch = Interactables(string("couch"), string(""));
	Interactables bench = Interactables(string("craft bench"), string(""));
	Interactables desk = Interactables(string("desk"), string(""));
	Interactables dresser = Interactables(string("dresser"), string(""));
	Interactables fridge = Interactables(string("fridge"), string(""));
	Interactables furnace = Interactables(string("furnace"), string(""));
	Interactables gym = Interactables(string("home gym"), string(""));
	Interactables mower = Interactables(string("lawnmower"), string(""));
	Interactables medicine = Interactables(string("medicine cabinet"), string(""));
	Interactables crates = Interactables(string("milk crates"), string(""));
	Interactables stand = Interactables(string("night stand"), string(""));
	Interactables sander = Interactables(string("belt sander"), string(""));
	Interactables kitchen_sink = Interactables(string("kitchen sink"), string(""));
	Interactables bathroom_sink = Interactables(string("bathroom sink"), string(""));
	Interactables table = Interactables(string("table"), string(""));
	Interactables toilet = Interactables(string("toilet"), string(""));
	Interactables towel = Interactables(string("towel"), string(""));
	Interactables bowl = Interactables(string("water bowl"), string(""));
	Interactables main = Interactables(string("water main"), string(""));
	All_interactables.push_back(&main);
};

void add_Valid_inputs() {
	(*valid_inputs)[string("Move")] = string("(Room) All done in this room? Move on to the next room, but watch out for potential tootsie pops.");
	(*valid_inputs)[string("Lick")] = string("The only way to get to the center is to erode the candy coating. Get licking!");
	(*valid_inputs)[string("Sugar")] = string("Strategy, eh? Well if you're worried about taking that next lick, confirm your sugar level before going for it.");
	(*valid_inputs)[string("Map")] = string("This house is so big that it's easy to get lost in. Pull out the map to see where to go next.");
	(*valid_inputs)[string("Search")] = string("You may have missed something you can interact with. Take another look around.");
	(*valid_inputs)[string("Check")] = string("(Item) You remember that thing you picked up earlier? It might be useful. Check it out just to be sure.");
	(*valid_inputs)[string("Use")] = string("(Item) Those items in your pack aren't just there to look pretty. Put them to good use");
	(*valid_inputs)[string("Get")] = string("(Item) Your supplies have been scattered. You must recover them. If you come across one, use this to add it to your tool belt.");
	(*valid_inputs)[string("Hint")] = string("In the stress and surprise, you may have forgotten your master plan. That's fine. You can scan your mind for bits of the plan.");
	(*valid_inputs)[string("Help")] = string("It helps to take time to reflect on your options. Help yourself out by stopping for a breather.");
#ifdef _DEBUG
	(*valid_inputs)[string("Gimme")] = string("Shhhh... Debugging is long and hard. Just do it for me.");
#endif
	(*valid_inputs)[string("Quit")] = string("There are no saves, but you can quit out whenever you feel like it.");
};

void Collections::add_hidden_room() {
	Room hidden_room = Room(string("Hidden Room"), string(""), 0.0, {}, {});
	hidden_room.Boss_defeated = false;
	Rooms.push_back(&hidden_room);
};

void Collections::reset_collections() {
	create_map();
	add_all_items();
	add_all_interactables();
	Inventory = {};
	add_Valid_inputs();
};
