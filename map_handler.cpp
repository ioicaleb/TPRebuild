#include "map_handler.h"
#include "stuff_handler.h"

Room Attic = Room(std::string("Attic"), std::string("The attic hatch is open but out of reach. You see where you could hook a LADDER if you had one."), 1.0, {}, {}, { "ladder" });
Room Backyard = Room(std::string("Backyard"), std::string("You step outside for just a moment. The air is temperate and comfortable. Fresh air fills your lungs and reinvigorates you. Underneath it's cover rests your LAWNMOWER, a gift from your grandfather.\nYou see many mounds of dirt from where your yard has been dug up. You didn't dig any of these holes and you're not excited about needing to resod the lawn."), 0.1, {}, { "lawnmower" }, { "metal detector" });
Room Basement = Room(std::string("Basement"), std::string("You open the door to the basement and creep down the steps.\nThe basement is pitch black. You can't see your own hands.\nThe light switch clicks uselessly.\n...\nYou need to find a light source to explore further."), 1.0, {}, {}, { "camping lantern" });
Room Bathroom = Room(std::string("Bathroom"), std::string("You enter the bathroom, looking to take a break from your lolipop fighting. The modestly sized room fits a SINK with a mirrored MEDICINE CABINET above it, a BATHTUB with your favorite TOWEL hanging on a nearby towel rack, and a porcelain white TOILET."), 0.2, { "dentures" }, { "bathroom sink", "bathtub", "towel", "medicine cabinet", "toilet" }, {});
Room Dining_room = Room(std::string("Dining Room"), std::string("The dining room is ornately decorated. The TABLE is set with silver candle holders with long white CANDLES and empty dishes. The CHAIRs are all pushed in curteously."), 0.7, {}, { "candles", "chair", "table" }, {});
Room Garage = Room(std::string("Garage"), std::string("You turn the knob to discover that the door is locked. No matter how hard you press against the door, while trying to not break it down (you still have to live here after all), you can't seem to get in. You need to find the KEY."), 1.0, {}, {}, { "key" });
Room Guest_bedroom = Room(std::string("Guest Bedroom"), std::string("The guest bedroom is still messy from a recent guest. You really need to get around to cleaning the room up. The BED is untidy and the NIGHTSTAND is dissheveled."), 0.45, { "mouthguard" }, { "bed", "nightstand" }, {});
Room Kitchen = Room(std::string("Kitchen"), std::string("The kitchen seems disturbingly still. Your FRIDGE is silent, the SINK is dry as a bone, the CABINET doors are shut tight, and the WATER BOWL is full and still. Everything seems to be neatly in its place.\nExcept for your utility KNIFE, which you seem to have left on the counter near the sink."), 0.8, { "knife", "water bottle" }, { "kitchen sink", "cabinet", "fridge", "water bowl" }, {});
Room Living_room = Room(std::string("Living Room"), std::string("The COUCH in your living room looks like lolipops have been jumping on it. The television has been knocked off of the entertainment stand. Your mail is scattered all across your coffee table, which is suspiciously missing your remotes."), 0.6, { "key", "mints" }, { "couch" }, {});
Room Master_bedroom = Room(std::string("Master Bedroom"), std::string("You return to the Master Bedroom. Perhaps, you missed something before. Better safe than sorry. Couldn't hurt to check under the BED, through the DRESSER, or in the CLOSET."), 0.6, { "toolbelt" }, { "master bed", "dresser", "closet" }, {});
Room Office = Room(std::string("Office"), std::string("Small but cozy, you always feel at peace in your office. Your COMPUTER sits on a mahogany DESK."), 0.4, { "batteries", "hints" }, { "desk", "computer" }, {});
Room Pantry = Room(std::string("Pantry"), std::string("As you open the doors to the pantry, you hear rustling all over. There are almost certainly lolipops here. Of course, they're easy to find with a simple SEARCH."), 0.95, {}, {}, {});
Room Hidden_room = Room(std::string("Hidden Room"), std::string("The spiral staircase stretches on and on, down deeper and deeper below your house. Your feet finally find a landing on a solid concrete floor. A bright light blinds you before your eyes can adjust."), 1.0, {}, {}, { "knife", "shovel" });

std::set<Room*> Rooms{ &Attic, &Backyard, &Basement, &Bathroom, &Dining_room, &Garage, &Guest_bedroom, &Kitchen, &Living_room, &Master_bedroom, &Office, &Pantry };

void Map_Handler::add_hidden_room() { Rooms.insert(&Hidden_room); };

void Map_Handler::view_rooms() {
	for (Room* roomptr : Rooms) {
		Room room = *roomptr;
		Dialogue::print_line(format("{0} {1}", room.Name, (Room_Handler::get_current_location() == room.Name ? " - Current Location" : "")));
	}
}

Room* Map_Handler::get_room(const std::string& room_name) {
	for (Room* room : Rooms) {
		if (Dialogue::lowercase(room->Name) == Dialogue::lowercase(room_name)) {
			return room;
		}
	}
	return nullptr;
};

bool Map_Handler::verify_boss(const std::string& room_name) {
	if (room_name == "Garage") {
		return Bishop_defeated;
	}
	else if (room_name == "Basement") {
		return Rook_defeated;
	}
	else if (room_name == "Attic") {
		return Knight_defeated;
	}
	else if (room_name == "Hidden Room") {
		return King_defeated;
	}
};

