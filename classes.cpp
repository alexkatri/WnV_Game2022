#include <iostream>
#include "classes.h"
#include <cstdlib>

using namespace std;

//////////////////////////////////// struct Point
Point::Point(int a, int b) : x(a), y(b) {};


bool Point::near_points(Point p) {
	if ((this->x == p.x - 1 && this->y == p.y) || (this->x == p.x + 1 && this->y == p.y) || (this->x == p.x && this->y == p.y - 1) || (this->x == p.x && this->y == p.y + 1)) {
		return true;
	}
	return false;
}
bool Point::equal(Point& p) {
	if (this->x == p.x && this->y == p.y) {
		return true;
	}
	return false;
}



//////////////////////////////////// base class Element
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


Point Element::get_point() const {
	return point;
}
char Element::get_symbol() const {
	return symbol;
}


bool Element::is_empty() const {
	return empty;
}



//////////////////////////////////// classes Tree, Lake, Magic_filter
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



//////////////////////////////////// class Player
Player::Player(const Point& p, const char c) : Element(p, c) {
	initialize();
};
Player::Player(int x, int y, const char c) : Element(x, y, c) {
	initialize();
};
Player::Player() : Element() {
	set_symbol('P');
	initialize();
}


int Player::get_health() const {
	return health;
}
int Player::get_power() const {
	return power;
}
int Player::get_defence() const {
	return defence;
}
int Player::get_first_aid_kit() const {
	return first_aid_kit;
}


void Player::set_first_aid_kit(int n) {
	first_aid_kit = n;
}


void Player::initialize() {
	
	// setting the power
	int x = rand() % 4;
	while (x == 0) {
		x = rand() % 4;
	}
	power = x;

	// setting the defence
	int y = rand() % 3;
	while (y == 0) {
		y = rand() % 3;
	}
	defence = y;

	// setting the first aid kit
	first_aid_kit = rand() % 3;
}


void Player::attack(Player* p) {
	p->health_decrease(this, p);
}
void Player::heal(Player* p) {
	p->health_increase();
	--first_aid_kit;
}
void Player::health_decrease(Player* attacker, Player* defender) {
	if (attacker->power >= defender->defence) {
		defender->health -= attacker->power - defender->defence;
	}
}
void Player::health_increase() {
	if (health < 5)
		++health;
}


bool Player::move_or_stay() {
	return rand() % 2;
}
bool Player::enemy(Element* p) {
	if (this->get_symbol() == 'w' && p->get_symbol() == 'v') {
		return true;
	}
	if (this->get_symbol() == 'v' && p->get_symbol() == 'w') {
		return true;
	}
	return false;
}


void Player::move_up() {
	--point.x;
}
void Player::move_down() {
	++point.x;
}
void Player::move_right() {
	++point.y;
}
void Player::move_left() {
	--point.y;
}
void Player::move_NW() {
	move_up();
	move_left();
}
void Player::move_NE() {
	move_up();
	move_right();
}
void Player::move_SW() {
	move_down();
	move_left();
}
void Player::move_SE() {
	move_down();
	move_right();
}



//////////////////////////////////// class Werewolve
Werewolve::Werewolve(int x, int y) : Player(x, y, 'w') {};
Werewolve::Werewolve() : Player() {};



//////////////////////////////////// class Vampire
Vampire::Vampire(int x, int y) : Player(x, y, 'v') {};
Vampire::Vampire() : Player() {};



//////////////////////////////////// class Avatar
Avatar::Avatar(int x, int y) : Player(x, y, 'A') {};
Avatar::Avatar() : Player() {};


int Avatar::get_num_of_magic_filters() const {
	return num_of_magic_filters;
}
void Avatar::increase_magic_filters() {
	++num_of_magic_filters;
}
void Avatar::decrease_magic_filters() {
	if (num_of_magic_filters > 0)
		--num_of_magic_filters;
}