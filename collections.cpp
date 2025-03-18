#include "collections.h"

using namespace std;

vector<Room> Collections::Rooms = {};

vector<Item> All_items = {};

vector<Item> Inventory = {};

map<string, string> Collections::Valid_inputs = {};
map<string, string>* valid_inputs = (&Collections::Valid_inputs);

vector<Interactables> All_interactables = {};

bool Collections::verify_input(const string& input) {
	for (auto pair : Valid_inputs) {
		if (Dialogue::lowercase(pair.first) == input) {
			return true;
		}
	}
	return false;
};

bool Collections::verify_inventory(const string& name) {
	for (Item& item : Inventory) {
		if (item.Name == name) {
			return true;
		}
	};
	return false;
};

Item Collections::get_item(const string& name) {
	for (Item& item : All_items) {
		if (item.Name == name) {
			return item;
		};
	};
	return Item();
};

Item Collections::get_inventory_item(const string& name) {
	for (Item& item : Inventory) {
		if (item.Name == name) {
			return item;
		};
	};
	return Item();
};

Interactables Collections::get_interactable(const string& name) {
	for (Interactables& item : All_interactables) {
		if (item.Name == name) {
			return item;
		};
	};
	return Interactables();
};

Room Collections::get_room(const string& name) {
	for (Room& room : Rooms) {
		if (Dialogue::lowercase(room.Name) == Dialogue::lowercase(name)) {
			return room;
		};
	};
	return Room();
};

void Collections::remove_item(Item item) {
	Inventory.erase(find(Inventory.begin(), Inventory.end(), item));
};

void Collections::get_all_inventory() {
	if (Inventory.size() > 1) {
		for (Item item : Inventory) {
			if (item.Name != "tool belt") {
				Dialogue::print_line("-" + item.Name);
			}
		}
	}
	else {
		Dialogue::print_line("Just a bunch of empty pockets, holsters, and straps.");
	}
};

bool Collections::add_item(Item item) {
	if (!Collections::verify_inventory(item.Name)) {
		Inventory.push_back(item);
		return true;
	}
	else {
		Dialogue::print_line(format("You already have a {}. CHECK your TOOL BELT.", item.Name));
	}

	return false;
};

void create_map() {
	Room attic = Room(string("Attic"), string("The attic hatch is open but out of reach. You see where you could hook a LADDER if you had one."), 1.0, {}, {});
	attic.add_useable_item("ladder");
	Room backyard = Room(string("Backyard"), string("You step outside for just a moment. The air is temperate and comfortable. Fresh air fills your lungs and reinvigorates you. Underneath it's cover rests your LAWNMOWER, a gift from your grandfather.\nYou see many mounds of dirt from where your yard has been dug up. You didn't dig any of these holes and you're not excited about needing to resod the lawn."), 0.1, {}, { "lawnmower" });
	backyard.add_useable_item("metal detector");
	Room basement = Room(string("Basement"), string("You open the door to the basement and creep down the steps.\nThe basement is pitch black. You can't see your own hands.\nThe light switch clicks uselessly.\n...\nYou need to find a light source to explore further."), 1.0, {}, {});
	basement.add_useable_item("lantern");
	Room bathroom = Room(string("Bathroom"), string("You enter the bathroom, looking to take a break from your lolipop fighting. The modestly sized room fits a SINK with a mirrored MEDICINE CABINET above it, a BATHTUB with your favorite TOWEL hanging on a nearby towel rack, and a porcelain white TOILET."), 0.2, { "dentures" }, { "sink", "bathtub", "towel", "medicine cabinet", "toilet" });
	Room dining = Room(string("Dining Room"), string("The dining room is ornately decorated. The TABLE is set with silver candle holders with long white CANDLES and empty dishes. The CHAIRs are all pushed in curteously."), 0.7, {}, { "candles", "chair", "table" });
	Room garage = Room(string("Garage"), string("You turn the knob to discover that the door is locked. No matter how hard you press against the door, while trying to not break it down (you still have to live here after all), you can't seem to get in. You need to find the KEY."), 1.0, {}, {});
	garage.add_useable_item("key");
	Room guest = Room(string("Guest Bedroom"), string("The guest bedroom is still messy from a recent guest. You really need to get around to cleaning the room up. The BED is untidy and the NIGHTSTAND is dissheveled."), 0.45, { "mouthguard" }, { "bed", "nightstand" });
	Room kitchen = Room(string("Kitchen"), string("The kitchen seems disturbingly still. Your FRIDGE is silent, the SINK is dry as a bone, the CABINET doors are shut tight, and the WATER BOWL is full and still. Everything seems to be neatly in its place.\nExcept for your utility KNIFE, which you seem to have left on the counter near the sink."), 0.8, { "knife", "water bottle" }, { "sink", "cabinet", "fridge", "water bowl" });
	Room living = Room(string("Living Room"), string("The COUCH in your living room looks like lolipops have been jumping on it. The television has been knocked off of the entertainment stand. Your mail is scattered all across your coffee table, which is suspiciously missing your remotes."), 0.6, { "key", "mints" }, { "couch" });
	Room master = Room(string("Master Bedroom"), string("You return to the Master Bedroom. Perhaps, you missed something before. Better safe than sorry. Couldn't hurt to check under the BED, through the DRESSER, or in the CLOSET."), 0.6, { "tool belt" }, { "master bed", "dresser", "closet" });
	Room office = Room(string("Office"), string("Small but cozy, you always feel at peace in your office.Your COMPUTER sits on a mahogany DESK."), 0.4, { "batteries", "hints" }, { "desk", "computer" });
	Room pantry = Room(string("Pantry"), string("As you open the doors to the pantry, you hear rustling all over. There are almost certainly lolipops here. Of course, they're easy to find with a simple SEARCH."), 0.95, {}, {});
	vector<Room> rooms = { attic, backyard, basement, bathroom, dining, garage, guest, kitchen, living, master, office, pantry };
	for (Room room : rooms) {
		Collections::Rooms.push_back(room);
	}
}

