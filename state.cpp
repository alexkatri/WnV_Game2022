#include <iostream>
#include "classes.h"
#include <cstdlib>
#include <thread>

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
void State::state_update(int num_of_players) {
	/*for (Werewolve* ptr : werewolves_vector) {
		if (ptr->move_or_stay()) {
			board.move(ptr, rand() % 4);
		}
	}
	for (Vampire* ptr : vampires_vector) {
		if (ptr->move_or_stay()) {
			board.move(ptr, rand() % 8);
		}
	}*/
	
	for (int i = 0; i < num_of_players; i++) {
		if (werewolves_vector[i]->get_health() == 0) {
			Point c = werewolves_vector[i]->get_point();
			board.set_ground(c);
			//if (werewolves_vector[i]->get_symbol() == 'w') {
				werewolves_vector[i]->set_symbol('.');
				--num_of_werewolves;
				//board.at(c.x, c.y)->set_empty(true);
			//}
		}
		if (werewolves_vector[i]->get_health() > 0 && rand() % 2) {		// rand() % 2 -> 1/move, 0/stay
			board.move(werewolves_vector[i], rand() % 4);
		}
		if (vampires_vector[i]->get_health() == 0) {
			Point c = vampires_vector[i]->get_point();
			board.set_ground(c);
			//if (vampires_vector[i]->get_symbol() == 'v') {
				vampires_vector[i]->set_symbol('.');
				--num_of_vampires;
				//board.at(c.x, c.y)->set_empty(true);
			//}
		}
		if (vampires_vector[i]->get_health() > 0 && rand() % 2) {
			board.move(vampires_vector[i], rand() % 8);
		}
	}
}
//void State::delete_players(int num_of_players) {
//	for (int i = 0; i < num_of_players; i++) {
//		if (werewolves_vector[i]->get_health() == 0) {
//			Point c = werewolves_vector[i]->get_point();
//			//board.set_ground(c);
//			if (werewolves_vector[i]->get_symbol() == 'w') {
//				werewolves_vector[i]->set_symbol('.');
//				--num_of_werewolves;
//				board.at(c.x, c.y)->set_empty(true);
//			}
//		}
//		if (vampires_vector[i]->get_health() == 0) {
//			Point c = vampires_vector[i]->get_point();
//			//board.set_ground(c);
//			if (vampires_vector[i]->get_symbol() == 'v') {
//				vampires_vector[i]->set_symbol('.');
//				--num_of_vampires;
//				board.at(c.x, c.y)->set_empty(true);
//			}
//		}
//	}
//}


void State::scan_area(int i) {
	if (werewolves_vector[i]->get_symbol() == 'w') {
		area_check(werewolves_vector[i]);
	}
	if (vampires_vector[i]->get_symbol() == 'v') {
		area_check(vampires_vector[i]);
	}
}

void State::area_check(Player* player) {
	Point area;													// location to check
	for (int i = 0; i < 8; i++) {
		area = set_destination(player, i);
		if (board.check_coordinates(area)) {
			if (board.other_player(area)) {
				if (board.enemy_or_ally(area, player)) {
					Player* enemy = get_player(area, board.at(area.x, area.y)->get_symbol());
					player->attack_enemy(player, enemy);					// doesn't always attack enemy
				}
				else {
					Player* ally = get_player(area, board.at(area.x, area.y)->get_symbol());
					player->heal_ally(player, ally);							// doesn't necessarily heal ally
				}
			}

		}
	}
}

Player* State::get_player(Point p, char ch) {
	if (ch == 'w') {
		for (int i = 0; i < num_of_werewolves; ++i) {
			Point temp = werewolves_vector[i]->get_point();
			if (is_equal(temp, p)) {
				return werewolves_vector[i];
			}
		}
	}
	else if (ch == 'v') {
		for (int i = 0; i < num_of_vampires; ++i) {
			Point temp = vampires_vector[i]->get_point();
			if (is_equal(temp, p)) {
				return vampires_vector[i];
			}
		}
	}
}

Point State::set_destination(Player* p, int direction) {
	Point new_p = Point();
	switch (direction) {
	case 0:												// UP
		new_p.x = p->get_point().x - 1;
		new_p.y = p->get_point().y;
		break;
	case 1:												// DOWN
		new_p.x = p->get_point().x + 1;
		new_p.y = p->get_point().y;
		break;
	case 2:												// RIGHT
		new_p.x = p->get_point().x;
		new_p.y = p->get_point().y + 1;
		break;
	case 3:												// LEFT
		new_p.x = p->get_point().x;
		new_p.y = p->get_point().y - 1;
		break;
	case 4:												// NE
		new_p.x = p->get_point().x - 1;
		new_p.y = p->get_point().y + 1;
		break;
	case 5:												// NW
		new_p.x = p->get_point().x - 1;
		new_p.y = p->get_point().y - 1;
		break;
	case 6:												// SE
		new_p.x = p->get_point().x + 1;
		new_p.y = p->get_point().y + 1;
		break;
	case 7:												// SW
		new_p.x = p->get_point().x + 1;
		new_p.y = p->get_point().y - 1;
		break;
	}
	return new_p;
}

//bool State::enemy_or_ally(Point& p, Element* element) {
//	char ally, enemy;
//	if (element->get_symbol() == 'w') {
//		ally = 'w';
//		enemy = 'v';
//	}
//	else if (element->get_symbol() == 'v') {
//		ally = 'v';
//		enemy = 'w';
//	}
//	if (board.at(p.x, p.y)->get_symbol() == ally) {
//		return 0;
//	}
//	else if (board.at(p.x, p.y)->get_symbol() == enemy) {
//		return 1;
//	}
//}

bool State::is_equal(Point x, Point y) {
	if ((x.x == y.x) && (x.y == y.y)) {
		return 1;
	}
	return 0;
}

void State::print_info(int i) {
	
	if (werewolves_vector[i]->get_health() > 0) {
		cout << i << ". Werewolf's health = " << werewolves_vector[i]->get_health() << "\t";
	}
	else if (werewolves_vector[i]->get_health() == 0) {
		cout << i << ". Werewolf out\t";
	}
	
	if (vampires_vector[i]->get_health() > 0) {
		cout << i << ". Vampire's health = " << vampires_vector[i]->get_health() << endl;
	}
	else if (vampires_vector[i]->get_health() == 0) {
		cout << i << ". Vampire out" << endl;
	}
	
}