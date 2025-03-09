#pragma once
#include "enemy.cpp"
#include "player.cpp"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Characters_Handler {
	static Player player;

	static void spawn_enemy(const std::string& roomname);

	static bool attack_enemy(bool* combat);

	static bool attack_boss(const std::string& bossname);

	static bool attack_boss(int damage);
};
