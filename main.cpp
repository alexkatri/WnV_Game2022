#include <iostream>
#include <windows.h>   // for keyboard input (windows)
#include <chrono>	// for the time pace
#include <thread>	// for the time pace
#include <cstdlib>
#include "classes.h"

using namespace std;
using namespace chrono_literals; // for the time pace
								// it works for windows


int main() {
	unsigned short int size;
	cout << "Give board size..." << endl;
	cin >> size;
	Board b = Board(size);
	int num_of_trees = size / 2;
	int num_of_lakes = size / 4;
	int num_of_players = size * size / 15;
	State state = State(b, num_of_trees, num_of_lakes, num_of_players, num_of_players);
	
	srand((unsigned)time(NULL));		// Providing a seed value
	int x = rand() % (b.get_size());
	int y = rand() % (b.get_size());
	Avatar* avatar = new Avatar(x, y);		// Dhmiourgia tou avatar
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

	state.initialize();					// Dhmiourgia twn ontothtwn tou board
	
	bool exit = false;
	bool pause = false;
	while (!exit) {
		system("cls");
		state.get_board().display();
		this_thread::sleep_for(100ms);			// for the time pace
		if (GetKeyState(VK_NUMPAD0) & 0x8000) {  // 0x8000 -> key is
			exit = true;
		}
		if (GetKeyState(VK_SPACE) & 0x8000) {
			pause = true;
			system("cls");
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

	}

	return 0;
}
