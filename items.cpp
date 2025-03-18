#pragma once
#include "dialogue.h"

struct Item {
	bool operator==(const Item& rhs) const {
		return this->Name == rhs.Name;
	}

	std::string Name;
	std::string Description;

	Item() { this->Name = std::string(""); };
	Item(std::string name, std::string description) {
		this->Name = name;
		this->Description = description;
	};
};
