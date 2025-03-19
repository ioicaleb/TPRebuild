#include "stuff_handler.h"

int Stuff_Handler::Water_available = 0;

bool Toilet_used = false;
bool Towel_used = false;
bool Water_bowl_used = false;
bool Bed_made_master = false;
bool Bed_made_guest = false;
bool Water_on = false;
bool Sink_used_kitchen = false;
bool Sink_used_bathroom = false;
bool Light_on = false;
bool Switch_unburied = false;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

static Interactable create_item(std::string name, std::string description, std::string use_message) {
	Interactable item = Interactable(name, description, use_message);
	return item;
};

Interactable Bathtub = create_item(std::string("bathtub"), "A large, white bathtub. Your shower liner is getting near needing replaced and your shampoo is a little low.", "You can't seem to get any water from it. There doesn't seem to be anything else that would help you right now.");
Interactable Buried_switch = create_item(std::string("buried switch"), "A metal plate with a blinking switch under a plastic plate. Where did this come from and what was it hiding?", "What switch? There's no switch here.");
Interactable Cabinet = create_item(std::string("cabinet"), "The handleless doors of the cabinets look like they could use a cleaning, but you're overall proud of your kitchen.", "You open the cabinet doors.");
Interactable Candles = create_item(std::string("candles"), "A set of tall candles that line the dining room table. They're in pristine condition as you've never lit them.\nYou always intended to use them for a romantic or meaningful dinner but never think to light them when the occassion seems right.", "You think about removing the candles but don't want only one of the candles to be slightly used. You have a minor panic attack plotting how to make sure that they are both evenly used without wasting them.");
Interactable Car = create_item(std::string("car"), "A car of a model that has been discontinued and a make that you're not sure ever existed. It's currently locked and you don't remember where your keys are.\nAll you can tell is that you didn't put them back on the hook. Just as well, running from this fight wouldn't solve anything.", "You still haven't found your car keys. The car continues to be inaccessible.");
Interactable Chair = create_item(std::string("chair"), "An affordable wooden chair with a cushioned seat. Well-maintained and recently reupholstered, you're very proud of your dining room chairs.", "You consider standing on the chairs but decide against it. The cushions are in great shape, and you don't want to risk falling and ending the game prematurely.");
Interactable Chest = create_item(std::string("chest"), "A dusty, vintage looking chest. It's been locked since you received it from your grandmother.\nYou've tried unlocking it, but it seems stuck. The only way to open it would be to damage it.\nYou've refused to do that, choosing instead to keep it from harm in honor of Gram-Gram.", "You haven't been able to open this chest without damaging it until now, when you continue to be unable to open it. The chest is probably more important than anything inside.");
Interactable Closet = create_item(std::string("closet"), "A modest sized closet where you hang your work clothes and fashionable outfits.", "You open the doors to see your nicer shirts and formal wear hanging neatly in a row.");
Interactable Computer = create_item(std::string("computer"), "The old girl is just as reliable as the day you got her, which is to say not very.", "You spot a folder of unfinished projects that were started and abandoned. You don't have the time right now. Just definitely don't forget to work on them when things calm down...");
Interactable Couch = create_item(std::string("couch"), "A comfortable couch that is a lovely forest green color. The couch remains the centerpiece of your living room design aesthetic,\nbut more importantly, the cushions pull out. A good cleaning seems to be in order.", "You rummage through the couch cushions, pushing aside clumps of dust and indistinguishable crumbs.");
Interactable Bench = create_item(std::string("craft bench"), "A sturdy workbench that has almost enough tools to make whatever you need,\nmeaning that whatever you need, you always have almost enough tools to make it.", "You scan the bench for ideas of what to make.");
Interactable Desk = create_item(std::string("desk"), "A white wooden desk where you do all of your vaguely defined work.", "You can't find anything else of use and would rather not get back to work on your project just yet.");
Interactable Dresser = create_item(std::string("dresser"), "A long mahogany dresser with a mirror on top. You check each drawer but only find neatly folded clothes.\nYou've been on top of your laundry lately, a refreshing change of pace. There's nothing of real use here.", "You straighten some pairs of underwear and feel a little better with the increased sense of order in the world.");
Interactable Endgame_button = create_item(std::string("button"), "A mysterious button that seems to be the only thing in the room. It's glowing softly. A sign above says \"Win Game.\"", "When it fades, you see that you are back in your yard. The dirt piles are gone. Your toolbelt is gone. All of the stuff you collected is gone.");
Interactable Fridge = create_item(std::string("fridge"), "A large metallic fridge/freezer combo. The power to the fridge seems to be off. You should investigate this later, but it would be better to leave it alone until the power returns.", "Until you can figure out why the fridge has no power, it's better to leave it shut.");
Interactable Furnace = create_item(std::string("furnace"), "A decently new furnace. You've never had any problems with it.", "You touch the furnace haphazardly. It's cool to the touch. The weather has been warm and sunny recently, so there's been no need to run the furnace.");
Interactable Guest_bed = create_item(std::string("guest bed"), "A modest full-sized bed. The sheets and cover are a light gray and recently changed after your family recently visited.", "");
Interactable Home_gym = create_item(std::string("home gym"), "A home workout machine with adjustable weights that you bought cheaply and used briefly. If you think you could lift it, the weights might be able to do some damage.", "Your muscles are sore and exhausted from your adventures so far. It's nice you want to work out more, but now is not the time.");
Interactable Lawnmower = create_item(std::string("lawnmower"), "An older push mower you got from your grandfather after he repaired it. It runs reliably but it doesn't have any gas right now. You could siphon from the car but then you wouldn't be able to go get more gas", "You yank on the starter cord but can't seem to get the engine to do anything more than sputter.");
Interactable Light_switch = create_item(std::string("light switch"), "While the light may be fine enough for you to see, you can always adjust the text and background to help see better.", "*Click* You flick the lights ");
Interactable Master_bed = create_item(std::string("master bed"), "A cozy king - sized bed.You like your mattress firm and your pillows soft.\nWhen you're done battling lolipops, you should probably change the sheets. Clean, fresh sheets would be a nice way to celebrate.", "");
Interactable Medicine_cabinet = create_item(std::string("medicine cabinet"), "The mirror stands out from the wall. Behind it is your medicine cabinet, which may hold something of use.", "Behind the mirror are three shelves. Most of what's on them is not helpful");
Interactable Milk_crates = create_item(std::string("milk crates"), "Plastic crates that were left here by the previous owner. You constantly debate back and forth about getting rid of them but worry they might be useful one day.", "The milk crates don't seem to have much use right now.");
Interactable Nightstand = create_item(std::string("night stand"), "A small cherry nightstand with a reading lamp on top. The bulb has burned out, which you make a note to replace, intending to actually follow through this time.", "You open each drawer but find nothing that could be of any assistance.");
Interactable Sander = create_item(std::string("sander"), "A belt sander that looks like it could do some real damage. If the cord wasn't so short, you might be able to really put the hurt on some lolipops.", "The sander doesn't seem to have much use right now.");
Interactable Bathroom_sink = create_item(std::string("bathroom sink"), "A small sink with a mirror above it. Your toothbrush sits in a cup next to a mostly empty tube of toothpaste.", "No matter how hard you try, you can't get any water out of the sink.");
Interactable Kitchen_sink = create_item(std::string("kitchen sink"), "A single-chambered metal sink that is currently empty. You cleaned all of your dishes the night before.", "No matter how hard you try, you can't get any water out of the sink.");
Interactable Table = create_item(std::string("table"), "A long wooden table with candles and clean plates. You left it set mostly for show as you more often than not eat off the coffee table and couch.", "You wouldn't dare so much as approach the table for fear that you might knock your carefully set arrangement and have to recreate it.");
Interactable Toilet = create_item(std::string("toilet"), "A small white toilet. You've been thinking about getting a bidet for it but haven't taken the plunge on yet.\nThe bowl has some water in it.", "You lift the seat to see water in the bowl. Jiggling the handle doesn't seem to do anything. You check the tank to see that it is empty.");
Interactable Towel = create_item(std::string("towel"), "A solid blue towel that has slightly faded from being washed too many times. You still remember the day you bought it. Though it's color is fading, the feel still can't be beat.", "The towel is still damp and smells slightly. Probably best to not use it until you can wash it.");
Interactable Water_bowl = create_item(std::string("water bowl"), "A small bowl with \"Domino\" across the front. The water dish glistens with fresh water. You don't have any pets which gives you pause but that seems like an issue for another time.", "The bowl seems to be in pristine condition. Where did it come from? How did it get filled with water? You move on without thinking too hard about it.");
Interactable Water_main = create_item(std::string("water main"), "A pipe with a bright yellow handle that controls the flow of water to the entire house. It's currently off.", "Turning the handle off and on doesn't seem to be having any further effect.");

