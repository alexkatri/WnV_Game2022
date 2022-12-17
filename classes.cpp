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
Point Element::get_point() const {
	return point;
}
char Element::get_symbol() const {
	return symbol;
}
bool Element::is_empty() const {
	return empty;
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
int Player::get_first_aid_kit() const {
	return first_aid_kit;
}


void Player::set_power() {
	power = rand() % 4;
	while (power == 0) {
		power = rand() % 4;
	}
}
void Player::set_defence() {
	defence = rand() % 3;
	while (defence == 0) {
		defence = rand() % 3;
	}
}
void Player::set_first_aid_kit() {
	first_aid_kit = rand() % 3;
}


void Player::initialize() {
	srand((unsigned)time(NULL));

	set_power();
	set_defence();
	set_first_aid_kit();
}
void Player::health_decrease(Player* attacker, Player* defender) {
	if (attacker->power >= defender->defence) {
		defender->health -= attacker->power - defender->defence;
	}
}
void Player::health_increase() {
	++health;
}
void Player::first_aid_kit_decrease() {
	--first_aid_kit;
}
void Player::attack(Player* p) {
	p->health_decrease(this, p);
}
//void Player::heal(Player* p) {
//	p->health_increase();
//}
//void Player::move_up() {
//	++point.y;
//}
//void Player::move_down() {
//	--point.y;
//}
//void Player::move_right() {
//	++point.x;
//}
//void Player::move_left() {
//	--point.x;
//}



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
