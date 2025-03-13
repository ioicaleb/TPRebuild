#include "room_handler.h"

static std::string Current_location = "Master Bedroom";

bool Room_Handler::change_room(Room& target, bool& combat) {
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
	for (Room* room : Collections::Rooms) {
		Dialogue::print_line(format("{0} {1} {2}", (*room).Name, (Current_location == (*room).Name ? " - Current Location" : ""), ((*room).Locked ? " - Locked" : "")));
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

std::string Room_Handler::get_current_location() { return Current_location; };
