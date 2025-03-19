#pragma once
#include <string>

struct Interactable {
	std::string Name;
	std::string Description;
	std::string Use_message;

	Interactable() { Name = std::string(""); };
	Interactable(std::string name, std::string description, std::string use_message);
};