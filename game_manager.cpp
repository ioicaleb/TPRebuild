#include "game_manager.h"
#include "tutorial.h"

static bool game_over = false;

void Game_Manager::start_game() {
	Dialogue::show_title();
	std::cin.get();
	system("CLS");
	Dialogue::show_opening_monologue();
	std::cin.get();
	system("CLS");
	Collections::reset_collections();
	
	if (User_Input::get_bool("Would you like a tutorial?: ")) {
		Tutorial_Handler::teach();
	}
	else {
		Dialogue::print_line("I understand. Let's just drop you right into it.");
		Dialogue::add_pause(600);
		system("CLS");
		Dialogue::print_line("You hop out of your bed. You're in your master bedroom.");
		Dialogue::print_line("");
	}
	while (!game_over) {
		Input_Action command = User_Input::get_action("What would you like to do?: ");
		Input_Handler::handle_action(command);
		Dialogue::print_line("");
	};
};

void Game_Manager::win_game() {
	game_over = true;
	Dialogue::print_line("Congratulations! You have answered the age old question! It took " + std::to_string(Characters_Handler::get_player().get_licks()) + " licks to get to the center of yourself.\nThanks for playing! To quit out of the game, press enter.");
	std::cin.get();
	Dialogue::print_line("Bye! Have a good one!");
	Dialogue::add_pause(600);
	system("CLS");
}

void Game_Manager::lose_game() {
	Dialogue::print_line("Your head aches.");
	Dialogue::add_pause(300);
	Dialogue::print_line("Your vision blurs.");
	Dialogue::add_pause(300);
	Dialogue::print_line("Every muscle in your body spasms and twitches.");
	Dialogue::add_pause(300);
	Dialogue::print_line("You collapse to the ground. Your sugar level is too high! It's a sugar crash!\nYou can't go on. You'll have to start over and try again.");
	Dialogue::add_pause(300);
	Dialogue::print_line("Sorry, but your game is over. Press Enter to quit.");
	game_over = true;
};

void Game_Manager::quit_game() {
	if (User_Input::get_bool("Are you sure you want to quit?: ")) {
		Dialogue::print_line("Bye! Thanks for playing!");
		game_over = true;
	};
};
