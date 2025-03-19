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
		"tool belt",
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
	std::set<Room*> Rooms = { &Attic, &Backyard, &Basement, &Bathroom, &Dining_room, &Garage, &Guest_bedroom, &Kitchen, &Living_room, &Master_bedroom, &Office, &Pantry };

	/// <summary>
	/// Adds the Hidden room to rooms list
	/// </summary>
	void add_hidden_room() { Rooms.insert(&Hidden_room); };

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
	
private:
	Room Attic = Room(std::string("Attic"), std::string("The attic hatch is open but out of reach. You see where you could hook a LADDER if you had one."), 1.0, {}, {}, { "ladder" });
	Room Backyard = Room(std::string("Backyard"), std::string("You step outside for just a moment. The air is temperate and comfortable. Fresh air fills your lungs and reinvigorates you. Underneath it's cover rests your LAWNMOWER, a gift from your grandfather.\nYou see many mounds of dirt from where your yard has been dug up. You didn't dig any of these holes and you're not excited about needing to resod the lawn."), 0.1, {}, { "lawnmower" }, { "metal detector" });
	Room Basement = Room(std::string("Basement"), std::string("You open the door to the basement and creep down the steps.\nThe basement is pitch black. You can't see your own hands.\nThe light switch clicks uselessly.\n...\nYou need to find a light source to explore further."), 1.0, {}, {}, { "lantern" });
	Room Bathroom = Room(std::string("Bathroom"), std::string("You enter the bathroom, looking to take a break from your lolipop fighting. The modestly sized room fits a SINK with a mirrored MEDICINE CABINET above it, a BATHTUB with your favorite TOWEL hanging on a nearby towel rack, and a porcelain white TOILET."), 0.2, { "dentures" }, { "sink", "bathtub", "towel", "medicine cabinet", "toilet" }, {});
	Room Dining_room = Room(std::string("Dining Room"), std::string("The dining room is ornately decorated. The TABLE is set with silver candle holders with long white CANDLES and empty dishes. The CHAIRs are all pushed in curteously."), 0.7, {}, { "candles", "chair", "table" }, {});
	Room Garage = Room(std::string("Garage"), std::string("You turn the knob to discover that the door is locked. No matter how hard you press against the door, while trying to not break it down (you still have to live here after all), you can't seem to get in. You need to find the KEY."), 1.0, {}, {}, { "key" });
	Room Guest_bedroom = Room(std::string("Guest Bedroom"), std::string("The guest bedroom is still messy from a recent guest. You really need to get around to cleaning the room up. The BED is untidy and the NIGHTSTAND is dissheveled."), 0.45, { "mouthguard" }, { "bed", "nightstand" }, {});
	Room Kitchen = Room(std::string("Kitchen"), std::string("The kitchen seems disturbingly still. Your FRIDGE is silent, the SINK is dry as a bone, the CABINET doors are shut tight, and the WATER BOWL is full and still. Everything seems to be neatly in its place.\nExcept for your utility KNIFE, which you seem to have left on the counter near the sink."), 0.8, { "knife", "water bottle" }, { "sink", "cabinet", "fridge", "water bowl" }, {});
	Room Living_room = Room(std::string("Living Room"), std::string("The COUCH in your living room looks like lolipops have been jumping on it. The television has been knocked off of the entertainment stand. Your mail is scattered all across your coffee table, which is suspiciously missing your remotes."), 0.6, { "key", "mints" }, { "couch" }, {});
	Room Master_bedroom = Room(std::string("Master Bedroom"), std::string("You return to the Master Bedroom. Perhaps, you missed something before. Better safe than sorry. Couldn't hurt to check under the BED, through the DRESSER, or in the CLOSET."), 0.6, { "tool belt" }, { "master bed", "dresser", "closet" }, {});
	Room Office = Room(std::string("Office"), std::string("Small but cozy, you always feel at peace in your office.Your COMPUTER sits on a mahogany DESK."), 0.4, { "batteries", "hints" }, { "desk", "computer" }, {});
	Room Pantry = Room(std::string("Pantry"), std::string("As you open the doors to the pantry, you hear rustling all over. There are almost certainly lolipops here. Of course, they're easy to find with a simple SEARCH."), 0.95, {}, {}, {});
	Room Hidden_room = Room(std::string("Hidden Room"), std::string("The spiral staircase stretches on and on, down deeper and deeper below your house. Your feet finally find a landing on a solid concrete floor. A bright light blinds you before your eyes can adjust."), 1.0, {}, {}, { "knife", "shovel" });
};
