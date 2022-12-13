#pragma once
#include <string.h>

using namespace std;

struct Point {
	int x = 0;
	int y = 0;
	Point(int, int);
	Point() {};
};

class Element {
protected:
	Point point;
	char symbol = '.';
	bool empty = true;
public:
	Element(const Point&, const char);
	Element(int, int, char);
	Element();
	void set_point(const Point&);
	void set_symbol(char);
	void set_empty(bool);
	Point get_point() const;
	char get_symbol() const;
	bool is_empty() const;
};

class Tree : public Element {
public:
	Tree(const Point&);
	Tree(int, int);
	Tree();
};

class Lake : public Element {
public:
	Lake(const Point&);
	Lake(int, int);
	Lake();
};

class Magic_filter : public Element {
public:
	Magic_filter(const Point&);
	Magic_filter(int, int);
	Magic_filter();
};

class Player : public Element {
	int power = 0;
	int defence = 0;
	int health = 10;
	int first_aid_kit = 0;
public:
	Player(const Point&, const char);
	Player(int, int, const char);
	Player();
	int get_health() const;
	int get_power() const;
	int get_first_aid_kit() const;
	void set_power();
	void set_first_aid_kit(int);
	void initialize();
	void attack(Player*);
	void heal(Player*);
	void health_decrease(Player*, Player*);
	void health_increase();
	void move_up();
	void move_down();
	void move_right();
	void move_left();
};

class Werewolve : public Player {
public:
	Werewolve(int, int);
	Werewolve();
};

class Vampire : public Player {
public:
	Vampire(int, int);
	Vampire();

	/*
	void move_NW() {
		move_up();
		move_left();
	}
	void move_NE() {
		move_up();
		move_right();
	}
	void move_SW() {
		move_down();
		move_left();
	}
	void move_SE() {
		move_down();
		move_right();
	}
	*/
};

class Avatar : public Player {
protected:
	int num_of_magic_filters = 1;
public:
	Avatar(int, int);
	Avatar();
	int get_num_of_magic_filters() const;
	void increase_magic_filters();
};

class Board {
	int size = 10;
	Element*** board;
public:
	Board(unsigned short int);
	Board();
	//~Board();
	int get_size() const;
	Element* at(int, int);
	void push(int, int, Element*);
	void display() const;
	bool legal_move(Point*);
};

class State {
protected:
	Board board;
	Avatar avatar;
	int num_of_trees;
	int num_of_lakes;
	int num_of_werewolves;
	int num_of_vampires;
	string timer = "day";
public:
	State(Board&, int, int, int, int);
	State(Board&);
	Board get_board() const;
	int get_num_of_werewolves() const;
	int get_num_of_vampires() const;
	string get_timer() const;
	void change_timer(string);
	void initialize();
};