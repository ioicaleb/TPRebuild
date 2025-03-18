#include "item_handler.h"

bool Batteries_used = false;
bool Bed_made_master = false;
bool Bed_made_guest = false;
bool Water_on = false;
bool Sink_used_kitchen = false;
bool Sink_used_bathroom = false;
bool Plot_discovered = false;
bool Light_on = false;
int Water_available = 0;
bool Toilet_used = false;
bool Towel_used = false;
bool Water_bowl_used = false;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void Item_Handler::handle_use_item(Item item)
{
	std::string message;
	if (!Collections::verify_inventory(item.Name)) {
		message = "You don't have " + item.Name.back() == "s" ? "any " : "a " + item.Name + ".";
	}
	else {
		if (item.Name == "batteries") {
			if (!Collections::verify_inventory("camping lantern"))
			{
				message = "You roll the batteries in your hand. These could come in handy if you find something that could use them.";
			}
			else if (!Batteries_used)
			{
				Batteries_used = true;
				message = "You remove the pack to the lantern and insert the batteries. You test the lantern to see that it does turn on now. To preserve batteries, you switch the lantern back off.";
			}
			else
			{
				message = "You check the batteries in the lantern. They seem to be fine, so you shouldn't mess with them right now.";
			}
		}
		else if (item.Name == "mouthguard") {
			srand(time(NULL));
			int message_rand = rand() % 2;
			switch (message_rand)
			{
			case 0:
				message = "You dislodge the guard with your tongue and chew gently on the rubber. It doesn't do much but seems to make you feel a little better.";
				break;
			case 1:
				message = "You reach in and adjust the guard in your mouth, relieving some oral discomfort.";
				break;
			default:
				message = "ERROR! RANDOM FAILURE OCCURRED! Or you messed with my code. Don't do that. I worked hard on this.";
				break;
			};
		}
		else if (item.Name == "dentures") {
			message = "You pick at the false teeth. You don't know whose these were, and you hope they've been cleaned at some point...";
		}
		else if (item.Name == "camping lantern") {
			if (Batteries_used)
			{
				message = "You click the switch on the lantern, creating a slightly blue glow.";
				Collections::remove_item(item);
				message += "\n" + Room_Handler::unlock();
			}
			else
			{
				message = "You click the switch on the lantern, but nothing seems to be happening. The lantern needs batteries.";
			}
		}
		else if (item.Name == "key") {
			if (Collections::get_room("Garage").Locked) {
				message = "You turn the key in the door lock. This may have been an effective way of keeping anyone who broke into your garage from accessing the rest of the house, but now, it just seems like a huge hassle.";
				message += "\n" + Room_Handler::unlock();
			}
			else {
				message = "You play with flipping the key in the air and catching it on the rubber end. The garage is already unlocked, so it's more useful this way. Just make sure to put it back on the key hook.";
			}
		}
		else if (item.Name == "knife") {
			if (Characters_Handler::get_player().get_experience() < 10) {
				message = "You have all of the tools you need but just aren't able to visualize in your mind how all of this could be used together.\nMaybe with " + std::to_string(10 - Characters_Handler::get_player().get_experience()) + " more sticks the picture might become clearer.";
			}
			else if (Room_Handler::get_current_location() == "Hidden Room" && !Collections::get_room(Room_Handler::get_current_location()).Boss_defeated) {
				message = "You flick out your knife and frantically whittle away at the king's candy shell, removing layer after layer of candy coating until your knife is dull and useless.";
				Characters_Handler::attack_boss(25);
			}
			else
			{
				message = "You shave down and cut the sticks into various shapes, removing bits of candy left behind. To your amazement, you can definitely GET a LADDER out of the parts on the CRAFT BENCH now.\nThen again, are you really surprised? You have been practicing very hard recently for something, well not quite exactly like this, but not too dissimilar.";
				Collections::get_room("Garage").Get_items.insert("ladder");
				Collections::get_room("Garage").remove_useable_item("knife");

			}
		}
		else if (item.Name == "ladder") {
			if (Collections::get_room("attic").Locked) {
				message = "You hook the ends of the ladder into the slots on the attic hatch. After a quick integrity check, you confidently climb into the attic.";
				Collections::remove_item(item);
				Collections::get_room("attic").remove_useable_item(item.Name);
				message += "\n" + Room_Handler::unlock();
			}
			else {
				message = "As impressed as you are by your craftmanship, you decide not to tempt fate and leave the ladder in place.";
			}
		}
		else if (item.Name == "metal detector") {
			Collections::get_room("Backyard").Usable_items.insert("shovel");
			Dialogue::print_line("You scan pile after pile, in search of something you hope is there. Your resolve weakens as you wonder if there is anything to find. What are the odds of it being metal?\n*BEEP BEEP*");
			Dialogue::add_pause(300);
			message = "Very good, apparently. You note the spot.";
			Collections::remove_item(item);
		}
		else if (item.Name == "mints") {
			if (Room_Handler::get_current_location() == "Hidden Room" && Collections::get_room(Room_Handler::get_current_location()).Boss_defeated) {
				if (Plot_discovered)
				{
					message = "You shove the mints into your mouth, sucking and biting down as they scream and wail at their plan failing.\nThe weird voice in your head hasn't gone away yet, but you're confident that once the mints dissolve and get digested you'll return to normal.\nThe only thing to do is to USE the BUTTON and end this madness.";
					Collections::remove_item(item);
				}
				else
				{
					Dialogue::print_line("You pull out the mints to hear them chuckling maniacly. It all makes sense now.");
					Dialogue::add_pause(200);
					Dialogue::print_line("The lolipops coming to life.");
					Dialogue::add_pause(200);
					Dialogue::print_line("Your stuff being scattered everywhere.");
					Dialogue::add_pause(200);
					Dialogue::print_line("The weird voice in your head directing you to exactly where you need to go.");
					Dialogue::add_pause(200);
					Dialogue::print_line("It was the mints.");
					Dialogue::add_pause(200);
					Dialogue::print_line("They've been trapped in those cushions for too long, neglected and refreshing. They've designed this whole lolipop assault to eliminate their enemies and lead you to find them.");
					Dialogue::add_pause(200);
					Dialogue::print_line("\"You should USE the BUTTON,\" they tell you. \"Then, we will be free to carry out the final phase of our plan!\"\nThe mints take turns explaining their scheme, but you can barely understand it between the other mints' crazed laughter.\nYou can push the button and admit your defeat at the hands of these mints...");
					Dialogue::add_pause(400);
					message = "Or you can teach these mints a lesson they won't soon forget.";
					Plot_discovered = true;
				}
			}
			else
			{
				message = "You think about popping one or two of these bad boys into the old car crusher but can't help but wonder if that long hair is yours. It's not the same color as yours. Is it even human? What else with hair that long has been sitting on your couch? Better to just say no to these mints. Maybe once you've defeated the lolipops, you can have one as a celebratory snack.";
			}
		}
		else if (item.Name == "shovel") {
			if (!Collections::get_room("Backyard").verify_item("switch"))
			{
				Collections::get_room("Backyard").add_interactable({ "buried switch" });
				message = "You scoop up the loose dirt with ease. It's not long before you uncover a strange metal plate with a SWITCH covered in a plastic case.";
			}
			else if (Room_Handler::get_current_location() == "Hidden Room" && !Collections::get_room(Room_Handler::get_current_location()).Boss_defeated)
			{
				message = "You unstrap your trusty shovel. With a barbaric shout, you wallop the king, bashing layer after layer from it's shell. You smash until the wooden handle on your shovel cracks and splinters in two.";
				Collections::remove_item(item);
				Characters_Handler::attack_boss(25);
			}
			else
			{
				message = "You think that you could get a good swing out of this, if necessary. You're not sure how the handle will withstand an attack.";
			}
		}
		else if (item.Name == "tool belt") {
			Dialogue::print_line("You look at your belt to see what all you've collected.");
			Collections::get_all_inventory();
		}
		else if (item.Name == "water bottle") {
			if (Water_available > 0)
			{
				int sugar = Characters_Handler::get_player().get_sugar_level();
				if (sugar > 0)
				{
					if (Water_available > sugar)
					{
						Water_available -= sugar;
						sugar = 0;
					}
					else
					{
						sugar -= Water_available;
						Water_available = 0;
					}
					Characters_Handler::get_player().set_sugar(sugar);
					Dialogue::print_line("Your hands shake from the sugar as you press the bottle to your lips. With a heave, you throw back your head as the water rushes down your throat.\nYou feel the water absorbing the sugar and easing your shakes. You're not sure if that's how it works, but this has been a slightly unorthodox day already.");
					Dialogue::print_line(sugar > 0 ? "Your sugar level is now {sugar}%." : "You're now feeling sugar-free.");
					message = (Water_available > 0 ? "The bottle still has some water left, about " + std::to_string(Water_available) + "%." : "The bottle is now empty.");
				}
				else
				{
					message = "Hydration is important but you don't need to reduce your sugar level, a real and scientific biological metric, so you decide to wait on chugging your dubiously obtained water.";
				}
			}
			else
			{
				message = "The bottle is empty. No matter how hard you try, you can't get so much as a drop.";
			}
			if (Room_Handler::get_current_location() == "Hidden Room" && Water_available > 0 && !Collections::get_room(Room_Handler::get_current_location()).Boss_defeated)
			{
				message = "Knowing this is your last chance to use it, you spray all of your remaining water over the king. The powerful spray wears down his thick outer shell. ";
				Characters_Handler::attack_boss(Water_available);
				Collections::remove_item(item);
			}
		}
	}
	Dialogue::print_line(message);
}

