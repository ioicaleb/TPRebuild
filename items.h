#pragma once
#include "collections.h"
#include <string>

class Items {
public:
	std::string Name;
	std::string Description;

	Items();
	Items(std::string name, std::string description);

	void get_item();

	void use_item();
	void use_item(std::string message);
};
