#include <string>

class Room {
public:
	std::string Name;
	
	std::string Description;
	
	double encounter_chance;
	
	bool boss_defeated;
	
	enum get_items {};
	
	enum usable_items { 
		tool_belt, 
		water_bottle, 
		guard, 
		dentures, 
		mints,
		batteries };
	
	enum interactables {};

	bool roll_encounter() { return (encounter_chance * (rand() % 101)) > 0.3; };
	
	virtual void unlock();
	
	virtual void defeat_boss();
};