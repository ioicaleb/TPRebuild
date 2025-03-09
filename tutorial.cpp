#include "dialogue.h"
#include "input_action.cpp"
#include "input_handler.h"
#include "user_input.h"
#include <iostream>

class Tutorial_Handler {
private:
	static void set_room_for_tutorial() {};
	static void reset_room() {};
public:
	static void teach() {
		set_room_for_tutorial();
		Dialogue::print_line("Welcome! There are a preset list of commands that will work. This tutorial will highlight a few, but you can get a full list at any time by typing HELP.");
		Dialogue::print_line("Let's begin with the basics. Type in your command and what you intend to target before pressing enter to submit you request. Be sure to check your spelling. The game is not good at guessing what you meant.");
		Dialogue::print_line("For example, if you want to check the MASTER BEDROOM, you would type in MOVE MASTER BEDROOM.");
		bool stepComplete = false;
		while (!stepComplete)
		{
			Input_Action practiceIA(User_Input::get_action("Go ahead try it: "));
			if (practiceIA.command == "move" && practiceIA.target == "master bedroom")
			{
				Input_Handler::handle_action(practiceIA);
				stepComplete = true;
			}
			else
			{
				Dialogue::print_line("Not quite. Try again.");
			}
		}
		stepComplete = false;
		Dialogue::print_line("Great! You've moved to the Master Bedroom. You can also interact with items in the rooms. Keep an eye out for any capitalized words. These are either things you can interact with, rooms you can visit, or command suggestions.");
		Dialogue::print_line("If you forget what was in the room, you can always use SEARCH. SEARCH will show you a list of things you can interact with in the room. SEARCH doesn't require a target, the command is enough on its own.");
		while (!stepComplete)
		{
			Input_Action practiceIA(User_Input::get_action("Go ahead try it: "));
			if (practiceIA.command == "search")
			{
				Input_Handler::handle_action(practiceIA);
				stepComplete = true;
			}
			else
			{
				Dialogue::print_line("Not quite. Try again.");
			}
		}
		stepComplete = false;
		Dialogue::print_line("Great! You can interact with any of these using the USE command and then whatever you want to interact with. For practice, let's USE the CLOSET.");
		while (!stepComplete)
		{
			Input_Action practiceIA(User_Input::get_action("Go ahead try it: "));
			if (practiceIA.command == "use" && practiceIA.target == "closet")
			{
				Input_Handler::handle_action(practiceIA);
				stepComplete = true;
			}
			else
			{
				Dialogue::print_line("Not quite. Try again.");
			}
		}
		stepComplete = false;
		Dialogue::print_line("The TOOL BELT is one of the most useful items you will find. USE will help you find items you can grab, but you have to use GET to actually take the item. Just type GET and then the item name, i.e. GET TOOL BELT.");
		while (!stepComplete)
		{
			Input_Action practiceIA(User_Input::get_action("Go ahead try it: "));
			if (practiceIA.command == "get" && practiceIA.target == "tool belt")
			{
				Input_Handler::handle_action(practiceIA);
				stepComplete = true;
			}
			else
			{
				Dialogue::print_line("Not quite. Try again.");
			}
		}
		Dialogue::print_line("Now that you have your TOOL BELT, you can use it at any time. While each item has its own special use, your TOOL BELT can be USEd to look at what items you have collected. The command is the same as the GET command but with USE instead of GET.");
		Dialogue::print_line("I won't make you do this one but keep it in mind. Sometimes, you will need to USE an item from your TOOL BELT to advance.\nKeep an eye on your sugar level and go get those lolipops! If one jumps out in front of you, you can fight it by licking it, but your sugar level will increase each time you attack. Alternatively, you can run by using MOVE and going somewhere else.\nThat's all!\n\nGOOD LUCK!");
		Dialogue::print("Press any key to start the game!");
		Dialogue::add_pause(200);
		std::cin.get();
		system("CLS");
		reset_room();
	};
};