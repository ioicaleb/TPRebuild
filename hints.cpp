#include "hints.h"

/// <summary>
	/// Checks inventory and displays hint for first missing item from list
	/// </summary>
void Hints::display_hints()
{
	if (Collections::get_item("hints").Name != "")
	{
		Dialogue::print_line("Don't panic. Just stick to the plan.");
		Dialogue::add_pause(800);
		Dialogue::print_line("You forgot the plan?");
		Dialogue::add_pause(400);
		Dialogue::print_line("...");
		Dialogue::add_pause(800);
		Dialogue::print_line("That's fine...");
		Dialogue::add_pause(400);
		Dialogue::print_line("I'm sure you wrote it down somewhere. In fact, I'm sure you typed it up. Go USE the COMPUTER in your OFFICE to see if you saved it.");
	}
	else
	{

		const std::string itemOrder[11] = {"tool belt", "water bottle", "key", "knife", "ladder", "lantern", "batteries", "metal detector", "shovel", "dentures", "mouthguard"};
		int missing = 0;

		for (std::string name : itemOrder)
		{
			if (!Collections::verify_inventory(name)) {
				break;
			}
			++missing;
		}

		if (missing < 11)
		{
			Dialogue::print_line("Get " + itemOrder[missing]);
		}
		else
		{
			Dialogue::print_line("Get some fresh air");
		}
		switch (missing)
		{
		case 0: //tool belt in MB
			Dialogue::print_line("You haven't grabbed your tool belt yet? That's part of the tutorial.");
			Dialogue::add_pause(300);
			Dialogue::print_line("Go back to the MASTER BEDROOM and USE the CLOSET to GET the TOOL BELT.");
			break;
		case 1: //water bottle in kitchen
			Dialogue::print_line("You need something to help you stave off the sugar shakes.\nThere's some water in a few places, but it would be a lot better if you had something with which to drink.\nMaybe in the KITCHEN.");
			break;
		case 2: //key in living room
			Dialogue::print_line("The GARAGE door is locked. As silly as it seemed at the time, it has it's own lock and special KEY. You never remember to put it on the hook when you're done with it.\nMaybe it fell out of your pockets when you were sitting around in the LIVING ROOM.");
			break;
		case 3: //knife in kitchen
			if (Collections::get_room("Garage").Locked)
			{
				Dialogue::print_line("Don't forget to USE the KEY on the GARAGE door.");
			}
			else
			{
				Dialogue::print_line("The GARAGE craft bench has almost everything you need to build a LADDER to the ATTIC. The only thing missing is 10 LOLIPOP STICKS and something to cut them to the right shape.\nLast you remember, you were cutting open packages in the KITCHEN. Seems like a good place to start.");
			}
			break;
		case 4: //ladder in garage
			if (Collections::get_room("Garage").Locked)
			{
				Dialogue::print_line("Don't forget to USE the KEY on the GARAGE door.");
			}
			else if (Characters_Handler::get_player().get_experience() < 10)
			{
				Dialogue::print_line("You need " + std::to_string(10 - Characters_Handler::get_player().get_experience()) + " more sticks. The PANTRY is full of lolipops. Go start some trouble there for some extra sticks.");
			}
			else
			{
				Dialogue::print_line("Now, you have everything you need for the CRAFT BENCH. You should be able to somehow fashion a LADDER to the ATTIC.\nThe CRAFT BENCH in the GARAGE should be able to help you GET your LADDER.");
			}
			break;
		case 5: //lantern in attic
			if (Collections::get_room("Attic").Locked)
			{
				Dialogue::print_line("Don't forget to USE the LADDER to climb to the ATTIC.");
			}
			Dialogue::print_line("The BASEMENT is way too dark to see anything. You need some kind of light source.\nYou finally moved all of that gear from your camping trip to the ATTIC last week. Maybe there's something useful there.");
			break;
		case 6: //batteries in office
			Dialogue::print_line("The lantern won't light itself... Well, not without BATTERIES at least.\nYou have that junk drawer in your OFFICE. Maybe there are BATTERIES in there.");
			break;
		case 7: //metal detector in basement
			if (Collections::get_room("Basement").Locked)
			{
				Dialogue::print_line("Don't forget to USE the LANTERN in the BASEMENT.");
			}
			else
			{
				Dialogue::print_line("The BACKYARD has been dug up with several spots of freshly turned dirt. It would take forever to check each one.\nMaybe your METAL DETECTOR you keep in the BASEMENT can check them faster.");
			}
			break;
		case 8: //shovel in garage
			if (Collections::get_room("Backyard").Usable_items.find("shovel") != Collections::get_room("Backyard").Usable_items.end())
			{
				Dialogue::print_line("You've found something in the BACKYARD but you can't dig it up with your hands.\nYour SHOVEL is normally in the GARAGE but you had to move it to create space for a personal project. You think it's in the BASEMENT now.");
			}
			else
			{
				Dialogue::print_line("You can't check every pile of dirt. USE the METAL DETECTOR instead.");
			}
			break;
		case 9: //dentures in bathroom
			Dialogue::print_line("You have all of the essentials but a little help wouldn't hurt. You think that something to give you a little more bite would be amazing.\nDid you check the BATHROOM yet? You always seem to forget you even have a MEDICINE CABINET.");
			break;
		case 10: //guard in guest bedroom
			Dialogue::print_line("You have all of the essentials but a little help wouldn't hurt. You can already feel all of the sugar dissolving your teeth. They could use some protection.\nDid you check the GUEST BEDROOM yet? You recently had company. Maybe they left something worthwhile behind.");
			break;
		default: //got all items except maybe mints
			if (Collections::get_room("Hidden Room").Name != "")
			{
				Dialogue::print_line("The SWITCH must have changed something! Check the MAP to see if there's anything new that wasn't there before!");
			}
			else
			{
				Dialogue::print_line("You have everything you need. The lolipops' base must be nearby.\nMaybe a breath of fresh air will help you think clearly.");
			}
			break;
		}
	}
};
