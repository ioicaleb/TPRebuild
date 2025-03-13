#pragma once
#include "dialogue.h"
#include <string>

class Interactables {
public:
	std::string Name;
	std::string Description;

	Interactables() { this->Name = std::string(""); };
	Interactables(std::string name, std::string description);

	void use_interactable() const;
	void use_interactable(std::string message);
};
