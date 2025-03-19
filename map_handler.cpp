#include "map_handler.h"
#include "stuff_handler.h"

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
		add_get_item("Attic", { "lantern" });
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
		add_get_item("Basement", { "metal detector", "shovel"});
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
		Dialogue::print_line("You attach the ladder to the attic. The rungs creak beneath your feet as you climb.");
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
