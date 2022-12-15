#include <iostream>
#include "classes.h"
#include <cstdlib>

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
bool Board::legal_move(Point* p) {
	// Point p is out of board
	if (p->x < 0 || p->x >= size || p->y < 0 || p->y >= size) {
		return false;
	}
	// Point p is inside the board
	else {
		if (board[p->x][p->y]->get_symbol() == '.') {
			return true;
		}
	}
}