void Item_Handler::handle_get_item(std::string name) {
	if (name == "mouthguard") {
		Characters_Handler::get_player().increase_critical_multiplier();
		Dialogue::print_line("You open the case and remove the mouth guard. It looks clean enough, and, without any water to rinse it, you don't have any other options. You pop it into your mouth and smile aggresively, excited to take on more lolipops.");
	}
	else if (name == "dentures") {
		Characters_Handler::get_player().lower_critical_threshold();
		Dialogue::print_line("You grab the false teeth. Are they dentures? What's the difference?");
		if (Collections::verify_inventory("mouthguard"))
		{
			Dialogue::print_line("You pop out your mouth guard while considering that maybe there isn't a difference. Maybe it has to do with what they're made of?\n");
		}
		Dialogue::print_line("You're so distracted that you put them over your teeth without thinking about the fact that you don't own any false teeth. Too late now.");
	}
	else if (name == "ladder") {
		Dialogue::print_line("You assemble the ladder and lift it proudly. Strangely, there is a spot on your tool belt to secure the ladder. Convenient.");
		Characters_Handler::get_player().remove_exp();
	}
	else if (name == "tool belt") {
		Dialogue::print_line("You strap your tool belt around your waist and adjust the size to acccount for your recent weight loss.");
		Dialogue::add_pause(200);
		Dialogue::print_line("You look great.");
		Dialogue::add_pause(100);
		Dialogue::print_line("You feel great.");
	}
};

