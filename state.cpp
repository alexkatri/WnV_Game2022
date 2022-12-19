#include <iostream>
#include "classes.h"
#include <cstdlib>

using namespace std;

/////////////////////////////////////////////////
State::State(Board& b, Avatar* a, int x, int y, int w, int v) : board(b), avatar(a), num_of_trees(x), num_of_lakes(y), num_of_werewolves(w), num_of_vampires(v) {};
State::State(Board& b) : board(b), num_of_trees(0), num_of_lakes(0), num_of_werewolves(0), num_of_vampires(0) {};
Board State::get_board() const {
	return board;
}
Avatar* State::get_avatar() const {
	return avatar;
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
void State::team_heal(char ch) {
	if (ch == 'w' && timer == "night") {
		cout << "Magic filter activated for your team members...\n\n";
		cout << "Health level to be increased for all the " << ch << "'s...\n\n";
		for (Werewolve* ptr : werewolves_vector) {
			ptr->health_increase();
		}
		avatar->decrease_magic_filters();
		cout << "Avatar now has " << avatar->get_num_of_magic_filters() << " magic filters available" << endl << endl;
	}
	else {
		if (ch == 'v' && timer == "day") {
			cout << "Magic filter activated for your team members...\n\n";
			cout << "Health level to be increased for all the " << ch << "'s...\n\n";
			for (Vampire* ptr : vampires_vector) {
				ptr->health_increase();
			}
			avatar->decrease_magic_filters();
			cout << "Avatar now has " << avatar->get_num_of_magic_filters() << " magic filters available" << endl << endl;
		}
	}
}
void State::avatar_move(int direction) {
	Point new_p = Point();
	switch (direction) {
	case 0:
		new_p.x = avatar->get_point().x - 1;
		new_p.y = avatar->get_point().y;
		break;
	case 1:
		new_p.x = avatar->get_point().x + 1;
		new_p.y = avatar->get_point().y;
		break;
	case 2:
		new_p.x = avatar->get_point().x;
		new_p.y = avatar->get_point().y + 1;
		break;
	case 3:
		new_p.x = avatar->get_point().x;
		new_p.y = avatar->get_point().y - 1;
		break;
	}
	if (board.legal_move(avatar, new_p.x, new_p.y)) {
		if (board.at(new_p.x, new_p.y)->get_symbol() == '$') {
			avatar->increase_magic_filters();
		}
	}
	board.move(avatar, direction);
}
void State::state_update() {
	srand((unsigned)time(NULL));
	if (rand() % 2 == 1) {
		for (Werewolve* ptr : werewolves_vector) {
			Point point = ptr->get_point();
			int iterator = 0;
			for (Vampire* enemy : vampires_vector) {
				if (point.near_points(enemy->get_point())) {
					if (ptr->get_power() >= enemy->get_power()) {
						ptr->attack(enemy);
						if (enemy->get_health() <= 0) {
							vampires_vector.erase(vampires_vector.begin() + iterator);
							--num_of_vampires;
							board.kill(enemy->get_point().x, enemy->get_point().y);
						}
					}
					else {
						do {
							board.move(ptr, rand() % 4);
						} while (ptr->get_point().equal(point));
					}
				}
				iterator++;
			}

			if (ptr->move_or_stay()) {
				board.move(ptr, rand() % 4);
			}
		}
	}
	else {
		for (Vampire* ptr : vampires_vector) {
			Point point = ptr->get_point();
			int iterator = 0;
			for (Werewolve* enemy : werewolves_vector) {
				if (point.near_points(enemy->get_point())) {
					if (ptr->get_power() >= enemy->get_power()) {
						ptr->attack(enemy);
						if (enemy->get_health() <= 0) {
							werewolves_vector.erase(werewolves_vector.begin() + iterator);
							--num_of_vampires;
							board.kill(enemy->get_point().x, enemy->get_point().y);
						}
					}
					else {
						do {
							board.move(ptr, rand() % 8);
						} while (ptr->get_point().equal(point));
					}
				}
				iterator++;
			}

			if (ptr->move_or_stay()) {
				board.move(ptr, rand() % 8);
			}
		}
	}
}