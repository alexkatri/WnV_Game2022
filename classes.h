#pragma once
#include <string.h>

using namespace std;

struct Point {
	unsigned short int x = 0;
	unsigned short int y = 0;
	Point(unsigned short int, unsigned short int);
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

class Player : public Element {
	unsigned short int power;
	unsigned short int health = 10;
public:
	Player(const Point&, const char);
	Player(int, int, const char);
	Player();
	int get_health() const;
	int get_power() const;
	void attack(Player*);
	void health_decrease();
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
};

class Magic_filter : public Element {
public:
	Magic_filter(const Point&);
	Magic_filter(int, int);
	Magic_filter();
};

class Board {
	unsigned short int size = 10;
	Element*** board = new Element**;
public:
	Board(unsigned short int);
	Board();
	//~Board();
	int get_size() const;
	Element* at(int, int);
	void push(int, int, Element*);
	void display() const;
};

class State {
protected:
	Board board;
	Avatar avatar;
	unsigned short int num_of_trees;
	unsigned short int num_of_lakes;
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