void Item_Handler::handle_use_item(Interactables item)
{
	std::string message = item.Use_message;
	if (item.Name == "master bed") {
		if (Bed_made_master)
		{
			message = "Tightly made and neat as can be. You straighten the pillows slightly. You just can't quite get them right.";
		}
		else
		{
			message = "Embarassed at the sight of the unmade bed, you quickly tidy the sheets and covers. The pillows are placed meticulously, though you're not quite happy with the layout.";
			Bed_made_master = true;
		}
	}
	else if (item.Name == "guest bed") {
		if (Bed_made_guest)
		{
			message = "Tightly made and neat as can be. You straighten the pillows slightly. You just can't quite get them right.";
		}
		else
		{
			message = "Embarassed at the sight of the unmade bed, you quickly tidy the sheets and covers. The pillows are placed meticulously, though you're not quite happy with the layout.";
			Bed_made_guest = true;
		}

	}
	else if (item.Name == "buried switch") {
		Room backyard = Collections::get_room("Backyard");
		if (backyard.verify_item("backyard") && Collections::get_room("Hidden Room").Name == "")
		{
			Collections::add_hidden_room();
			message = "You lift the plastic cover and flick the switch. You hear a loud rumbling noise. Something has changed.";
		}
		else if (!backyard.verify_item("buried switch"))
		{
			message = "What switch? There's no switch here.";
		}
		else
		{
			message = "The switch is already on. Turning it off now won't help you in any way.";
		}
	}
	else if (item.Name == "cabinet") {
		message += Collections::verify_inventory("water bottle") ? " You see clean pots and pans. You start wondering what to make for dinner before your stomach rumbles. Maybe just a slice of bread to soak up some of the sugar." : " On one shelf is a WATER BOTTLE that looks like it's been cleaned recently.";

	}
	else if (item.Name == "closet") {
		message += Collections::verify_inventory("tool belt") ? "" : " One of the hangers holds all of your belts, including your TOOL BELT.";
	}
	else if (item.Name == "computer") {
		if (!Collections::verify_inventory("hints"))
		{
			message = "You dig through your folders to find your emergency plan. With that printed out, you'll be able to reference your plan whenever you forget it. You hover over the GET HINTS button to send the list to your printer.";
			Collections::add_item(Collections::get_item("hint list"));
		}
		else
		{
			message = "You spot a folder of unfinished projects that were started and abandoned. You don't have the time right now. Just definitely don't forget to work on them when things calm down...";
		}
	}
	else if (item.Name == "couch") {
		if (!Collections::verify_inventory("key"))
		{
			message += " Your hands brush against something metallic. You see a small silver KEY with a green rubber top, meaning this is the KEY to the GARAGE.";
		}
		if (!Collections::verify_inventory("mints"))
		{
			message += " Some small white candies roll out from behind a cushion. Even from here, you can smell that these are MINTS. Might come in handy, somehow.";
		}
	}
	else if (item.Name == "craft bench") {
		if (Collections::verify_inventory("ladder"))
		{
			Dialogue::print_line("Nothing comes to mind based on what's scattered across the bench.");
		}
		else
		{
			if (Characters_Handler::get_player().get_experience() < 10)
			{
				Dialogue::print_line("You can build a LADDER to reach the ATTIC. Except, you don't seem to have anything you could use to build it with...");
				Dialogue::add_pause(200);
				Dialogue::print_line("The LOLIPOP STICKS! They would be perfect! You need at least 10 though. That means you need " + std::to_string(10 - Characters_Handler::get_player().get_experience()) + " more sticks.");
			}
			else
			{
				Dialogue::print_line("You can build a LADDER to reach the ATTIC. You believe that the lolipop sticks can handle your weight with some modifications.");
				if (Collections::verify_inventory("knife"))
				{
					Dialogue::print_line("Luckily, you have your utility KNIFE that you can USE to modify the sticks.");
				}
				else
				{
					Dialogue::print_line("Unfortunately, your bench is missing something to cut the sticks");
				}
			}
		}

	}
	else if (item.Name == "desk") {
		message = !Collections::verify_inventory("batteries") ? "You pull out the drawer and see 4 BATTERIES. They're size C." : "You can't find anything else of use and would rather not get back to work on your project just yet.";

	}
	else if (item.Name == "button") {
		Dialogue::add_pause(800);
		if (!Light_on) {
			SetConsoleTextAttribute(hConsole, 107 | 30);
			system("CLS");
			Dialogue::add_pause(750);
			Dialogue::print_line("Everything goes white for a few seconds.");
			Dialogue::add_pause(750);
			SetConsoleTextAttribute(hConsole, 40 | 97);
		}
		else {
			SetConsoleTextAttribute(hConsole, 40 | 97);
			system("CLS");
			Dialogue::add_pause(750);
			Dialogue::print_line("Everything goes black for a few seconds.");
			Dialogue::add_pause(750);
			SetConsoleTextAttribute(hConsole, 107 | 30);
		}
		system("CLS");
		Dialogue::print_line("When it fades, you see that you are back in your yard. The dirt piles are gone. Your tool belt is gone. All of the stuff you collected is gone.");
		Dialogue::add_pause(500);
		Dialogue::print_line("It's over. Great job!", 40);
		Game_Manager::win_game();
	}
	else if (item.Name == "home gym") {
		if (!Collections::get_room(Room_Handler::get_current_location()).Boss_defeated)
		{
			Characters_Handler::attack_boss();
			message = "You grab the knight and lift as much weight as you can manage. You force the knight between the weights and ignore all of your gym etiquette, smashing the knight to pieces. One more lick ought to reach the core.";
		}
	}
	else if (item.Name == "light switch") {
		if (Light_on) {
			SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		}
		else {
			SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
		}
		system("CLS");
		message += Light_on ? "off." : "on.";
		Light_on = !Light_on;
	}
	else if (item.Name == "medicine cabinet") {
		message += Collections::verify_inventory("dentures") ? "." : ", except for the DENTURES.You might be able to do some damage with them.";
	}
	else if (item.Name == "milk crates") {
		if (!Collections::get_room(Room_Handler::get_current_location()).Boss_defeated) {
			Characters_Handler::attack_boss();
			message = "You grab one of the milk crates and vault from one to a stack of two and leap toward the knight. With a thunderous force, you smash into it's thick candy shell, thinning it significantly.";
		}

	}
	else if (item.Name == "night stand") {
		message = Collections::verify_inventory("guard") ? "You open each drawer but find nothing that could be of any assistance." : "You open the draw to discover a familiar case. It's your mouth GUARD that you left behind when this nightstand used to be in your room. It should still fit your mouth.";

	}
	else if (item.Name == "sander") {
		if (!Collections::get_room(Room_Handler::get_current_location()).Boss_defeated) {
			Characters_Handler::attack_boss();
			message = "You grab the sander and grind the bishop down to a thin shell. One more lick ought to reach the core.";
		}
	}
	else if (item.Name == "bathroom sink") {
		if (Water_on && !Sink_used_bathroom) {
			Water_available += 50;
			message = "You're able to get a little bit of water out of the sink.";
			Sink_used_bathroom = true;
		}
		else {
			message = "No matter how hard you try, you can't get any water out of the sink.";
		}
	}
	else if (item.Name == "kitchen sink") {
		if (Water_on && !Sink_used_kitchen) {
			Water_available += 50;
			message = "You're able to get a little bit of water out of the sink.";
			Sink_used_kitchen = true;
		}
		else {
			message = "No matter how hard you try, you can't get any water out of the sink.";
		}
	}
	else if (item.Name == "toilet") {
		if (Collections::verify_inventory("water bottle") && !Toilet_used) {
			Water_available += 50;
			Dialogue::print_line("You kneel down and inspect the bowl intensely. Desperate times...");
			Dialogue::add_pause(300);
			message = "You decide that you cleaned it recently enough and scoop up as much water as you can manage.";
		}
		else if (Toilet_used)
		{
			Dialogue::print_line("The bowl doesn't have enough water in it...");
			Dialogue::add_pause(200);
			Dialogue::print_line("Unless you're willing to shove your head in and lick the drain...");
			Dialogue::add_pause(800);
			Dialogue::print_line("You're not are you?");
			Dialogue::add_pause(400);
			message = "You know what, I just decided you're not. Don't think about it anymore.";
		}
	}
	else if (item.Name == "towel") {
		if (!Towel_used)
		{
			message = "You use the towel to wipe off your accumulated sweat. It's been rough going and taking a break to towel off has reinvigorated you.";
			Towel_used = true;
			item.Description += "The towel is slightly damp from your sweat.";
		}
	}
	else if (item.Name == "water bowl") {
		if (Collections::verify_inventory("water bottle") && !Water_bowl_used)
		{
			Water_available += 50;
			Dialogue::print_line("You kneel down and inspect the water briefly. Desperate times...");
			Dialogue::add_pause(300);
			message = "You gently pour as much of the water as you can into your water bottle.";
		}
		else
		{
			message = "The bowl seems to be in pristine condition. Where did it come from? How did it get filled with water? You move on without thinking too hard about it.";
		}
	}
	else if (item.Name == "water main") {
		if (!Water_on)
		{
			Water_on = true;
			message = "You turn the handle, which results in the pipes gently rumbling. You can hear a short burst of water running through the pipes.\nThe pipes quickly go quiet. It seems there wasn't much water left.";

		}
	}
	Dialogue::print_line(message);
};
