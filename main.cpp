#include <iostream>
#include <windows.h>   // for keyboard input (windows)
#include "classes.h"

using namespace std;



int main() {
	unsigned short int size;
	cout << "Give board size..." << endl;
	cin >> size;
	Board b = Board(size);
	
	bool exit = false;
	while (!exit) {
		system("cls");
		b.display();
		if (GetKeyState(VK_NUMPAD0) & 0x8000) {  // 0x8000 -> key is
			exit = true;
		}
	}

	return 0;
}
