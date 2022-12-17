#pragma once
#include <string>
#include <vector>

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
	int health = 10;
	int power = 0;
	int defence = 0;
	int first_aid_kit = 0;
public:
	Player(const Point&, const char);
	Player(int, int, const char);
	Player();

	bool give_medicine();							// 1 = heal, 0 = don't heal

	int get_health() const;
	int get_power() const;
	int get_defence() const;
	int get_first_aid_kit() const;

	void set_power();				// random [1-3] ~ doesn't change
	void set_defence();				// random [1-2] ~ doesn't change
	void set_first_aid_kit();		// random [0-2] ~ decreases when it gets used

	void initialize();
	void health_decrease(Player*, Player*);
	void health_increase();
	void first_aid_kit_decrease();
	void attack_enemy(Player*, Player*);
	void heal_ally(Player*, Player*);

	friend class Move;
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
};

class Avatar : public Player {
protected:
	int num_of_magic_filters = 1;
public:
	Avatar(int, int);
	Avatar();
	int get_num_of_magic_filters() const;
	void increase_magic_filters();
	void decrease_magic_filters();
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
	bool check_coordinates(Point&);
	bool legal_move(Point&);
	void set_ground(Point);
	bool is_equal(Point, Point);
};

class State {
protected:
	Board board;
	Avatar* avatar;
	int num_of_trees;
	int num_of_lakes;
	int num_of_werewolves;
	int num_of_vampires;
	string timer = "day";
	vector <Werewolve*> werewolves_vector;
	vector <Vampire*> vampires_vector;
public:
	State(Board&, Avatar*, int, int, int, int);
	State(Board&);

	Board get_board() const;
	Avatar* get_avatar() const;
	
	int get_num_of_werewolves() const;
	int get_num_of_vampires() const;
	string get_timer() const;
	void set_board(Board);
	void set_avatar(Avatar*);
	void change_timer(string);
	void initialize();
	void team_heal(char);

	friend class Move;
};

class Move {
public:
	Move();

	int set_direction(char);						// 0 = up, 1 = down, 2 = right, 3 = left, 4 = NE, 5 = NW, 6 = SE, 7 = SW						
	Point set_destination(Point&, int);				// Point& -> old location, int -> direction || it creates the new location
	Player* get_player(State, Point, char);			// returns the player on a specific location

	bool move_or_stay();							// 1 = move, 0 = stay
	bool enemy_or_ally(Board&, Point&, Element*);	// 1 = enemy, 0 = ally
	bool is_equal(Point, Point);

	void area_check(State, Board&, Point&, Player*);		// looking for allies and enemies (also healing or attacking if necessary)
	void move(Board&, Point&, Player*, int);

	void werewolves_move(Board&, State);
	void vampires_move(Board&, State);

};

