#pragma once
#include "dialogue.h"
#include <string>

struct Interactables {
	std::string Name;
	std::string Description;
	std::string Use_message;

	Interactables() { Name = std::string(""); };
	Interactables(std::string name, std::string description, std::string use_message) {
		Name = name;
		Description = description;
		Use_message = use_message;
	};
};
