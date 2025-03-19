#include "stuff_handler.h"

bool Batteries_used = false;
bool Plot_discovered = false;

static Item create_item(std::string name, std::string description)
{
	Item item = Item(name, description);
	return item;
}

Item Batteries = create_item(std::string("batteries"), "Four C batteries that should have enough juice to power the lantern for as long as you need.");
Item Lantern = create_item(std::string("camping lantern"), "\"For Use In Emergencies\" feels very appropriate right now. The lantern requires 4 'C' batteries, which are not included currently.");
Item Dentures = create_item(std::string("dentures"), "A set of false teeth that look weak but may be able to give you a little more bite. You can bite more aggressively with these on.");
Item hints = create_item(std::string("hint list"), "A list of steps of your master plan. Can be checked by typing \"Hint\" at any time.");
Item key = create_item(std::string("key"), "A silver key with a green rubber cap to identify it as the garage key. The rubber is worn down where you have picked at it. Why you have a special lock and key for a single room is beyond you, but you weren't the one who designed and built this house.");
Item knife = create_item(std::string("knife"), "The various tools on the utility knife have been worn down. The screwdriver is bent. The corkscrew is fine, but you don't drink wine. The magnifying glass is stuck. The only thing that seems useful is the small knife.\nIt's a little dull from your whittling practice, but your duck carvings are getting much better.");
Item ladder = create_item(std::string("ladder"), "The lolipop sticks surprisingly support your weight without any sign of breaking. You even fashioned convenient places to put your hands.");
Item detector = create_item(std::string("metal detector"), "A relatively small, relatively weak metal detector that should be plenty to find what you might need.");
Item mints = create_item(std::string("mints"), "A handful of spearmint candies. The smell is powerful enough that you can smell them from your hand. You did dig these out from your couch cushions so they are covered in lint and some unidentifiable crumbs.");
Item mouthguard = create_item("mouthguard", "A plastic mouth guard that you found again just recently. You constantly feel it against the roof of your mouth, but it will protect your teeth from the sugar.");
Item shovel = create_item(std::string("shovel"), "A metal shovel with a wooden shaft and a comfortable plastic grip. You haven't used it much since you planted your garden.");
Item tool_belt = create_item("tool belt", "A modified utilty belt prepared to hold any items you find that seem useful, no matter how impratically sized.");
Item bottle = create_item("water bottle", "A tall, large, green water bottle you stored for an emergency like this.");

std::vector<Item> Stuff_Handler::All_items = {};

Item* Stuff_Handler::get_itemptr(const std::string& item_name)
{
	for (Item item : All_items) {
		if (item.Name == item_name) {
			return &item;
		}
	}
	return nullptr;
}

