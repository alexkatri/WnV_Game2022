#include <iostream>
#include "classes.h"
#include <cstdlib>
#include <thread>	// for the time pace
#include <windows.h>   // for keyboard input (windows)

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
void State::print() const {
	system("cls");
	board.display();
	cout << "Time = " << timer << endl << endl;
	cout << "Press 'SPACE' for pause\n";
	cout << "Press '0' for exit\n";
	cout << "Press '1' to use magic potion\n";
}
void State::initialize() {
	//srand((unsigned)time(NULL));

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
		if (avatar->get_num_of_magic_filters() > 0) {
			if (is_health_full('w')) {
				cout << "Magic potion activated for your team members...\n\n";
				cout << "Health level to be increased for all the " << ch << "'s...\n\n";
				for (Werewolve* ptr : werewolves_vector) {
					ptr->health_increase();
				}
				avatar->decrease_magic_filters();
				cout << "Avatar now has " << avatar->get_num_of_magic_filters() << " magic potions available" << endl << endl;
			}
			else {
				cout << "No need to use your magic potion...\n\n";
				this_thread::sleep_for(0.5s);
				cout << "All your team members are healthy!\n\n";
			}
		}
		else {
			cout << "Avatar has no magic potions available...\n";
			this_thread::sleep_for(2s);
		}
		
	}
	else if (ch == 'v' && timer == "day") {
		if (avatar->get_num_of_magic_filters() > 0) {
			if (is_health_full('v')) {
				cout << "Magic potion activated for your team members...\n\n";
				cout << "Health level to be increased for all the " << ch << "'s...\n\n";
				for (Vampire* ptr : vampires_vector) {
					ptr->health_increase();
				}
				avatar->decrease_magic_filters();
				cout << "Avatar now has " << avatar->get_num_of_magic_filters() << " magic potions available" << endl << endl;
			}
			else {
				cout << "No need to use your magic potion...\n\n";
				this_thread::sleep_for(0.5s);
				cout << "All your team members are healthy!\n\n";
			}
		}
		else {
			cout << "Avatar has no magic potions available...\n";
			this_thread::sleep_for(2s);
		}

	}
	else if ((ch == 'w' && timer == "day") || (ch == 'v' && timer == "night")) {
		cout << "You can't use the magic potion now\n";
		cout << "It's still " << timer << "..." << endl;
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
	//srand((unsigned)time(NULL));
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
						cout << "\n\n\nvampire killed...";
						this_thread::sleep_for(1s);
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

		for (Werewolve* ptr2 : werewolves_vector) {
			if (ptr2 == ptr) continue;
			if (point.near_points(ptr2->get_point())) {
				if (ptr2->get_health() < 5 && ptr->get_first_aid_kit() > 0) {
					if (rand() % 2) {
						ptr->heal(ptr2);
					}
				}
			}
		}

		if (ptr->move_or_stay()) {
			board.move(ptr, rand() % 4);
		}
	}


	for (Vampire* ptr : vampires_vector) {
		Point point = ptr->get_point();
		int iterator = 0;
		for (Werewolve* enemy : werewolves_vector) {
			if (point.near_points(enemy->get_point())) {
				if (ptr->get_power() >= enemy->get_power()) {
					ptr->attack(enemy);
					if (enemy->get_health() <= 0) {
						werewolves_vector.erase(werewolves_vector.begin() + iterator);
						--num_of_werewolves;
						board.kill(enemy->get_point().x, enemy->get_point().y);
						cout << "\n\n\nwerewolf killed...";
						this_thread::sleep_for(1s);
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

		for (Vampire* ptr2 : vampires_vector) {
			if (ptr2 == ptr) continue;
			if (point.near_points(ptr2->get_point())) {
				if (ptr2->get_health() < 5 && ptr->get_first_aid_kit() > 0) {
					if (rand() % 2) {
						ptr->heal(ptr2);
					}
				}
			}
		}

		if (ptr->move_or_stay()) {
			board.move(ptr, rand() % 8);
		}
	}
}
bool State::gameover() const {
	if (num_of_werewolves == 0) {
		system("cls");
		this_thread::sleep_for(1s);
		cout << "GAME OVER...\n\n" << "VAMPIRES WIN !!!\n\n";
		this_thread::sleep_for(100ms);
		if (avatar->get_symbol() == 'V') {
			cout << "YOU WIN :)\n\n";
		}
		else {
			cout << "YOU LOSE :(\n\n";
		}
		return true;
	}
	if (num_of_vampires == 0) {
		system("cls");
		this_thread::sleep_for(1s);
		cout << "GAME OVER...\n\n" << "WEREWOLVES WIN !!!\n\n";
		this_thread::sleep_for(100ms);
		if (avatar->get_symbol() == 'W') {
			cout << "YOU WIN :)\n\n";
		}
		else {
			cout << "YOU LOSE :(\n\n";
		}
		return true;
	}
	return false;
}

void State::key_control(bool& exit, bool& pause, char team) {
	if (GetKeyState(VK_NUMPAD0) & 0x8000) {  // 0x8000 -> key is
		exit = true;
	}
	if (GetKeyState(VK_SPACE) & 0x8000) {
		pause = true;
		this_thread::sleep_for(200ms);
		cout << "\n\n\nGAME PAUSED...\n\n";
		cout << "Number of active werewolves is: " << num_of_werewolves << endl;
		cout << "Number of active vampires is: " << num_of_vampires << endl;
		cout << "Avatar has " << avatar->get_num_of_magic_filters() << " magic potions available" << endl << endl;
		print_info();
		cout << "Press SPACE to return to game..." << endl;
		while (pause) {
			if (GetKeyState(VK_SPACE) & 0x8000) {
				pause = false;
			}
		}
	}
	if (GetKeyState(VK_NUMPAD1) & 0x8000) {
		system("cls");
		this_thread::sleep_for(200ms);
		team_heal(team);
		this_thread::sleep_for(3s);
	}
	if (GetKeyState(VK_UP) & 0x8000) {
		system("cls");
		avatar_move(0);
	}
	if (GetKeyState(VK_DOWN) & 0x8000) {
		system("cls");
		avatar_move(1);
	}
	if (GetKeyState(VK_RIGHT) & 0x8000) {
		system("cls");
		avatar_move(2);
	}
	if (GetKeyState(VK_LEFT) & 0x8000) {
		system("cls");
		avatar_move(3);
	}
}

void State::print_info() {
	cout << "Werewolves: \n";
	for (int i = 0; i < num_of_werewolves; i++) {
		cout << i << ". health: " << werewolves_vector[i]->get_health() << "\tpower: " << werewolves_vector[i]->get_power() << "\tdefence: " << werewolves_vector[i]->get_defence() << "\tfirst aid kit: " << werewolves_vector[i]->get_first_aid_kit();
		cout << endl;
	}
	cout << endl << "Vampires: \n";
	for (int i = 0; i < num_of_vampires; i++) {
		cout << i << ". health: " << vampires_vector[i]->get_health() << "\tpower: " << vampires_vector[i]->get_power() << "\tdefence: " << vampires_vector[i]->get_defence() << "\tfirst aid kit: " << vampires_vector[i]->get_first_aid_kit();
		cout << endl;
	}
	cout << endl;
} 

bool State::is_health_full(char ch) {
	if (ch == 'v') {
		for (Vampire* ptr : vampires_vector) {
			if (ptr->get_health() < 5) {
				return 1;
				break;
			}

		}
		
	}
	if (ch == 'w') {
		for (Werewolve* ptr : werewolves_vector) {
			if (ptr->get_health() < 5) {
				return 1;
				break;
			}
		}
	}
	return 0;
}