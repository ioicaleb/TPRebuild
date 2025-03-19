#include "room_handler.h"

static std::string Current_location = "Master Bedroom";

static Map_Handler Map = Map_Handler();

bool Room_Handler::change_room(const std::string& target, bool& combat) {
	Room* roomptr = Map.get_room(target);
	if (roomptr == nullptr) {
		Dialogue::print_line("That's not somewhere you can go right now.");
		return false;
	};
	if (combat) {
		if (!User_Input::get_bool("Are you sure you want to run away?: ")) {
			return false;
		}
	}
	Room room = *roomptr;
	Dialogue::print_line(format("\nYou are now in the {}.\n", room.Name));
	Dialogue::print_line(room.Description);
	Current_location = room.Name;

	combat = room.roll_encounter();

	return true;
};

void Room_Handler::view_rooms() {
	for (Room* roomptr : Map.Rooms) {
		Room room = *roomptr;
		Dialogue::print_line(format("{0} {1}", room.Name, (Current_location == room.Name ? " - Current Location" : "")));
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
		Room room = *Map.get_room(Current_location);
		for (std::string item : room.Interactables) {
			Dialogue::print_line(item);
		}
	}
}

std::string Room_Handler::get_current_location() { return Current_location; };
