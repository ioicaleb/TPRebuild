#include "room_handler.h"

static std::string Current_location = "Master Bedroom";

bool Room_Handler::change_room(Room target, bool& combat) {
	if (combat) {
		if (!User_Input::get_bool("Are you sure you want to run away?: ")) {
			return false;
		}
	}
	Dialogue::print_line(format("\nYou are now in the {}.\n", target.Name));
	Dialogue::print_line(target.Description);
	Current_location = target.Name;

	combat = target.roll_encounter();

	return true;
};

void Room_Handler::view_rooms() {
	for (Room room : Collections::Rooms) {
		Dialogue::print_line(format("{0} {1} {2}", room.Name, (Current_location == room.Name ? " - Current Location" : ""), (room.Locked ? " - Locked" : "")));
	}
}

void Room_Handler::search_room(bool& combat) {
	if (Current_location == "Pantry") {
		if (combat) {
			Dialogue::print_line("Woah, you've already got trouble. Take it one at a time, cowboy.");
		}
		else {
			combat = true;
			Characters_Handler::spawn_enemy("Pantry");
		}
	}
	else {
		Dialogue::print_line("You look around quickly. Here's what seems to be of use around here: ");
		for (std::string item : Collections::get_room(Current_location).Room_interactables) {
			Dialogue::print_line(item);
		}
	}
}

std::string Room_Handler::unlock() {
	Collections::get_room(Current_location).unlock_room();
	std::string message = "";
	if (Collections::get_room(Current_location).Name == "Attic") {
		Dialogue::print_line("You attach the ladder to the attic. The rungs creak beneath your feet as you climb.");
		message = "The light pours in through large windows on the far side of the attic. The shine gleams off of your HOME GYM equipment that you put here after converting the guest bedroom.";
		Collections::get_room(Current_location).Description = message;
		Collections::get_room(Current_location).add_interactable({ "home gym" });
		Collections::get_room(Current_location).remove_useable_item("ladder");
	}
	else if (Collections::get_room(Current_location).Name == "Garage") {
		message = "The door to the garage sticks slightly as you force it open. You pull the string on the light bulb to see a messy, disorganized garage.\nYou almost trip over your belt SANDER, whose cord runs into the wall plug near the door.";
		Collections::get_room(Current_location).Description = message;
		Collections::get_room(Current_location).add_interactable({ "sander" });
	}
	else if (Collections::get_room(Current_location).Name == "Basement") {
		message = "In the dim light of the basement, you can see a stack of MILK CRATES and a vague silhouette.";
		Collections::get_room(Current_location).Description = Collections::get_room(Current_location).Description.substr(0, Collections::get_room(Current_location).Description.find("\n")) + "\n" + message;
		Collections::get_room(Current_location).add_interactable({ "milk crates" });
	}
	else {
		message = "Uh oh... This room wasn't locked and I wasn't supposed to allow you to unlock it...\nIf you're reading this... something... somewhere has definitely broken... Sorry.";
	}
	return message;
}

void Room_Handler::defeat_boss() {
	std::string message;
	Collections::get_room(Current_location).defeat_boss();
	if (Collections::get_room(Current_location).Name == "Attic") {
		std::string message = "You see the small gilded CHEST your grandmother bequeathed you, just as you left it." + Collections::verify_inventory("camping lantern") ? "" : "\nYour camping LANTERN rests on some boxes of halloween decorations.";
		Collections::get_room(Current_location).Get_items.insert("lantern");
		Collections::get_room(Current_location).add_interactable({ "chest" });
		Collections::get_room(Current_location).Description += " " + message;
	}
	else if (Collections::get_room(Current_location).Name == "Garage") {
		Collections::get_room(Current_location).add_interactable({ "craft bench", "car" });
		Collections::get_room(Current_location).add_useable_item("knife");
		std::string message = "As you look around, you can see your CAR parked where you left it and a CRAFT BENCH set up against the far wall.";
		Collections::get_room(Current_location).Description = Collections::get_room(Current_location).Description.substr(0, Collections::get_room(Current_location).Description.find("\n")) + "\n" + message;;
	}
	else if (Collections::get_room(Current_location).Name == "Basement") {
		std::string message = "The pale glow of the lantern illuminates the FURNACE and the WATER MAIN."; 
		if (!Collections::verify_inventory("metal detector") || !Collections::verify_inventory("shovel")) {
			"\nOn a wall rack, you see your " + Collections::verify_inventory("metal detector") ? "" : "METAL DETECTOR" + (Collections::verify_inventory("metal detector") && Collections::verify_inventory("shovel")) ? "" : "and" + Collections::verify_inventory("shovel") ? "" : "SHOVEL" + std::string(".");
		}
		Collections::get_room(Current_location).Description = Collections::get_room(Current_location).Description.substr(0, Collections::get_room(Current_location).Description.find("\n")) + "\n" + message;
		Collections::get_room(Current_location).add_interactable({ "furnace", "water main" });
		Collections::get_room(Current_location).Get_items.insert("metal detector");
		Collections::get_room(Current_location).Get_items.insert("shovel");
	}
	else {
		std::string message = "You see a BUTTON on the far wall with a sign over it that says, \n\"Evil Plan Abort Button\nDo Not Press Unless King Has Been Defeated\".";
		Collections::get_room(Current_location).Description += "\n" + message;
		Collections::get_room(Current_location).add_interactable({ "button" });
	}
	Dialogue::print_line(message);
}

std::string Room_Handler::get_current_location() { return Current_location; };