void add_all_items() {
	Item batteries = Item(string("batteries"), "Four C batteries that should have enough juice to power the lantern for as long as you need.");
	Item lantern = Item(string("camping lantern"), "\"For Use In Emergencies\" feels very appropriate right now. The lantern requires 4 'C' batteries, which are not included currently.");
	Item dentures = Item(string("dentures"), "A set of false teeth that look weak but may be able to give you a little more bite. You can bite more aggressively with these on.");
	Item hints = Item(string("hint list"), "A list of steps of your master plan. Can be checked by typing \"Hint\" at any time.");
	Item key = Item(string("key"), "A silver key with a green rubber cap to identify it as the garage key. The rubber is worn down where you have picked at it. Why you have a special lock and key for a single room is beyond you, but you weren't the one who designed and built this house.");
	Item knife = Item(string("knife"), "The various tools on the utility knife have been worn down. The screwdriver is bent. The corkscrew is fine, but you don't drink wine. The magnifying glass is stuck. The only thing that seems useful is the small knife.\nIt's a little dull from your whittling practice, but your duck carvings are getting much better.");
	Item ladder = Item(string("ladder"), "The lolipop sticks surprisingly support your weight without any sign of breaking. You even fashioned convenient places to put your hands.");
	Item detector = Item(string("metal detector"), "A relatively small, relatively weak metal detector that should be plenty to find what you might need.");
	Item mints = Item(string("mints"), "A handful of spearmint candies. The smell is powerful enough that you can smell them from your hand. You did dig these out from your couch cushions so they are covered in lint and some unidentifiable crumbs.");
	Item mouthguard = Item("mouthguard", "A plastic mouth guard that you found again just recently. You constantly feel it against the roof of your mouth, but it will protect your teeth from the sugar.");
	Item shovel = Item(string("shovel"), "A metal shovel with a wooden shaft and a comfortable plastic grip. You haven't used it much since you planted your garden.");
	Item tool_belt = Item("tool belt", "A modified utilty belt prepared to hold any items you find that seem useful, no matter how impratically sized.");
	Item bottle = Item("water bottle", "A tall, large, green water bottle you stored for an emergency like this.");
	vector<Item> items = { tool_belt, bottle, mouthguard, dentures, mints, batteries, lantern, hints, key, knife, ladder, detector, shovel };
	for (Item item : items) {
		All_items.push_back(item);
	}
};