std::vector<Interactable> Stuff_Handler::All_interactables{ 
	Bathtub, Buried_switch, Cabinet, Candles, Car, Chair, Chest, Closet, Computer, Couch, Bench, Desk, Dresser, Endgame_button, Fridge, Furnace,
	Guest_bed, Home_gym, Lawnmower, Light_switch, Master_bed, Medicine_cabinet, Milk_crates, Nightstand, Sander, Bathroom_sink, Kitchen_sink, Table,
	Toilet, Towel, Water_bowl, Water_main
};

Interactable* Stuff_Handler::get_interactptr(const std::string& item_name) {
	for (Interactable& item : All_interactables) {
		if (item.Name == item_name) {
			return &item;
		}
	}
	return nullptr;
}


void Stuff_Handler::handle_use_interact(const std::string& item_name)
{
	Interactable* itemptr = get_interactptr(item_name);
	Interactable item = (*itemptr);
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
		if (Switch_unburied && Room_Handler::Map.verify_locked("Hidden Room"))
		{
			Room_Handler::Map.add_hidden_room();
			message = "You lift the plastic cover and flick the switch. You hear a loud rumbling noise. Something has changed.";
		}
		else if (!Switch_unburied)
		{
			message = "What switch? There's no switch here.";
		}
		else
		{
			message = "The switch is already on. Turning it off now won't help you in any way.";
		}
	}
	else if (item.Name == "cabinet") {
		message += Stuff_Handler::verify_inventory("water bottle") ? " You see clean pots and pans. You start wondering what to make for dinner before your stomach rumbles. Maybe just a slice of bread to soak up some of the sugar." : " On one shelf is a WATER BOTTLE that looks like it's been cleaned recently.";

	}
	else if (item.Name == "closet") {
		message += Stuff_Handler::verify_inventory("toolbelt") ? "" : " One of the hangers holds all of your belts, including your toolbelt.";
	}
	else if (item.Name == "computer") {
		if (!Stuff_Handler::verify_inventory("hints"))
		{
			message = "You dig through your folders to find your emergency plan. With that printed out, you'll be able to reference your plan whenever you forget it. You hover over the GET HINTS button to send the list to your printer.";
			Stuff_Handler::add_item("hint list");
		}
		else
		{
			message = "You spot a folder of unfinished projects that were started and abandoned. You don't have the time right now. Just definitely don't forget to work on them when things calm down...";
		}
	}
	else if (item.Name == "couch") {
		if (!Stuff_Handler::verify_inventory("key"))
		{
			message += " Your hands brush against something metallic. You see a small silver KEY with a green rubber top, meaning this is the KEY to the GARAGE.";
		}
		if (!Stuff_Handler::verify_inventory("mints"))
		{
			message += " Some small white candies roll out from behind a cushion. Even from here, you can smell that these are MINTS. Might come in handy, somehow.";
		}
	}
	else if (item.Name == "craft bench") {
		if (Stuff_Handler::verify_inventory("ladder"))
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
				if (Stuff_Handler::verify_inventory("knife"))
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
		message = !Stuff_Handler::verify_inventory("batteries") ? "You pull out the drawer and see 4 BATTERIES. They're size C." : "You can't find anything else of use and would rather not get back to work on your project just yet.";

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
		Dialogue::print_line("When it fades, you see that you are back in your yard. The dirt piles are gone. Your toolbelt is gone. All of the stuff you collected is gone.");
		Dialogue::add_pause(500);
		Dialogue::print_line("It's over. Great job!", 40);
		Game_Manager::win_game();
	}
	else if (item.Name == "home gym") {
		if (!Room_Handler::Map.verify_boss("Attic"))
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
		message +=Stuff_Handler::verify_inventory("dentures") ? "." : ", except for the DENTURES.You might be able to do some damage with them.";
	}
	else if (item.Name == "milk crates") {
		if (!Room_Handler::Map.verify_boss("Basement")) {
			Characters_Handler::attack_boss();
			message = "You grab one of the milk crates and vault from one to a stack of two and leap toward the knight. With a thunderous force, you smash into it's thick candy shell, thinning it significantly.";
		}

	}
	else if (item.Name == "night stand") {
		message =Stuff_Handler::verify_inventory("guard") ? "You open each drawer but find nothing that could be of any assistance." : "You open the draw to discover a familiar case. It's your mouthguard that you left behind when this nightstand used to be in your room. It should still fit your mouth.";

	}
	else if (item.Name == "sander") {
		if (!Room_Handler::Map.verify_boss("Garage")) {
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
		if (Stuff_Handler::verify_inventory("water bottle") && !Toilet_used) {
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
		if (Stuff_Handler::verify_inventory("water bottle") && !Water_bowl_used)
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
