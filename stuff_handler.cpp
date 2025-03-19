#include "stuff_handler.h"

bool Stuff_Handler::add_item(const std::string& item_name) {
	Item* item = get_itemptr(item_name);
	if (item != nullptr) {
		Inventory.push_back(item);
		return true;
	}
	return false;
};

void Stuff_Handler::remove_item(const std::string& item_name) {
	for (Item* item : Inventory) {
		if (item->Name == item_name) {
			All_items.erase(std::remove(All_items.begin(), All_items.end(), item), All_items.end());
			Inventory.erase(std::remove(Inventory.begin(), Inventory.end(), item), Inventory.end());
		}
	}
};

bool Stuff_Handler::verify_inventory(const std::string& item_name) {
	for (Item* item : Inventory) {
		if (item->Name == item_name) {
			return true;
		}
	}
	return false;
};

void Stuff_Handler::handle_use_switch(const std::string& item_name) {
	if (verify_item(item_name))
	{
		handle_use_item(item_name);
	}
	else if (verify_interact(item_name)) {
		handle_use_interact(item_name);
	}
	else
	{
		Dialogue::print_line("There's no " + item_name + " to use.");
	}
};

void Stuff_Handler::get_all_inventory() {
	for (Item* itemptr : Inventory) {
		Item item = *itemptr;
		if (item.Name != "tool belt") {
			Dialogue::print_line(item.Name);
		}
	}
}
