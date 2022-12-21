#include <iostream>
#include "classes.h"
#include <cstdlib>
#include <thread>

using namespace std;


////////////////////////////// class Board
Board::Board(unsigned short int n) : size(n) {
	board = new Element * *[n];
	for (int i = 0; i < n; i++) {
		board[i] = new Element * [n];
		for (int j = 0; j < n; j++) {
			board[i][j] = new Element(i, j, '.');
		}
	}
}
Board::Board() {
	board = new Element * *[size];
	for (int i = 0; i < size; i++) {
		board[i] = new Element * [size];
		for (int j = 0; j < size; j++) {
			board[i][j] = new Element(i, j, '.');
		}
	}
}
//Board::~Board() {
//	for (int i = 0; i < size; i++) {
//		delete[] board[i];
//	}
//	delete[] board;
//}
int Board::get_size() const {
	return size;
}
Element*** Board::get_board() {
	return board;
}
Element* Board::at(int x, int y) {
	return board[x][y];
}
void Board::display() const {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << board[i][j]->get_symbol() << "  ";
		}
		cout << endl;
	}
	cout << endl << endl;
}
void Board::push(int x, int y, Element* element) {
	delete board[x][y];
	board[x][y] = element;
	board[x][y]->set_empty(false);
}
bool Board::legal_move(Player* p, int x, int y) {
	// Point p is out of board
	if (x < 0 || x >= size || y < 0 || y >= size) {
		return false;
	}
	// Point p is inside the board
	else {
		if (board[x][y]->get_symbol() == '.') {
			return true;
		}
		if (p->get_symbol() == 'W' || p->get_symbol() == 'V') {
			if (board[x][y]->get_symbol() == '$') {
				return true;
			}
		}
	}
	return false;
}
void Board::move(Player* p, int i) {
	Point old_p = p->get_point();
	switch (i) {
	case 0:
		if (legal_move(p, old_p.x - 1, old_p.y)) {
			p->move_up();
			break;
		}
		else {
			return;
		}
	case 1:
		if (legal_move(p, old_p.x + 1, old_p.y)) {
			p->move_down();
			break;
		}
		else {
			return;
		}
	case 2:
		if (legal_move(p, old_p.x, old_p.y + 1)) {
			p->move_right();
			break;
		}
		else {
			return;
		}
	case 3:
		if (legal_move(p, old_p.x, old_p.y - 1)) {
			p->move_left();
			break;
		}
		else {
			return;
		}
	case 4:	// NW
		if (legal_move(p, old_p.x - 1, old_p.y - 1)) {
			p->move_NW();
			break;
		}
		else {
			return;
		}
	case 5: // NE
		if (legal_move(p, old_p.x - 1, old_p.y + 1)) {
			p->move_NE();
			break;
		}
		else {
			return;
		}
	case 6: // SW
		if (legal_move(p, old_p.x + 1, old_p.y - 1)) {
			p->move_SW();
			break;
		}
		else {
			return;
		}
	case 7: // SE
		if (legal_move(p, old_p.x + 1, old_p.y + 1)) {
			p->move_SE();
			break;
		}
		else {
			return;
		}
	}

	push(p->get_point().x, p->get_point().y, p);
	board[old_p.x][old_p.y] = new Element(old_p.x, old_p.y, '.');
}
void Board::kill(int x, int y) {
	delete board[x][y];
	board[x][y] = new Element(x, y, '.');
}