void add_all_interactables() {
	Interactables bathtub = Interactables(string("bathtub"), "A large, white bathtub. Your shower liner is getting near needing replaced and your shampoo is a little low.", "You can't seem to get any water from it. There doesn't seem to be anything else that would help you right now.");
	Interactables master_bed = Interactables(string("master bed"), "A cozy king - sized bed.You like your mattress firm and your pillows soft.\nWhen you're done battling lolipops, you should probably change the sheets. Clean, fresh sheets would be a nice way to celebrate.", "");
	Interactables guest_bed = Interactables(string("guest bed"), "A modest full-sized bed. The sheets and cover are a light gray and recently changed after your family recently visited.", "");
	Interactables buried = Interactables(string("buried switch"), "A metal plate with a blinking switch under a plastic plate. Where did this come from and what was it hiding?", "What switch? There's no switch here.");
	Interactables endgame = Interactables(string("button"), "A mysterious button that seems to be the only thing in the room. It's glowing softly. A sign above says \"Win Game.\"", "When it fades, you see that you are back in your yard. The dirt piles are gone. Your tool belt is gone. All of the stuff you collected is gone.");
	Interactables cabinet = Interactables(string("cabinet"), "The handleless doors of the cabinets look like they could use a cleaning, but you're overall proud of your kitchen.", "You open the cabinet doors.");
	Interactables candles = Interactables(string("candles"), "A set of tall candles that line the dining room table. They're in pristine condition as you've never lit them.\nYou always intended to use them for a romantic or meaningful dinner but never think to light them when the occassion seems right.", "You think about removing the candles but don't want only one of the candles to be slightly used. You have a minor panic attack plotting how to make sure that they are both evenly used without wasting them.");
	Interactables chair = Interactables(string("chair"), "An affordable wooden chair with a cushioned seat. Well-maintained and recently reupholstered, you're very proud of your dining room chairs.", "You consider standing on the chairs but decide against it. The cushions are in great shape, and you don't want to risk falling and ending the game prematurely.");
	Interactables car = Interactables(string("car"), "A car of a model that has been discontinued and a make that you're not sure ever existed. It's currently locked and you don't remember where your keys are.\nAll you can tell is that you didn't put them back on the hook. Just as well, running from this fight wouldn't solve anything.", "You still haven't found your car keys. The car continues to be inaccessible.");
	Interactables chest = Interactables(string("chest"), "A dusty, vintage looking chest. It's been locked since you received it from your grandmother.\nYou've tried unlocking it, but it seems stuck. The only way to open it would be to damage it.\nYou've refused to do that, choosing instead to keep it from harm in honor of Gram-Gram.", "You haven't been able to open this chest without damaging it until now, when you continue to be unable to open it. The chest is probably more important than anything inside.");
	Interactables closet = Interactables(string("closet"), "A modest sized closet where you hang your work clothes and fashionable outfits.", "You open the doors to see your nicer shirts and formal wear hanging neatly in a row.");
	Interactables computer = Interactables(string("computer"), "The old girl is just as reliable as the day you got her, which is to say not very.", "You spot a folder of unfinished projects that were started and abandoned. You don't have the time right now. Just definitely don't forget to work on them when things calm down...");
	Interactables couch = Interactables(string("couch"), "A comfortable couch that is a lovely forest green color. The couch remains the centerpiece of your living room design aesthetic,\nbut more importantly, the cushions pull out. A good cleaning seems to be in order.", "You rummage through the couch cushions, pushing aside clumps of dust and indistinguishable crumbs.");
	Interactables bench = Interactables(string("craft bench"), "A sturdy workbench that has almost enough tools to make whatever you need,\nmeaning that whatever you need, you always have almost enough tools to make it.", "You scan the bench for ideas of what to make.");
	Interactables desk = Interactables(string("desk"), "A white wooden desk where you do all of your vaguely defined work.", "You can't find anything else of use and would rather not get back to work on your project just yet.");
	Interactables dresser = Interactables(string("dresser"), "A long mahogany dresser with a mirror on top. You check each drawer but only find neatly folded clothes.\nYou've been on top of your laundry lately, a refreshing change of pace. There's nothing of real use here.", "You straighten some pairs of underwear and feel a little better with the increased sense of order in the world.");
	Interactables fridge = Interactables(string("fridge"), "A large metallic fridge/freezer combo. The power to the fridge seems to be off. You should investigate this later, but it would be better to leave it alone until the power returns.", "Until you can figure out why the fridge has no power, it's better to leave it shut.");
	Interactables furnace = Interactables(string("furnace"), "A decently new furnace. You've never had any problems with it.", "You touch the furnace haphazardly. It's cool to the touch. The weather has been warm and sunny recently, so there's been no need to run the furnace.");
	Interactables gym = Interactables(string("home gym"), "A home workout machine with adjustable weights that you bought cheaply and used briefly. If you think you could lift it, the weights might be able to do some damage.", "Your muscles are sore and exhausted from your adventures so far. It's nice you want to work out more, but now is not the time.");
	Interactables mower = Interactables(string("lawnmower"), "An older push mower you got from your grandfather after he repaired it. It runs reliably but it doesn't have any gas right now. You could siphon from the car but then you wouldn't be able to go get more gas", "You yank on the starter cord but can't seem to get the engine to do anything more than sputter.");
	Interactables light = Interactables(string("light switch"), "While the light may be fine enough for you to see, you can always adjust the text and background to help see better.", "*Click* You flick the lights ");
	Interactables medicine = Interactables(string("medicine cabinet"), "The mirror stands out from the wall. Behind it is your medicine cabinet, which may hold something of use.", "Behind the mirror are three shelves. Most of what's on them is not helpful");
	Interactables crates = Interactables(string("milk crates"), "Plastic crates that were left here by the previous owner. You constantly debate back and forth about getting rid of them but worry they might be useful one day.", "The milk crates don't seem to have much use right now.");
	Interactables stand = Interactables(string("night stand"), "A small cherry nightstand with a reading lamp on top. The bulb has burned out, which you make a note to replace, intending to actually follow through this time.", "You open each drawer but find nothing that could be of any assistance.");
	Interactables sander = Interactables(string("sander"), "A belt sander that looks like it could do some real damage. If the cord wasn't so short, you might be able to really put the hurt on some lolipops.", "The sander doesn't seem to have much use right now.");
	Interactables bathroom_sink = Interactables(string("bathroom sink"), "A small sink with a mirror above it. Your toothbrush sits in a cup next to a mostly empty tube of toothpaste.", "No matter how hard you try, you can't get any water out of the sink.");
	Interactables kitchen_sink = Interactables(string("kitchen sink"), "A single-chambered metal sink that is currently empty. You cleaned all of your dishes the night before.", "No matter how hard you try, you can't get any water out of the sink.");
	Interactables table = Interactables(string("table"), "A long wooden table with candles and clean plates. You left it set mostly for show as you more often than not eat off the coffee table and couch.", "You wouldn't dare so much as approach the table for fear that you might knock your carefully set arrangement and have to recreate it.");
	Interactables toilet = Interactables(string("toilet"), "A small white toilet. You've been thinking about getting a bidet for it but haven't taken the plunge on yet.\nThe bowl has some water in it.", "You lift the seat to see water in the bowl. Jiggling the handle doesn't seem to do anything. You check the tank to see that it is empty.");
	Interactables towel = Interactables(string("towel"), "A solid blue towel that has slightly faded from being washed too many times. You still remember the day you bought it. Though it's color is fading, the feel still can't be beat.", "The towel is still damp and smells slightly. Probably best to not use it until you can wash it.");
	Interactables bowl = Interactables(string("water bowl"), "A small bowl with \"Domino\" across the front. The water dish glistens with fresh water. You don't have any pets which gives you pause but that seems like an issue for another time.", "The bowl seems to be in pristine condition. Where did it come from? How did it get filled with water? You move on without thinking too hard about it.");
	Interactables main = Interactables(string("water main"), "A pipe with a bright yellow handle that controls the flow of water to the entire house. It's currently off.", "Turning the handle off and on doesn't seem to be having any further effect.");
	vector<Interactables> interacts = { light, bathtub, master_bed, guest_bed, buried, endgame, cabinet, candles, chair, car, chest, closet, computer, couch, bench, desk, dresser, fridge,
	furnace, gym, mower, medicine, crates, stand, sander, kitchen_sink, bathroom_sink, table, toilet, towel, bowl, main };
	for (Interactables interact : interacts) {
		All_interactables.push_back(interact);
	}
};

