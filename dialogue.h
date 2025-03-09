#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

struct Dialogue {
	static void print_line(const std::string& line, int delay = 30);

	static void print(const std::string& line, int delay = 30);

	static void add_pause(int delay);

	static void show_title();

	static void show_opening_monologue();

	static std::string lowercase(const std::string& string);
};