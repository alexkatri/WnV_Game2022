#include <iostream>
#include "classes.h"
#include <cstdlib>

using namespace std;

/////////////////////////////////////////////////
State::State(Board& b, int x, int y, int w, int v) : board(b), num_of_trees(x), num_of_lakes(y), num_of_werewolves(w), num_of_vampires(v) {};
State::State(Board& b) : board(b), num_of_trees(0), num_of_lakes(0), num_of_werewolves(0), num_of_vampires(0) {};
Board State::get_board() const {
	return board;
}
int State::get_num_of_werewolves() const {
	return num_of_werewolves;
}
int State::get_num_of_vampires() const {
	return num_of_vampires;
}
string State::get_timer() const {
	return timer;
}
void State::set_board(Board B) {
	board = B;
}
void State::set_avatar(Avatar* A) {
	avatar = A;
}
void State::change_timer(string s) {
	timer = s;
}
void State::initialize() {
	srand((unsigned)time(NULL));

	int x;
	int y;
	bool exit = false;
	while (!exit) {
		x = rand() % (board.get_size());
		y = rand() % (board.get_size());
		if (board.at(x, y)->is_empty()) {	// h thesi tou board einai kenh
			Magic_filter* magic_filter = new Magic_filter(x, y);
			board.push(x, y, magic_filter);
			exit = true;
		}
	}

	for (int i = 0; i < num_of_werewolves; i++) {
		bool exit = false;
		while (!exit) {
			x = rand() % (board.get_size());
			y = rand() % (board.get_size());
			if (board.at(x, y)->is_empty()) {	// h thesi tou board einai kenh
				Werewolve* werewolve = new Werewolve(x, y);
				board.push(x, y, werewolve);
				werewolves_vector.push_back(werewolve);
				exit = true;
			}
		}
	}

	for (int i = 0; i < num_of_vampires; i++) {
		bool exit = false;
		while (!exit) {
			x = rand() % (board.get_size());
			y = rand() % (board.get_size());
			if (board.at(x, y)->is_empty()) {	// h thesi tou board einai kenh
				Vampire* vampire = new Vampire(x, y);
				board.push(x, y, vampire);
				vampires_vector.push_back(vampire);
				exit = true;
			}
		}
	}

	for (int i = 0; i < num_of_trees; i++) {
		bool exit = false;
		while (!exit) {
			x = rand() % (board.get_size());
			y = rand() % (board.get_size());
			if (board.at(x, y)->is_empty()) {	// h thesi tou board einai kenh
				Tree* tree = new Tree(x, y);
				board.push(x, y, tree);
				exit = true;
			}
		}
	}

	for (int i = 0; i < num_of_lakes; i++) {
		bool exit = false;
		while (!exit) {
			x = rand() % (board.get_size());
			y = rand() % (board.get_size());
			if (board.at(x, y)->is_empty()) {	// h thesi tou board einai kenh	
				Lake* lake = new Lake(x, y);
				board.push(x, y, lake);
				exit = true;
			}
		}
	}
}