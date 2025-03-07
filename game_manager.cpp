#include "dialogue.h"
#include "game_manager.h"
#include "user_input.h"
#include "characters.cpp"
#include "input_handler.h"
#include <iostream>

static bool game_over = false;

void Game_Manager::start_game() {
	show_title();
	std::cin.get();
	system("CLS");
	show_opening_monologue();
	std::cin.get();
	system("CLS");
	if (user_input::get_bool("Would you like a tutorial?: ")) {
		
	}
	else {
		print_line("I understand. Let's just drop you right into it.");
		add_pause(600);
		system("CLS");
		print_line("You hop out of your bed. You're in your master bedroom.");
		print_line("");
	}
	while (!game_over) {
		Input_Handler::handle_action(user_input::get_action("What would you like to do?: "));
		print_line("");
	};
};

void Game_Manager::win_game() {
	game_over = true;
	print_line("Congratulations! You have answered the age old question! It took " + std::to_string(player.get_licks()) + " licks to get to the center of yourself.\nThanks for playing! To quit out of the game, press enter.");
	std::cin.get();
	print_line("Bye! Have a good one!");
	add_pause(600);
	system("CLS");
}

void Game_Manager::lose_game() {
	print_line("Your head aches.");
	add_pause(300);
	print_line("Your vision blurs.");
	add_pause(300);
	print_line("Every muscle in your body spasms and twitches.");
	add_pause(300);
	print_line("You collapse to the ground. Your sugar level is too high! It's a sugar crash!\nYou can't go on. You'll have to start over and try again.");
	add_pause(300);
	print_line("Sorry, but your game is over. Press Enter to quit.");
	game_over = true;
};

void Game_Manager::quit_game() {
	if (user_input::get_bool("Are you sure you want to quit?: ")) {
		print_line("Bye! Thanks for playing!");
		game_over = true;
	};
};