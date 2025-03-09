#pragma once
#include "input_handler.h"

struct Cheat {

    static void CreateSendAction(string command) { Input_Handler::handle_action(Input_Action(command)); };

    static void GrindXP()
    {
        while (Characters_Handler::player.get_experience() < 9)
        {
            bool combat = true;
            Characters_Handler::spawn_enemy("Pantry");
            while (combat)
            {
                combat = Characters_Handler::attack_enemy(&combat);
            }
        }
    };

	static void play_game_for_me() {
        CreateSendAction("use light switch");
        CreateSendAction("get tool belt");
        CreateSendAction("move kitchen");
        CreateSendAction("get knife");
        CreateSendAction("get water bottle");
        CreateSendAction("use water bowl");
        CreateSendAction("use water bottle");
        Input_Handler::combat = false;
        CreateSendAction("move living room");
        CreateSendAction("get mints");
        CreateSendAction("get key");
        Input_Handler::combat = false;
        CreateSendAction("move guest bedroom");
        CreateSendAction("get guard");
        Input_Handler::combat = false;
        CreateSendAction("move bathroom");
        CreateSendAction("get dentures");
        CreateSendAction("use toilet");
        CreateSendAction("use water bottle");
        Input_Handler::combat = false;
        CreateSendAction("move office");
        CreateSendAction("get batteries");
        Input_Handler::combat = false;
        GrindXP();
        CreateSendAction("move garage");
        CreateSendAction("use key");
        CreateSendAction("use sander");
        while (!(*Collections::get_room(Room_Handler::Current_location)).Boss_defeated && Characters_Handler::player.get_sugar_level() < 100)
        {
            CreateSendAction("lick");
        }
        CreateSendAction("use knife");
        CreateSendAction("get ladder");
        CreateSendAction("move attic");
        CreateSendAction("use ladder");
        CreateSendAction("use home gym");
        while (!(*Collections::get_room(Room_Handler::Current_location)).Boss_defeated && Characters_Handler::player.get_sugar_level() < 100)
        {
            CreateSendAction("lick");
        }
        CreateSendAction("get lantern");
        CreateSendAction("use batteries");
        CreateSendAction("move basement");
        CreateSendAction("use lantern");
        CreateSendAction("use milk crates");
        while (!(*Collections::get_room(Room_Handler::Current_location)).Boss_defeated && Characters_Handler::player.get_sugar_level() < 100)
        {
            CreateSendAction("lick");
        }
        CreateSendAction("get shovel");
        CreateSendAction("get metal detector");
        CreateSendAction("use water main");
        CreateSendAction("move kitchen");
        CreateSendAction("use sink");
        Input_Handler::combat = false;
        CreateSendAction("move bathroom");
        CreateSendAction("use sink");
        Input_Handler::combat = false;
        CreateSendAction("move backyard");
        CreateSendAction("use metal detector");
        CreateSendAction("use shovel");
        CreateSendAction("use switch");
        CreateSendAction("move hidden room");
        CreateSendAction("use knife");
        CreateSendAction("use shovel");
        CreateSendAction("use water bottle");
        while (!(*Collections::get_room(Room_Handler::Current_location)).Boss_defeated && Characters_Handler::player.get_sugar_level() < 100)
        {
            CreateSendAction("lick");
        }
        CreateSendAction("use mints");
        CreateSendAction("use mints");
        CreateSendAction("use button");
    }
};