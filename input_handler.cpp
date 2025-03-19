#include "input_handler.h"
#include <map>

static bool combat = false;

std::map<std::string, std::string> Valid_inputs = {
	std::string("Move") = "(Room) All done in this room? Move on to the next room, but watch out for potential tootsie pops.",
	std::string("Lick") = "The only way to get to the center is to erode the candy coating. Get licking!",
	std::string("Sugar") = "Strategy, eh? Well if you're worried about taking that next lick, confirm your sugar level before going for it.",
	std::string("Map") = "This house is so big that it's easy to get lost in. Pull out the map to see where to go next.",
	std::string("Search") = "You may have missed something you can interact with. Take another look around.",
	std::string("Check") = "(Item) You remember that thing you picked up earlier? It might be useful. Check it out just to be sure.",
	std::string("Use") = "(Item) Those items in your pack aren't just there to look pretty. Put them to good use",
	std::string("Get") = "(Item) Your supplies have been scattered. You must recover them. If you come across one, use this to add it to your tool belt.",
	std::string("Hint") = "In the stress and surprise, you may have forgotten your master plan. That's fine. You can scan your mind for bits of the plan.",
	std::string("Help") = "It helps to take time to reflect on your options. Help yourself out by stopping for a breather.",
#ifdef _DEBUG
	std::string("Gimme") = "Shhhh... Debugging is long and hard. Just do it for me.",
#endif
	std::string("Quit") = "There are no saves, but you can quit out whenever you feel like it."
};

static void list_help() {
	for (auto pair : Valid_inputs) {
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
			Room_Handler::change_room(action.target, combat);
	}
	else if (action.command == "map") {
		Room_Handler::view_rooms();
	}
	else if (action.command == "check") {
		Item item = Collections::get_item(action.target);
		if (item.Name == "")
		{
			Interactable interact = Collections::get_interactable(action.target);
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
				Stuff_Handler::handle_use_item(Collections::get_interactable("kitchen sink"));
			}
			else if (Room_Handler::get_current_location() == std::string("Bathroom")) {
				Stuff_Handler::handle_use_item(Collections::get_interactable("bathroom sink"));
			}
		}
		else if (action.target == "bed") {
			if (Room_Handler::get_current_location() == std::string("Master Bedroom")) {
				Stuff_Handler::handle_use_item(Collections::get_interactable("master bed"));
			}
			else if (Room_Handler::get_current_location() == std::string("Guest Bedroom")) {
				Stuff_Handler::handle_use_item(Collections::get_interactable("guest bed"));
			}
		}
		else {
			Item item = Collections::get_item(action.target);
			if (item.Name == "")
			{
				Interactable interact = Collections::get_interactable(action.target);
				if (interact.Name != "") {
					Stuff_Handler::handle_use_item(interact);
				}
				else {
					Dialogue::print_line("There's no " + action.target + " that you can use.");
				}
			}
			else {
				Stuff_Handler::handle_use_item(item);
				if (((item.Name == "key" && Room_Handler::get_current_location() == "Garage") || (item.Name == "ladder" && Room_Handler::get_current_location() == "Attic") || (item.Name == "camping lanter" && Room_Handler::get_current_location() == "Basement") ) && !Room_Handler::Map.verify_boss()) {
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
