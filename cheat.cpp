#include "cheat.h"

static bool combat = false;

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
	Input_Handler::create_send_action("get tool belt");
	Input_Handler::create_send_action("move kitchen");
	Input_Handler::create_send_action("get knife");
	Input_Handler::create_send_action("get water bottle");
	Input_Handler::create_send_action("use water bowl");
	Input_Handler::create_send_action("use water bottle");
	combat = false;
	Input_Handler::create_send_action("move living room");
	Input_Handler::create_send_action("get mints");
	Input_Handler::create_send_action("get key");
	combat = false;
	Input_Handler::create_send_action("move guest bedroom");
	Input_Handler::create_send_action("get guard");
	combat = false;
	Input_Handler::create_send_action("move bathroom");
	Input_Handler::create_send_action("get dentures");
	Input_Handler::create_send_action("use toilet");
	Input_Handler::create_send_action("use water bottle");
	combat = false;
	Input_Handler::create_send_action("move office");
	Input_Handler::create_send_action("get batteries");
	combat = false;
	GrindXP();
	Input_Handler::create_send_action("move garage");
	Input_Handler::create_send_action("use key");
	Input_Handler::create_send_action("use sander");
	while ((Collections::get_room(Room_Handler::get_current_location()).Boss_defeated != false) && (Characters_Handler::get_player().get_sugar_level() < 100))
	{
		Input_Handler::create_send_action("lick");
	}
	Input_Handler::create_send_action("use knife");
	Input_Handler::create_send_action("get ladder");
	Input_Handler::create_send_action("move attic");
	Input_Handler::create_send_action("use ladder");
	Input_Handler::create_send_action("use home gym");
	while ((Collections::get_room(Room_Handler::get_current_location()).Boss_defeated != false) && (Characters_Handler::get_player().get_sugar_level() < 100))
	{
		Input_Handler::create_send_action("lick");
	}
	Input_Handler::create_send_action("get lantern");
	Input_Handler::create_send_action("use batteries");
	Input_Handler::create_send_action("move basement");
	Input_Handler::create_send_action("use lantern");
	Input_Handler::create_send_action("use milk crates");
	while ((Collections::get_room(Room_Handler::get_current_location()).Boss_defeated != false) && (Characters_Handler::get_player().get_sugar_level() < 100))
	{
		Input_Handler::create_send_action("lick");
	}
	Input_Handler::create_send_action("get shovel");
	Input_Handler::create_send_action("get metal detector");
	Input_Handler::create_send_action("use water main");
	Input_Handler::create_send_action("move kitchen");
	Input_Handler::create_send_action("use sink");
	combat = false;
	Input_Handler::create_send_action("move bathroom");
	Input_Handler::create_send_action("use sink");
	combat = false;
	Input_Handler::create_send_action("move backyard");
	Input_Handler::create_send_action("use metal detector");
	Input_Handler::create_send_action("use shovel");
	Input_Handler::create_send_action("use switch");
	Input_Handler::create_send_action("move hidden room");
	Input_Handler::create_send_action("use knife");
	Input_Handler::create_send_action("use shovel");
	Input_Handler::create_send_action("use water bottle");
	while ((Collections::get_room(Room_Handler::get_current_location()).Boss_defeated != false) && Characters_Handler::get_player().get_sugar_level() < 100)
	{
		Input_Handler::create_send_action("lick");
	}
	Input_Handler::create_send_action("use mints");
	Input_Handler::create_send_action("use mints");
	Input_Handler::create_send_action("use button");
};
