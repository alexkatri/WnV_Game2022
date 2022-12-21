#include <iostream>
#include <windows.h>   // for keyboard input (windows)
#include <chrono>	// for the time pace
#include <thread>	// for the time pace
#include <cstdlib>
#include "classes.h"

using namespace std;
using namespace std::chrono;
using namespace chrono_literals; // for the time pace
// it works for windows


int main() {
	
	// Initial message
	cout << "\nWelcome...\n";
	this_thread::sleep_for(1.5s);
	system("cls");
	cout << "\nSoon you will have to choose a team...\n\n";
	this_thread::sleep_for(1s);
	cout << "Will you be a Werewolf or a Vampire?\n";
	this_thread::sleep_for(2s);
	system("cls");
	cout << "\nYou will have a magic potion on your possession, \nwhich can be used only once, to heal all your team members." << endl << endl;
	this_thread::sleep_for(3s);
	cout << "There will also be an additional magic potion on the map...\n";
	this_thread::sleep_for(1.5s);
	cout << "Make sure to find it and get it!!!";
	this_thread::sleep_for(2.5s);
	system("cls");

	// Dhmiourgia tou board
	unsigned short int size;
	cout << "Give board size... (10 - 20)\n";
	bool valid = false;
	while (!valid) {
		try {
			cin >> size;
			if (size < 10 || size > 20) {
				throw(invalid_argument("Not valid size... Input must be between 10 and 20"));
			}
			valid = true;
		}
		catch (invalid_argument& inpt) {
			cerr << inpt.what() << endl;
		}
	}
	cout << endl;
	Board b = Board(size);


	// Dhmiourgia tou avatar
	srand((unsigned)time(NULL));		// Providing a seed value
	int x = rand() % (b.get_size());
	int y = rand() % (b.get_size());
	Avatar* avatar = new Avatar(x, y);
	cout << "Choose your team...\n";
	cout << "Press 'w' for werewolves or 'v' for vampires...\n";
	char ch;				// Exei to xarakthra 'w' h 'v' analoga me thn omada pou uposrthrizei o avatar
	valid = false;
	while (!valid) {
		try {
			cin >> ch;
			if (ch != 'w' && ch != 'v') {
				throw(invalid_argument("Not valid argument... Input must be either 'w' or 'v'"));
			}
			valid = true;
		}
		catch (invalid_argument& inpt) {
			cerr << inpt.what() << endl;
		}
	}
	if (ch == 'w') {
		avatar->set_symbol('W');
		
		// screen message
		system("cls");
		cout << "\nSo Werewolf it is...\n\n";
		this_thread::sleep_for(1s);
		cout << "Be careful..." << endl;
		this_thread::sleep_for(1s);
		cout << "You can use the magic potion only at night!!!" << endl;
		this_thread::sleep_for(2s);
	}
	else if (ch == 'v') {
		avatar->set_symbol('V');
		
		// screen message
		system("cls");
		cout << "\nSo Vapire it is...\n\n";
		this_thread::sleep_for(1s);
		cout << "Be careful..." << endl;
		this_thread::sleep_for(1s);
		cout << "You can use the magic potion only at daytime!!!" << endl;
		this_thread::sleep_for(2s);
	}
	b.push(x, y, avatar);


	// Dhmiourgia tou state
	int num_of_trees = size / 2;
	int num_of_lakes = size / 4;
	int num_of_players = size * size / 15;
	State state = State(b, avatar, num_of_trees, num_of_lakes, num_of_players, num_of_players);
	state.initialize();		// Dhmiourgia twn ontothtwn tou board



	bool exit = false;
	bool pause = false;
	auto time_then = high_resolution_clock::now();
	auto change_time = 10s;		// H mera kai h nuxta diarkoun 10 seconds
	while (!exit) {
		// Allagh wras
		auto time_now = high_resolution_clock::now();
		auto time_elapsed = duration_cast<seconds>(time_now - time_then);
		if (time_elapsed >= change_time) {
			if (state.get_timer() == "day") {
				state.change_timer("night");
			}
			else {
				state.change_timer("day");
			}
			time_then = time_now;
		}

		//state.print_info();
		state.print();
		state.state_update();
		state.key_control(exit, pause, ch);
		if (state.gameover()) exit = true;

		this_thread::sleep_for(100ms);			// for the time pace
	}

	delete avatar;
	return 0;
}