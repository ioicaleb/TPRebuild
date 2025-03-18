#include "input_handler.h"

static bool combat = false;

static void list_help() {
	for (auto pair : Collections::Valid_inputs) {
		Dialogue::print_line(pair.first + " - " + pair.second, 10);
	}
}

void Input_Handler::handle_action(const Input_Action& action)
{
	if (action.command == "lick") {
		combat = Characters_Handler::attack_enemy(combat);

		if (Characters_Handler::get_player().get_sugar_level() > 99) {
			Game_Manager::lose_game();
		}
	}
	else if (action.command == "move") {
		Room room = Collections::get_room(action.target);
		if (room.Name == "") {
			Dialogue::print_line("That's not somewhere you can go right now.");
		}
		else {
			Room_Handler::change_room(room, combat);
		}
	}
	else if (action.command == "map") {
		Room_Handler::view_rooms();
	}
	else if (action.command == "check") {
		Item item = Collections::get_item(action.target);
		if (item.Name == "")
		{
			Interactables interact = Collections::get_interactable(action.target);
			if (interact.Name != "") {
				Dialogue::print_line(interact.Description);
			}
			else {
				Dialogue::print_line("There's no " + action.target + " to check.");
			}
		}
		else {
			Dialogue::print_line(item.Description);
		}
	}
	else if (action.command == "use") {
		if (action.target == "sink") {
			if (Room_Handler::get_current_location() == std::string("Kitchen")) {
				Item_Handler::handle_use_item(Collections::get_interactable("kitchen sink"));
			}
			else if (Room_Handler::get_current_location() == std::string("Bathroom")) {
				Item_Handler::handle_use_item(Collections::get_interactable("bathroom sink"));
			}
		}
		else if (action.target == "bed") {
			if (Room_Handler::get_current_location() == std::string("Master Bedroom")) {
				Item_Handler::handle_use_item(Collections::get_interactable("master bed"));
			}
			else if (Room_Handler::get_current_location() == std::string("Guest Bedroom")) {
				Item_Handler::handle_use_item(Collections::get_interactable("guest bed"));
			}
		}
		else {
			Item item = Collections::get_item(action.target);
			if (item.Name == "")
			{
				Interactables interact = Collections::get_interactable(action.target);
				if (interact.Name != "") {
					Item_Handler::handle_use_item(interact);
				}
				else {
					Dialogue::print_line("There's no " + action.target + " that you can use.");
				}
			}
			else {
				Item_Handler::handle_use_item(item);
				if (((item.Name == "key" && Room_Handler::get_current_location() == "Garage") || (item.Name == "ladder" && Room_Handler::get_current_location() == "Attic") || (item.Name == "camping lanter" && Room_Handler::get_current_location() == "Basement") ) && !Collections::get_room(Room_Handler::get_current_location()).Boss_defeated) {
					combat = true;
					Characters_Handler::spawn_enemy(Room_Handler::get_current_location());
				}
			}
		}
	}
	else if (action.command == "get") {
		Item item = Collections::get_item(action.target);
		if (item.Name != "") {
			if(Collections::add_item(item)) {
				Item_Handler::handle_get_item(item.Name);
			}
		}
		else {
			Dialogue::print_line("You can't fit " + action.target + " anywhere on your TOOLBELT.");
		}
	}
	else if (action.command == "help") {
		list_help();
	}
	else if (action.command == "hint") {
		Hints::display_hints();
	}
	else if (action.command == "search") {
		Room_Handler::search_room(combat);
	}
	else if (action.command == "sugar") {
		Dialogue::print_line("Your sugar level is currently " + std::to_string(Characters_Handler::get_player().get_sugar_level()) + "%.");
	}
#ifdef _DEBUG
	else if (action.command == "gimmee") {
		Cheat::play_game_for_me();
	}
	else if ("scatter") {
		combat = false;
	}
#endif
	else if (action.command == "quit") {
		Game_Manager::quit_game();
	}
	else {
		Dialogue::print_line("Sorry. I didn't catch that. Please try again.");
	}
}

void Input_Handler::create_send_action(const char* command) { handle_action(Input_Action(std::string(command))); };
