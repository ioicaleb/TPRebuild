#include "input_handler.h"
#include <map>

static bool combat = false;

std::map<std::string, std::string> Valid_inputs {
	{"Move", "(Room) All done in this room? Move on to the next room, but watch out for potential tootsie pops."},
	{"Lick", "The only way to get to the center is to erode the candy coating. Get licking!"},
	{"Sugar", "Strategy, eh? Well if you're worried about taking that next lick, confirm your sugar level before going for it."},
	{"Map", "This house is so big that it's easy to get lost in. Pull out the map to see where to go next."},
	{"Search", "You may have missed something you can interact with. Take another look around."},
	{"Check", "(Item) You remember that thing you picked up earlier? It might be useful. Check it out just to be sure."},
	{"Use", "(Item) Those items in your pack aren't just there to look pretty. Put them to good use"},
	{"Get", "(Item) Your supplies have been scattered. You must recover them. If you come across one, use this to add it to your toolbelt."},
	{"Hint", "In the stress and surprise, you may have forgotten your master plan. That's fine. You can scan your mind for bits of the plan."},
	{"Help", "It helps to take time to reflect on your options. Help yourself out by stopping for a breather."},
#ifdef _DEBUG
	{"Gimme", "Shhhh... Debugging is long and hard. Just do it for me."},
#endif
	{"Quit", "There are no saves, but you can quit out whenever you feel like it."}
};

static void list_help() {
	for (auto pair : Valid_inputs) {
		Dialogue::print_line(pair.first + " - " + pair.second, 10);
	}
}

void Input_Handler::handle_action(Input_Action& action)
{
	if (action.command == "lick") {
		combat = Characters_Handler::attack_enemy(combat);

		if (Characters_Handler::get_player().get_sugar_level() > 99) {
			Game_Manager::lose_game();
		}
	}
	else if (action.command == "move") {
		action = action.target == "" ? User_Input::get_target(action, "Which room would you like to go to?") : action;
		if(Room_Handler::change_room(action.target, combat))
		{
			Characters_Handler::spawn_enemy(Room_Handler::get_current_location());
		}
	}
	else if (action.command == "map") {
		Room_Handler::Map.view_rooms();
	}
	else if (action.command == "check") {
		action = action.target == "" ? User_Input::get_target(action, "Which item would you like to check?") : action;
		Item* itemptr = Stuff_Handler::get_itemptr(action.target);
		if (itemptr == nullptr)
		{
			Interactable* interactptr = Stuff_Handler::get_interactptr(action.target);
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
	else if (action.command == "use") {
		action = action.target == "" ? User_Input::get_target(action, "Which item would you like to use?") : action;
		if (action.target == "sink") {
			if (Room_Handler::get_current_location() == std::string("Kitchen")) {
				Stuff_Handler::handle_use_switch("kitchen sink");
			}
			else if (Room_Handler::get_current_location() == std::string("Bathroom")) {
				Stuff_Handler::handle_use_switch("bathroom sink");
			}
		}
		else if (action.target == "bed") {
			if (Room_Handler::get_current_location() == std::string("Master Bedroom")) {
				Stuff_Handler::handle_use_switch("master bed");
			}
			else if (Room_Handler::get_current_location() == std::string("Guest Bedroom")) {
				Stuff_Handler::handle_use_switch("guest bed");
			}
		}
		else {
			Stuff_Handler::handle_use_switch(action.target);
			if (action.target == "key" && Room_Handler::get_current_location() == "Garage" && !Room_Handler::Map.verify_boss("Garage")) {
				combat = true;
				Characters_Handler::spawn_enemy("Garage");
			}
			else if (action.target == "ladder" && Room_Handler::get_current_location() == "Attic" && !Room_Handler::Map.verify_boss("Attic")) {
				combat = true;
				Characters_Handler::spawn_enemy("Attic");
			}
			else if (action.target == "camping lantern" && Room_Handler::get_current_location() == "Basement" && !Room_Handler::Map.verify_boss("Basement")) {
				combat = true;
				Characters_Handler::spawn_enemy("Basement");
			}
		}

	}
	else if (action.command == "get") {
		action = action.target == "" ? User_Input::get_target(action, "Which item would you like to get?") : action;
		if (!Stuff_Handler::verify_item(action.target)) {
			Dialogue::print_line("There's no " + action.target + " to take.");
		}
		else if (Stuff_Handler::verify_inventory(action.target)) {
			Dialogue::print_line("You already have one. USE your TOOLBELT to check what you have.");
		}
		else if (Room_Handler::Map.verify_room_item(action.target, "get")) {
			if (Stuff_Handler::add_item(action.target)) {
				Stuff_Handler::handle_get_item(action.target);
			}
			else {
				Dialogue::print_line("You can't fit " + Dialogue::set_article(action.target) + action.target + " anywhere on your TOOLBELT.");
			}
		}
		else {
			Dialogue::print_line("You can't take " + Dialogue::set_article(action.target) + action.target + " with you.");
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

void Input_Handler::create_send_action(const std::string& command) { 
	Input_Action action = Input_Action(command);
	handle_action(action); 
};
