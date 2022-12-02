#include <iostream>
#include "classes.h"

using namespace std;

//////////////////////////////////// class Point
Point::Point(unsigned short int a, unsigned short int b) : x(a), y(b) {};



/////////////////////////////////// class Element
Element::Element(const Point& p, const char c) : point(p), symbol(c) {};
Element::Element() {
	symbol = '.';
}
void Element::set_point(const Point& p) {
	point = p;
}
void Element::set_symbol(char c = '.') {
	symbol = c;
}
char Element::get_symbol() const {
	return symbol;
}


/////////////////////////////////// class Player
Player::Player(const Point& p, const char c) {
	Element::set_point(p);
	Element::set_symbol(c);
};



////////////////////////////// class Board
Board::Board(unsigned short int n) : size(n) {
	board = new Element*[n];
	for (int i = 0; i < n; i++) {
		board[i] = new Element[n];
	}
}
Board::~Board() {
	for (int i = 0; i < size; i++) {
		delete[] board[i];
	}
	delete[] board;
}
void Board::display() const {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << board[i][j].get_symbol() << " ";
		}
		cout << endl;
	}
}


