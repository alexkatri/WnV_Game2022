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
	//// Providing a seed value
	//srand((unsigned)time(NULL));
	int num_of_trees = size;
	int num_of_lakes = size / 2;
	State state = State(b, num_of_trees, num_of_lakes);
	state.initialize();
	
	bool exit = false;
	while (!exit) {
		system("cls");
		state.get_board().display();
		this_thread::sleep_for(200ms);			// for the time pace
		if (GetKeyState(VK_NUMPAD0) & 0x8000) {  // 0x8000 -> key is
			exit = true;
		}
	}

	return 0;
}
