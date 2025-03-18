#pragma once
#include "player.cpp"
#include "enemy.cpp"
#include "dialogue.h"
#include "collections.h"
#include "room_handler.h"
#include <string>
#include <time.h>

struct Characters_Handler {
	static void spawn_enemy(const std::string& roomname);

	static bool attack_enemy(bool& combat);

	static void attack_boss();

	static void attack_boss(int damage);

	static Player get_player();
};