bool Map_Handler::verify_locked(const std::string& room_name) {
	if (room_name == "Garage") {
		return Locked_Garage;
	}
	else if (room_name == "Basement") {
		return Locked_Basement;
	}
	else if (room_name == "Attic") {
		return Locked_Attic;
	}
	else if (room_name == "Hidden Room") {
		return Hidden_room_hidden;
	}
};

std::string Map_Handler::defeat_boss(std::string room_name) {
	std::string message = "";
	if (room_name == "Attic") {
		Knight_defeated = true;
		message = "You see the small gilded CHEST your grandmother bequeathed you, just as you left it." + Stuff_Handler::verify_inventory("camping lantern") ? "" : "\nYour camping LANTERN rests on some boxes of halloween decorations.";
		add_get_item("Attic", { "camping lantern" });
		add_interactable("Attic", { "chest" });
		Attic.Description += " " + message;
	}
	else if (room_name == "Basement") {
		Rook_defeated = true;
		message = "The pale glow of the lantern illuminates the FURNACE and the WATER MAIN.";
		bool has_detector = Stuff_Handler::verify_inventory("metal detector");
		bool has_shovel = Stuff_Handler::verify_inventory("shovel");
		bool has_both = has_detector && has_shovel;
		if (!has_detector || !has_shovel) {
			"\nOn a wall rack, you see your " + has_detector ? "" : "METAL DETECTOR" + has_both ? "" : "and" + has_shovel ? "" : "SHOVEL" + std::string(".");
		}
		Basement.Description = Basement.Description.substr(0, Basement.Description.find("\n")) + "\n" + message;
		add_interactable("Basement", { "furnace", "water main" });
		add_get_item("Basement", { "metal detector", "shovel" });
	}
	else if (room_name == "Garage") {
		Bishop_defeated = true;
		add_interactable("Garage", { "craft bench", "car" });
		add_use_item("Garage", { "knife" });
		message = "As you look around, you can see your CAR parked where you left it and a CRAFT BENCH set up against the far wall.";
		Garage.Description = Garage.Description.substr(0, Garage.Description.find("\n")) + "\n" + message;;
	}
	else if (room_name == "Hidden Room") {
		King_defeated = true;
		message = "You see a BUTTON on the far wall with a sign over it that says, \n\"Evil Plan Abort Button\nDo Not Press Unless King Has Been Defeated\".";
		Hidden_room.Description += "\n" + message;
		add_interactable("Hidden Room", { "button" });
	}

	return message;
};

std::string Map_Handler::unlock(std::string room_name) {
	std::string message = "";
	if (room_name == "Attic") {
		Locked_Attic = false;
		message = "The light pours in through large windows on the far side of the attic. The shine gleams off of your HOME GYM equipment that you put here after converting the guest bedroom.";
		Attic.Description = message;
		add_interactable("Attic", { "home gym" });
		remove_use_item("Attic", { "ladder" });
	}
	else if (room_name == "Basement") {
		Locked_Basement = false;
		message = "In the dim light of the basement, you can see a stack of MILK CRATES and a vague silhouette.";
		Basement.Description = Basement.Description.substr(0, Basement.Description.find("\n")) + "\n" + message;
		add_interactable("Basement", { "milk crates" });
	}
	else if (room_name == "Garage") {
		Locked_Garage = false;
		message = "The door to the garage sticks slightly as you force it open. You pull the string on the light bulb to see a messy, disorganized garage.\nYou almost trip over your belt SANDER, whose cord runs into the wall plug near the door.";
		Garage.Description = message;
		add_interactable("Garage", { "sander" });
	}
	else if (room_name == "Hidden Room") {
		Hidden_room_hidden = false;
	}
	else {
		message = "Uh oh... This room wasn't locked and I wasn't supposed to allow you to unlock it...\nIf you're reading this... something... somewhere has definitely broken... Sorry.";
	}
	return message;
};

void Map_Handler::add_get_item(const std::string& room_name, std::set<std::string> items) {
	Room* room = get_room(room_name);
	room->Get_items.insert(items.begin(), items.end());
};
void Map_Handler::remove_get_item(const std::string& room_name, std::set<std::string> items) {
	Room* room = get_room(room_name);
	for (std::string item : items) {
		room->Get_items.erase(item);
	}
};
void Map_Handler::add_use_item(const std::string& room_name, std::set<std::string> items) {
	Room* room = get_room(room_name);
	room->Useable_items.insert(items.begin(), items.end());
};
void Map_Handler::remove_use_item(const std::string& room_name, std::set<std::string> items) {
	Room* room = get_room(room_name);
	for (std::string item : items) {
		room->Useable_items.erase(item);
	}
};

void Map_Handler::add_interactable(const std::string& room_name, std::set<std::string> items) {
	Room* room = get_room(room_name);
	room->Interactables.insert(items.begin(), items.end());
};

void Map_Handler::remove_interactable(const std::string& room_name, std::set<std::string> items) {
	Room* room = get_room(room_name);
	for (std::string item : items) {
		room->Interactables.erase(item);
	}
};

bool Map_Handler::verify_room_item(const std::string& item_name, const std::string& command) {
	Room* roomptr = get_room(Room_Handler::get_current_location());
	Room room = (*roomptr);
	if (command == "get")
	{
		for (std::string item : room.Get_items) {
			if (item == item_name) {
				return true;
			}
		}
	}
	else if (command == "use") {
		for (std::string item : room.Useable_items) {
			if (item == item_name) {
				return true;
			}
		}
	}
	else if (command == "interact") {
		for (std::string item : room.Interactables) {
			if (item == item_name) {
				return true;
			}
		}
	}

	return false;
}
