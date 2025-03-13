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
		Characters_Handler::attack_enemy(combat);
		
		if (Characters_Handler::get_player().get_sugar_level() > 99) {
			Game_Manager::lose_game();
		}
	}
	else if (action.command == "move") {
		Room_Handler::change_room(Collections::get_room(action.target), combat);
	}
	else if (action.command == "map") {
		Room_Handler::view_rooms();
	}
	else if (action.command == "check") {
		Items item = Collections::get_item(action.target);
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
	else if(action.command == "use") {
		Items item = Collections::get_item(action.target);
		if (item.Name == "")
		{
			Interactables interact = Collections::get_interactable(action.target);
			if (interact.Name != "") {
				interact.use_interactable();
			}
			else {
				Dialogue::print_line("There's no " + action.target + " that you can use.");
			}
		}
		else {
			item.use_item();
		}
	}
	else if (action.command == "get") {
		Items item = Collections::get_item(action.target);
		if (item.Name != "") {
			Collections::add_item(item);
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
#endif
	else if (action.command == "quit") {
		Game_Manager::quit_game();
	}
	else {
		Dialogue::print_line("Sorry. I didn't catch that. Please try again.");
	}
}

void Input_Handler::create_send_action(const char* command) { handle_action(Input_Action(std::string(command))); };
