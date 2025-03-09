#pragma once
#include "dialogue.h"
#include <string>

class Interactables {
public:
	std::string Name;
	std::string Description;

	Interactables();
	Interactables(std::string name, std::string description);

	void use_interactable();
	void use_interactable(std::string message);
};