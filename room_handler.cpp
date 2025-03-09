#include "room_handler.h"

bool Room_Handler::change_room(Room* target, bool* combat) {
	if (*combat) {
		if (!User_Input::get_bool("Are you sure you want to run away?: ")) {
			return false;
		}
	}
	Dialogue::print_line("\nYou are now in the " + (*target).Name + ".\n");
	Dialogue::print_line((*target).Description);
	Current_location = (*target).Name;

	*combat = (*target).roll_encounter();
	
	return true;
};

void Room_Handler::view_rooms() {
	for (Room room : Collections::rooms) {
		Dialogue::print_line(room.Name + (Current_location == room.Name ? " - Current Location" : "") + (room.Locked ? " - Locked" : ""));
	}
}

void Room_Handler::search_room(bool* combat) {
	if (Current_location == "Pantry") {
		if (*combat) {
			Dialogue::print_line("Woah, you've already got trouble. Take it one at a time, cowboy.");
		}
		else {
			*combat = true;
			Characters_Handler::spawn_enemy("Pantry");
		}
	}
	else {
		Dialogue::print_line("You look around quickly. Here's what seems to be of use around here: ");
		for (string interactable : Collections::verify_room(Current_location).Room_interactables) {
			Dialogue::print_line(interactable);
		}
	}
}
