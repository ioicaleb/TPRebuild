#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

struct Dialogue {
	/// <summary>
	/// Outputs a line of text with a delay between each character then adds new line
	/// </summary>
	/// <param name="line">Text to output</param>
	/// <param name="delay">Milliseconds between each character</param>
	static void print_line(const std::string& line, int delay = 30);

	/// <summary>
	/// Outputs a line of text with a delay between each character
	/// </summary>
	/// <param name="line">Text to output</param>
	/// <param name="delay">Milliseconds between each character</param>
	static void print(const std::string& line, int delay = 30);

	/// <summary>
	/// Pauses the program for a set amount of time
	/// </summary>
	/// <param name="delay">Milliseconds to delay program</param>
	static void add_pause(int delay);

	/// <summary>
	/// Shows title text
	/// </summary>
	static void show_title();

	/// <summary>
	/// Show opening monologue text
	/// </summary>
	static void show_opening_monologue();

	/// <summary>
	/// Converts string to lowercase characters
	/// </summary>
	/// <param name="string">Text to modify</param>
	/// <returns>Lowercase text</returns>
	static std::string lowercase(const std::string& string);

	static std::string capitalize(const std::string& string);

	/// <summary>
	/// Checks if string begins with a vowel
	/// </summary>
	/// <param name="string">Text to check</param>
	/// <returns>n if true or a space if false</returns>
	static std::string set_article(const std::string& string);
};