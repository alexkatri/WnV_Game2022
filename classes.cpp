#include <iostream>
#include "classes.h"
#include <cstdlib>

using namespace std;

//////////////////////////////////// class Point
Point::Point(unsigned short int a, unsigned short int b) : x(a), y(b) {};



/////////////////////////////////// base class Element
Element::Element(const Point& p, const char c) : point(p), symbol(c), empty(true) {};
Element::Element(int x, int y, char c) : point(x, y), symbol(c), empty(true) {};
Element::Element() : point(0, 0), symbol('.'), empty(true) {};
void Element::set_point(const Point& p) {
	point = p;
}
void Element::set_symbol(char c = '.') {
	symbol = c;
}
void Element::set_empty(bool b) {
	empty = b;
}
bool Element::is_empty() const {
	if (empty != NULL) {
		return empty;
	}
	return NULL;
}
char Element::get_symbol() const {
	if (symbol != NULL) {
		return symbol;
	}
	return NULL;
}


Tree::Tree() : Element() {
	set_symbol('T');
}
Tree::Tree(const Point& p) : Element(p, 'T') {};
Tree::Tree(int x, int y) : Element(x, y, 'T') {};

Lake::Lake() : Element() {
	set_symbol('O');
}
Lake::Lake(const Point& p) : Element(p, 'O') {};
Lake::Lake(int x, int y) : Element(x, y, 'O') {};



/////////////////////////////////// class Player
Player::Player(const Point& p, const char c) : Element(p, c) {};



////////////////////////////// class Board
Board::Board(unsigned short int n) : size(n) {
	board = new Element**[n];
	for (int i = 0; i < n; i++) {
		board[i] = new Element*[n];
		for (int j = 0; j < n; j++) {
			board[i][j] = new Element(i, j, '.');
			cout << board[i][j]->is_empty() << " ";
		}
	}
}
Board::Board() {
	board = new Element**[size];
	for (int i = 0; i < size; i++) {
		board[i] = new Element*[size];
		for (int j = 0; j < size; j++) {
			board[i][j] = new Element(i, j, '.');
			cout << board[i][j]->is_empty() << " ";
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
	if (board[x][y] != NULL) {
		return board[x][y];
	}
	return NULL;
}
void Board::display() const {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << board[i][j]->get_symbol() << " ";
		}
		cout << endl;
	}
}
void Board::push(int x, int y, const Element* element) {
	board[x][y]->set_symbol(element->get_symbol());
	board[x][y]->set_empty(false);
}





/////////////////////////////////////////////////
State::State(Board& b, int x, int y) : board(b), num_of_trees(x), num_of_lakes(y) {};
State::State(Board& b) : board(b), num_of_trees(0), num_of_lakes(0) {};
Board State::get_board() const {
	return board;
}
void State::initialize() {
	srand((unsigned)time(NULL));
	int* x = new int;
	int* y = new int;
	for (int i = 0; i < num_of_trees; i++) {
		bool exit = false;
		while (!exit) {
			*x = rand() % (board.get_size());
			*y = rand() % (board.get_size());
			if (board.at(*x, *y)->is_empty()) {	// h thesi tou board einai kenh
			//if (board.at(a,b)->get_symbol() == '.') {
				Tree* tree = new Tree(*x, *y);
				board.push(*x, *y, tree);
				exit = true;
			}
		}
	}
	for (int i = 0; i < num_of_lakes; i++) {
		bool exit = false;
		while (!exit) {
			*x = rand() % (board.get_size());
			*y = rand() % (board.get_size());
			if (board.at(*x, *y)->is_empty()) {	// h thesi tou board einai kenh	
				Lake* lake = new Lake(*x, *y);
				board.push(*x, *y, lake);
				exit = true;
			}
		}
	}
	delete x;
	delete y;
}

