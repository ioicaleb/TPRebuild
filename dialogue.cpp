#include "dialogue.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

string opening_monologue = string("You awaken to a bright new day as the sunshine pours through your window.\n\"What a beautiful day!\" you think to yourself."
	"\nIt's then that you hear suspicious rustling from the foot of your bed.\nAs you peer over the edge, you see wrappers strewn across your floor."
	"\nYou have always kept a stash of delicious Tootsie pops around,\nbut it seems they have gained sentience and are looking to get their revenge."
	"\nYou have trained for this moment so don't be scared.\nGather the supplies and figure out how your candies have turned so sour."
	"\nIt's time to be a hero...\n\nThe journey of any good hero starts by pushing enter to continue.");

string title = string("Quest to the Center of a Tootsie Pop\n\n"
	"\nHow many licks does it take to get to the center of a Tootsie Pop?"
	"\nThe world may never know..."
	"\nPress enter to begin!");

static void print_line(string line, int delay = 30) {
	for (char c : line) {
		cout << c;
		this_thread::sleep_for(chrono::milliseconds(delay));
	};
	cout << "\n";
};

static void print(string line, int delay = 30) {
	for (char c : line) {
		cout << c;
		this_thread::sleep_for(chrono::milliseconds(delay));
	};
};

void show_title() { print_line(title); };

void show_opening_monologue() { print_line(opening_monologue); };

static void add_pause(int delay) {
	this_thread::sleep_for(chrono::milliseconds(delay));
};