void add_Valid_inputs() {
	(*valid_inputs)[string("Move")] = string("(Room) All done in this room? Move on to the next room, but watch out for potential tootsie pops.");
	(*valid_inputs)[string("Lick")] = string("The only way to get to the center is to erode the candy coating. Get licking!");
	(*valid_inputs)[string("Sugar")] = string("Strategy, eh? Well if you're worried about taking that next lick, confirm your sugar level before going for it.");
	(*valid_inputs)[string("Map")] = string("This house is so big that it's easy to get lost in. Pull out the map to see where to go next.");
	(*valid_inputs)[string("Search")] = string("You may have missed something you can interact with. Take another look around.");
	(*valid_inputs)[string("Check")] = string("(Item) You remember that thing you picked up earlier? It might be useful. Check it out just to be sure.");
	(*valid_inputs)[string("Use")] = string("(Item) Those items in your pack aren't just there to look pretty. Put them to good use");
	(*valid_inputs)[string("Get")] = string("(Item) Your supplies have been scattered. You must recover them. If you come across one, use this to add it to your tool belt.");
	(*valid_inputs)[string("Hint")] = string("In the stress and surprise, you may have forgotten your master plan. That's fine. You can scan your mind for bits of the plan.");
	(*valid_inputs)[string("Help")] = string("It helps to take time to reflect on your options. Help yourself out by stopping for a breather.");
#ifdef _DEBUG
	(*valid_inputs)[string("Gimme")] = string("Shhhh... Debugging is long and hard. Just do it for me.");
#endif
	(*valid_inputs)[string("Quit")] = string("There are no saves, but you can quit out whenever you feel like it.");
};

void Collections::add_hidden_room() {
	Room hidden_room = Room(string("Hidden Room"), string("The spiral staircase stretches on and on, down deeper and deeper below your house. Your feet finally find a landing on a solid concrete floor. A bright light blinds you before your eyes can adjust."), 1.0, {}, {});
	hidden_room.Boss_defeated = false;
	hidden_room.add_useable_item(set<string>{"knife", "shovel"});
	Rooms.push_back(hidden_room);
};

void Collections::reset_collections() {
	create_map();
	add_all_items();
	add_all_interactables();
	Inventory = {};
	add_Valid_inputs();
};
