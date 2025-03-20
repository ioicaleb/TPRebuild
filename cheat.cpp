#include "cheat.h"

static void GrindXP()
{
	while (Characters_Handler::get_player().get_experience() < 9)
	{
		bool combat = true;
		Characters_Handler::spawn_enemy("Pantry");
		while (combat)
		{
			combat = Characters_Handler::attack_enemy(combat);
		}
	}
};

void Cheat::play_game_for_me() {
	Input_Handler::create_send_action("use light switch");
	Input_Handler::create_send_action("use light switch");
	Input_Handler::create_send_action("get toolbelt");
	Input_Handler::create_send_action("move kitchen");
	Input_Handler::create_send_action("get knife");
	Input_Handler::create_send_action("get water bottle");
	Input_Handler::create_send_action("use water bowl");
	Input_Handler::create_send_action("use water bottle");
	Input_Handler::create_send_action("scatter");
	Input_Handler::create_send_action("move living room");
	Input_Handler::create_send_action("get mints");
	Input_Handler::create_send_action("get key");
	Input_Handler::create_send_action("scatter");
	Input_Handler::create_send_action("move guest bedroom");
	Input_Handler::create_send_action("get mouthguard");
	Input_Handler::create_send_action("scatter");
	Input_Handler::create_send_action("move bathroom");
	Input_Handler::create_send_action("get dentures");
	Input_Handler::create_send_action("use toilet");
	Input_Handler::create_send_action("use water bottle");
	Input_Handler::create_send_action("scatter");
	Input_Handler::create_send_action("move office");
	Input_Handler::create_send_action("get batteries");
	Input_Handler::create_send_action("scatter");
	GrindXP();
	Input_Handler::create_send_action("move garage");
	Input_Handler::create_send_action("use key");
	Input_Handler::create_send_action("use sander");
	while (!Room_Handler::Map.verify_boss("Garage") && (Characters_Handler::get_player().get_sugar_level() < 100))
	{
		Input_Handler::create_send_action("lick");
	}
	Input_Handler::create_send_action("use knife");
	Input_Handler::create_send_action("get ladder");
	Input_Handler::create_send_action("move attic");
	Input_Handler::create_send_action("use ladder");
	Input_Handler::create_send_action("use home gym");
	while (!Room_Handler::Map.verify_boss("Attic") && (Characters_Handler::get_player().get_sugar_level() < 100))
	{
		Input_Handler::create_send_action("lick");
	}
	Input_Handler::create_send_action("get camping lantern");
	Input_Handler::create_send_action("use batteries");
	Input_Handler::create_send_action("move basement");
	Input_Handler::create_send_action("use camping lantern");
	Input_Handler::create_send_action("use milk crates");
	while (!Room_Handler::Map.verify_boss("Basement") && (Characters_Handler::get_player().get_sugar_level() < 100))
	{
		Input_Handler::create_send_action("lick");
	}
	Input_Handler::create_send_action("get shovel");
	Input_Handler::create_send_action("get metal detector");
	Input_Handler::create_send_action("use water main");
	Input_Handler::create_send_action("move kitchen");
	Input_Handler::create_send_action("use sink");
	Input_Handler::create_send_action("scatter");
	Input_Handler::create_send_action("move bathroom");
	Input_Handler::create_send_action("use sink");
	Input_Handler::create_send_action("scatter");
	Input_Handler::create_send_action("move backyard");
	Input_Handler::create_send_action("use metal detector");
	Input_Handler::create_send_action("use shovel");
	Input_Handler::create_send_action("use buried switch");
	Input_Handler::create_send_action("move hidden room");
	Input_Handler::create_send_action("use knife");
	Input_Handler::create_send_action("use shovel");
	Input_Handler::create_send_action("use water bottle");
	while (!Room_Handler::Map.verify_boss("Hidden Room") && Characters_Handler::get_player().get_sugar_level() < 100)
	{
		Input_Handler::create_send_action("lick");
	}
	Input_Handler::create_send_action("use mints");
	Input_Handler::create_send_action("use mints");
	Input_Handler::create_send_action("use button");
};
