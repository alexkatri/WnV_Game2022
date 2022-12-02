#pragma once

using namespace std;

struct Point {
	unsigned short int x;
	unsigned short int y;
public:
	Point(unsigned short int, unsigned short int);
	Point() {};
};

class Element {
	Point point;
	char symbol;
public:
	void set_point(const Point&);
	virtual void set_symbol(char);
	char get_symbol() const;
	Element(const Point&, const char);
	Element();

	/*
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
	*/

};

class Tree : public Element {
public:
	Tree();
};

class Lake : public Element {
public:
	Lake();
};

class Player : public Element {
	unsigned short int power;
	unsigned short int health;
public:
	virtual void attack() {};
	Player(const Point&, const char);
};

class Werewolve : public Player, public Element {
public:
	//void attack();
	//	void set_symbol() {
	//		symbol = 'W';
	//	}
};

class Vampire : public Player, public Element {
public:
	//void attack();
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

class Avatar;

class Board {
	Element** board;
	unsigned short int size;
public:
	Board(unsigned short int);
	Board();
	~Board();
	int get_size() const;
	void display() const;
};

class State {
	Board board;
	unsigned short int num_of_trees;
	unsigned short int num_of_lakes;
	//bool day;
public:
	State(Board&, int, int);
	void initialize();
};