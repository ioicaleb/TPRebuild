#include "input_handler.h"

static void list_help() {
	for (auto pair : Collections::Valid_inputs) {
		Dialogue::print_line(pair.first + " - " + pair.second, 10);
	}
}

void Input_Handler::handle_action(Input_Action action)
{
	if (action.command == "lick") {
		Characters_Handler::attack_enemy(&combat);
	}
	else if (action.command == "move") {
		Room_Handler::change_room(Collections::get_room(action.target), &combat);
	}
	else if (action.command == "map") {
		Room_Handler::view_rooms();
	}
	else if (action.command == "check") {
		Items* itemptr = Collections::get_item(action.target);
		if (itemptr == nullptr)
		{
			Interactables* interactptr = Collections::get_interactable(action.target);
			if (interactptr != nullptr) {
				Dialogue::print_line((*interactptr).Description);
			}
			else {
				Dialogue::print_line("There's no " + action.target + " to check.");
			}
		}
		else {
			Dialogue::print_line((*itemptr).Description);
		}
	}
	else if(action.command == "use") {
		Items* itemptr = Collections::get_item(action.target);
		if (itemptr == nullptr)
		{
			Interactables* interactptr = Collections::get_interactable(action.target);
			if (interactptr != nullptr) {
				interactptr->use_interactable();
			}
			else {
				Dialogue::print_line("There's no " + action.target + " that you can use.");
			}
		}
		else {
			itemptr->use_item();
		}
	}
	else if (action.command == "get") {
		Items* item = Collections::get_item(action.target);
		if (item != nullptr) {
			item->get_item();
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
		Room_Handler::search_room(&combat);
	}
	else if (action.command == "sugar") {
		Dialogue::print_line("Your sugar level is currently " + to_string(Characters_Handler::player.get_sugar_level()) + "%.");
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
