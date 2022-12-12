#include <iostream>
#include "classes.h"
#include <cstdlib>

using namespace std;

//////////////////////////////////// struct Point
Point::Point(int a, int b) : x(a), y(b) {};



/////////////////////////////////// base class Element
Element::Element(const Point& p, const char c) : point(p), symbol(c), empty(true) {};
Element::Element(int x, int y, char c) : point(x, y), symbol(c), empty(true) {};
Element::Element() : point(0, 0), symbol('.'), empty(true) {};
void Element::set_point(const Point& p) {
	point = p;
}
void Element::set_symbol(char c) {
	symbol = c;
}
void Element::set_empty(bool b) {
	empty = b;
}
bool Element::is_empty() const {
	return empty;
}
char Element::get_symbol() const {
	return symbol;
}


/////////////////////////////////////// classes Tree, Lake, Magic_filter
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
Magic_filter::Magic_filter() : Element() {
	set_symbol('$');
}
Magic_filter::Magic_filter(const Point& p) : Element(p, '$') {};
Magic_filter::Magic_filter(int x, int y) : Element(x, y, '$') {};



/////////////////////////////////// class Player
Player::Player(const Point& p, const char c) : Element(p, c) {
	this->initialize();
};
Player::Player(int x, int y, const char c) : Element(x, y, c) {
	this->initialize();
};
Player::Player() : Element() {
	set_symbol('P');
	this->initialize();
}
int Player::get_health() const {
	return health;
}
int Player::get_power() const {
	return power;
}
int Player::get_first_aid_kit() const {
	return first_aid_kit;
}
void Player::set_first_aid_kit(int n) {
	first_aid_kit = n;
}
void Player::initialize() {
	srand((unsigned)time(NULL));

	int x = rand() % 4;
	while (x == 0) {
		x = rand() % 4;
	}
	power = x;

	int y = rand() % 3;
	while (y == 0) {
		y = rand() % 3;
	}
	defence = y;

	first_aid_kit = rand() % 3;
}
void Player::health_decrease(Player* attacker, Player* defender) {
	defender->health -= attacker->power - defender->defence;
}
void Player::health_increase() {
	++health;
}
void Player::attack(Player* p) {
	p->health_decrease(this, p);
}
void Player::heal(Player* p) {
	p->health_increase();
}
void Player::move_up() {
	++point.y;
}
void Player::move_down() {
	--point.y;
}
void Player::move_right() {
	++point.x;
}
void Player::move_left() {
	--point.x;
}



//////////////////////////////// class Werewolve
Werewolve::Werewolve(int x, int y) : Player(x, y, 'w') {};
Werewolve::Werewolve() : Player() {};

//////////////////////////////// class Vampire
Vampire::Vampire(int x, int y) : Player(x, y, 'v') {};
Vampire::Vampire() : Player() {};

//////////////////////////////// class Avatar
Avatar::Avatar(int x, int y) : Player(x, y, 'A') {};
Avatar::Avatar() : Player() {};
int Avatar::get_num_of_magic_filters() const {
	return num_of_magic_filters;
}
void Avatar::increase_magic_filters() {
	++num_of_magic_filters;
}



////////////////////////////// class Board
Board::Board(unsigned short int n) : size(n) {
	board = new Element**[n];
	for (int i = 0; i < n; i++) {
		board[i] = new Element*[n];
		for (int j = 0; j < n; j++) {
			board[i][j] = new Element(i, j, '.');
		}
	}
}
Board::Board() {
	board = new Element**[size];
	for (int i = 0; i < size; i++) {
		board[i] = new Element*[size];
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





/////////////////////////////////////////////////
State::State(Board& b, int x, int y, int w, int v) : board(b), num_of_trees(x), num_of_lakes(y), num_of_werewolves(w), num_of_vampires(v) {};
State::State(Board& b) : board(b), num_of_trees(0), num_of_lakes(0), num_of_werewolves(0), num_of_vampires(0) {};
Board State::get_board() const {
	return board;
}
int State::get_num_of_werewolves() const {
	return num_of_werewolves;
}
int State::get_num_of_vampires() const {
	return num_of_vampires;
}
string State::get_timer() const {
	return timer;
}
void State::change_timer(string s) {
	timer = s;
}
void State::initialize() {
	srand((unsigned)time(NULL));

	int x;
	int y;
	bool exit = false;
	while (!exit) {
		x = rand() % (board.get_size());
		y = rand() % (board.get_size());
		if (board.at(x, y)->is_empty()) {	// h thesi tou board einai kenh
			Magic_filter* magic_filter = new Magic_filter(x, y);
			board.push(x, y, magic_filter);
			exit = true;
		}
	}

	for (int i = 0; i < num_of_werewolves; i++) {
		bool exit = false;
		while (!exit) {
			x = rand() % (board.get_size());
			y = rand() % (board.get_size());
			if (board.at(x, y)->is_empty()) {	// h thesi tou board einai kenh
				Werewolve* werewolve = new Werewolve(x, y);
				//werewolve->initialize();
				board.push(x, y, werewolve);
				exit = true;
			}
		}
	}

	for (int i = 0; i < num_of_vampires; i++) {
		bool exit = false;
		while (!exit) {
			x = rand() % (board.get_size());
			y = rand() % (board.get_size());
			if (board.at(x, y)->is_empty()) {	// h thesi tou board einai kenh
				Vampire* vampire = new Vampire(x, y);
				//vampire->initialize();
				board.push(x, y, vampire);
				exit = true;
			}
		}
	}

	for (int i = 0; i < num_of_trees; i++) {
		bool exit = false;
		while (!exit) {
			x = rand() % (board.get_size());
			y = rand() % (board.get_size());
			if (board.at(x, y)->is_empty()) {	// h thesi tou board einai kenh
				Tree* tree = new Tree(x, y);
				board.push(x, y, tree);
				exit = true;
			}
		}
	}

	for (int i = 0; i < num_of_lakes; i++) {
		bool exit = false;
		while (!exit) {
			x = rand() % (board.get_size());
			y = rand() % (board.get_size());
			if (board.at(x, y)->is_empty()) {	// h thesi tou board einai kenh	
				Lake* lake = new Lake(x, y);
				board.push(x, y, lake);
				exit = true;
			}
		}
	}
}