void Stuff_Handler::handle_use_item(const std::string& item_name)
{
	std::string message;
	if (Stuff_Handler::verify_inventory(item_name)) {
		message = "You don't have " + item_name.back() == "s" ? "any " : "a " + item_name + ".";
	}
	else {
		if (item_name == "batteries") {
			if (Stuff_Handler::verify_inventory("camping lantern"))
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
		else if (item_name == "mouthguard") {
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
		else if (item_name == "dentures") {
			message = "You pick at the false teeth. You don't know whose these were, and you hope they've been cleaned at some point...";
		}
		else if (item_name == "camping lantern") {
			if (Batteries_used)
			{
				message = "You click the switch on the lantern, creating a slightly blue glow.";
				Stuff_Handler::remove_item(item_name);
				message += "\n" + Room_Handler::Map.unlock("Basement");
			}
			else
			{
				message = "You click the switch on the lantern, but nothing seems to be happening. The lantern needs batteries.";
			}
		}
		else if (item_name == "key") {
			if (Room_Handler::Map.verify_locked("Garage")) {
				message = "You turn the key in the door lock. This may have been an effective way of keeping anyone who broke into your garage from accessing the rest of the house, but now, it just seems like a huge hassle.";
				message += "\n" + Room_Handler::Map.unlock("Garage");
			}
			else {
				message = "You play with flipping the key in the air and catching it on the rubber end. The garage is already unlocked, so it's more useful this way. Just make sure to put it back on the key hook.";
			}
		}
		else if (item_name == "knife") {
			if (Characters_Handler::get_player().get_experience() < 10) {
				message = "You have all of the tools you need but just aren't able to visualize in your mind how all of this could be used together.\nMaybe with " + std::to_string(10 - Characters_Handler::get_player().get_experience()) + " more sticks the picture might become clearer.";
			}
			else if (Room_Handler::get_current_location() == "Hidden Room" && !(Room_Handler::Map.verify_boss("Hidden Room"))) {
				message = "You flick out your knife and frantically whittle away at the king's candy shell, removing layer after layer of candy coating until your knife is dull and useless.";
				Characters_Handler::attack_boss(25);
			}
			else
			{
				message = "You shave down and cut the sticks into various shapes, removing bits of candy left behind. To your amazement, you can definitely GET a LADDER out of the parts on the CRAFT BENCH now.\nThen again, are you really surprised? You have been practicing very hard recently for something, well not quite exactly like this, but not too dissimilar.";
				Room_Handler::Map.add_get_item("Garage", { "ladder" });
				Room_Handler::Map.remove_use_item("Garage", { "knife" });

			}
		}
		else if (item_name == "ladder") {
			if (Room_Handler::Map.get_room("Attic")) {
				message = "You hook the ends of the ladder into the slots on the attic hatch. After a quick integrity check, you confidently climb into the attic.";
				Room_Handler::Map.remove_use_item("Attic", { "ladder" });
				Stuff_Handler::remove_item("ladder");
				message += "\n" + Room_Handler::Map.unlock("Attic");
			}
			else {
				message = "As impressed as you are by your craftmanship, you decide not to tempt fate and leave the ladder in place.";
			}
		}
		else if (item_name == "metal detector") {
			Room_Handler::Map.add_use_item("Backyard", { "shovel" });
			Dialogue::print_line("You scan pile after pile, in search of something you hope is there. Your resolve weakens as you wonder if there is anything to find. What are the odds of it being metal?\n*BEEP BEEP*");
			Dialogue::add_pause(300);
			message = "Very good, apparently. You note the spot.";
			Room_Handler::Map.remove_use_item("Backyard", { "metal detector" });
		}
		else if (item_name == "mints") {
			if (Room_Handler::get_current_location() == "Hidden Room" && Room_Handler::Map.verify_boss("Hidden Room")) {
				if (Plot_discovered)
				{
					message = "You shove the mints into your mouth, sucking and biting down as they scream and wail at their plan failing.\nThe weird voice in your head hasn't gone away yet, but you're confident that once the mints dissolve and get digested you'll return to normal.\nThe only thing to do is to USE the BUTTON and end this madness.";
					Room_Handler::Map.remove_use_item("Hidden Room", {"mints"});
					Stuff_Handler::remove_item("mints");
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
		else if (item_name == "shovel") {
			if ()
			{
				(Room_Handler::Map.get_room("Backyard")).add_interactable({ "buried switch" });
				message = "You scoop up the loose dirt with ease. It's not long before you uncover a strange metal plate with a SWITCH covered in a plastic case.";
			}
			else if (Room_Handler::get_current_location() == "Hidden Room" && !Room_Handler::Map.verify_boss())
			{
				message = "You unstrap your trusty shovel. With a barbaric shout, you wallop the king, bashing layer after layer from it's shell. You smash until the wooden handle on your shovel cracks and splinters in two.";
				Room_Handler::Map.remove_use_item();
				Characters_Handler::attack_boss(25);
			}
			else
			{
				message = "You think that you could get a good swing out of this, if necessary. You're not sure how the handle will withstand an attack.";
			}
		}
		else if (item_name == "tool belt") {
			Dialogue::print_line("You look at your belt to see what all you've collected.");
			Collections::get_all_inventory();
		}
		else if (item_name == "water bottle") {
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
			if (Room_Handler::get_current_location() == "Hidden Room" && Water_available > 0 && !Room_Handler::Map.verify_boss())
			{
				message = "Knowing this is your last chance to use it, you spray all of your remaining water over the king. The powerful spray wears down his thick outer shell. ";
				Characters_Handler::attack_boss(Water_available);
				Room_Handler::Map.remove_use_item();
			}
		}
	}
	Dialogue::print_line(message);
}

void Stuff_Handler::handle_get_item(std::string name) {
	if (name == "mouthguard") {
		Characters_Handler::get_player().increase_critical_multiplier();
		Dialogue::print_line("You open the case and remove the mouth guard. It looks clean enough, and, without any water to rinse it, you don't have any other options. You pop it into your mouth and smile aggresively, excited to take on more lolipops.");
	}
	else if (name == "dentures") {
		Characters_Handler::get_player().lower_critical_threshold();
		Dialogue::print_line("You grab the false teeth. Are they dentures? What's the difference?");
		if (Stuff_Handler::verify_inventory("mouthguard"))
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
