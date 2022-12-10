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
	unsigned short int size;
	cout << "Give board size..." << endl;
	cin >> size;
	Board b = Board(size);

	// Dhmiourgia tou state
	int num_of_trees = size / 2;
	int num_of_lakes = size / 4;
	int num_of_players = size * size / 15;
	State state = State(b, num_of_trees, num_of_lakes, num_of_players, num_of_players);
	

	// Dhmiourgia tou avatar
	srand((unsigned)time(NULL));		// Providing a seed value
	int x = rand() % (b.get_size());
	int y = rand() % (b.get_size());
	Avatar* avatar = new Avatar(x, y);
	cout << "Choose your team...?\n";
	cout << "Press 'w' for werewolves or 'v' for vampires...\n";
	char ch;
	cin >> ch;
	if (ch == 'w') {
		avatar->set_symbol('W');
	}
	else if (ch == 'v') {
		avatar->set_symbol('V');
	}
	b.push(x, y, avatar);


	// Dhmiourgia twn ontothtwn tou board
	state.initialize();
	

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

		// print board
		system("cls");
		state.get_board().display();
		cout << "Time = " << state.get_timer();


		// Elegxos tou plhktrologiou
		if (GetKeyState(VK_NUMPAD0) & 0x8000) {  // 0x8000 -> key is
			exit = true;
		}
		if (GetKeyState(VK_SPACE) & 0x8000) {
			pause = true;
			system("cls");
			this_thread::sleep_for(200ms);
			cout << "GAME PAUSED...\n\n";
			cout << "Number of active werewolves is: " << state.get_num_of_werewolves() << endl;
			cout << "Number of active vampires is: " << state.get_num_of_vampires() << endl;
			cout << "Avatar has " << avatar->get_num_of_magic_filters() << " magic filters available" << endl << endl;
			cout << "Press SPACE to return to game..." << endl;
			while (pause) {
				if (GetKeyState(VK_SPACE) & 0x8000) {
					pause = false;
				}
			}
		}

		// Elegxos gia gameover
		if (state.get_num_of_werewolves() == 0) {
			system("cls");
			this_thread::sleep_for(200ms);
			cout << "GAME OVER...\n\n" << "VAMPIRES WIN !!!\n\n";
			exit = true;
		}
		if (state.get_num_of_vampires() == 0) {
			system("cls");
			this_thread::sleep_for(200ms);
			cout << "GAME OVER...\n\n" << "WEREWOLVES WIN !!!\n\n";
			exit = true;
		}

		this_thread::sleep_for(100ms);			// for the time pace
	}

	delete avatar;
	return 0;
}
