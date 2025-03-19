#include "dialogue.h"

using namespace std;

std::string opening_monologue = std::string("You awaken to a bright new day as the sunshine pours through your window.\n\"What a beautiful day!\" you think to yourself."
	"\nIt's then that you hear suspicious rustling from the foot of your bed.\nAs you peer over the edge, you see wrappers strewn across your floor."
	"\nYou have always kept a stash of delicious Tootsie pops around,\nbut it seems they have gained sentience and are looking to get their revenge."
	"\nYou have trained for this moment so don't be scared.\nGather the supplies and figure out how your candies have turned so sour."
	"\nIt's time to be a hero...\n\nThe journey of any good hero starts by pushing enter to continue.");

std::string title = std::string("Quest to the Center of a Tootsie Pop\n\n"
	"\nHow many licks does it take to get to the center of a Tootsie Pop?"
	"\nThe world may never know..."
	"\nPress enter to begin!");

void Dialogue::print_line(const std::string& line, int delay) {
	for (char c : line) {
		cout << c;
		this_thread::sleep_for(chrono::milliseconds(delay));
	};
	cout << "\n";
};

void Dialogue::print(const std::string& line, int delay) {
	for (char c : line) {
		cout << c;
		this_thread::sleep_for(chrono::milliseconds(delay));
	};
};

void Dialogue::show_title() { print_line(title); };

void Dialogue::show_opening_monologue() { print_line(opening_monologue); };

void Dialogue::add_pause(int delay) {
	this_thread::sleep_for(chrono::milliseconds(delay));
};

std::string Dialogue::lowercase(const std::string& input) {
	std::string output = "";
	for (int i = 0; i < input.length(); i++) {
		output += tolower(input[i]);
	}
	return output;
}
