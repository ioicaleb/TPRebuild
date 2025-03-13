#pragma once
#include "dialogue.h"


struct Items {
	std::string Name;
	std::string Description;

	Items() { this->Name = std::string(""); };
	Items(std::string name, std::string description);

	void use_item();
};
