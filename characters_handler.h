#pragma once
#include <time.h>
#include <string>
#include "dialogue.h"
#include "room_handler.h"
#include "player.cpp"

struct Characters_Handler {
	/// <summary>
	/// Spawns an enemy
	/// </summary>
	/// <param name="roomname">Determines if a boss should spawn instead of generic enemy</param>
	static void spawn_enemy(const std::string& roomname);

	/// <summary>
	/// Roll for critical damage to add to base damage and reduces enemy health
	/// Increments player sugar level for every attack and handles if enemy health drops below 0
	/// </summary>
	/// <param name="combat"></param>
	/// <returns></returns>
	static bool attack_enemy(bool& combat);

	/// <summary>
	/// Reduces boss health to 1
	/// </summary>
	static void attack_boss();

	/// <summary>
	/// Reduces King's health by param
	/// </summary>
	/// <param name="damage">Amount of health reduction</param>
	static void attack_boss(int damage);

	/// <summary>
	/// Returns player object
	/// </summary>
	/// <returns></returns>
	static Player get_player();
};
