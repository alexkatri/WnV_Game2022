#include <iostream>
#include <windows.h>   // for keyboard input (windows)
#include "classes.h"

using namespace std;


struct Point {
	unsigned short int x;
	unsigned short int y;

public:
	Point(unsigned short int a, unsigned short int b) : x(a), y(b) {};
};


class Element {
	Point point;
	//	char symbol;

public:
	void set_point(const Point& p) {
		point = p;
	}
	void move_up() {
		point.y++;
	}
	void move_down() {
		point.y--;
	}
	void move_right() {
		point.x++;
	}
	void move_left() {
		point.x--;
	}
	Element(const Point& p) : point(p) {};
	//	virtual void set_symbol() = 0;
};

class Player : Element {

private:
	unsigned short int power;
	unsigned short int health;

public:
	virtual void attack() {};
	//	void set_symbol() {
	//		symbol = '.';
	//	};

};

class Board {
	char** board;
	unsigned short int size;

public:
	Board(unsigned short int n) : size(n) {
		board = new char* [n];
		for (int i = 0; i < n; i++) {
			board[i] = new char[n];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				board[i][j] = '.';
			}
		}
	};

	~Board() {
		for (int i = 0; i < size; i++) {
			delete[] board[i];
		}
		delete[] board;
	}
	void display() const {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				cout << board[i][j] << " ";
			}
			cout << endl;
		}
	}
};

class State {
	Board board;
	bool day;
};


int main() {
	unsigned short int size;
	cout << "Give board size..." << endl;
	cin >> size;
	Board b(size);

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
