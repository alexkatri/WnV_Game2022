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
	bool is_empty() const;			// Epistrefei true an to stoixeio tou board einai keno
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
	int get_defence() const;
	int get_first_aid_kit() const;
	void set_first_aid_kit(int);
	void initialize();				// Arxikopoiei ta epipeda power, defence kai first_aid_kit me tyxaies times
	//void attack(Player*);			// Gia antipalo paixth
	//void heal(Player*);				// Gia sympaixth
	void health_decrease(Player*, Player*);
	void health_increase();
	bool move_or_stay();
	void move_up();
	void move_down();
	void move_right();
	void move_left();
	void move_NW();
	void move_NE();
	void move_SW();
	void move_SE();

	void attack_enemy(Player*, Player*);
	void heal_ally(Player*, Player*);
	void first_aid_kit_decrease();
	bool give_medicine();
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
	Element*** board;				// Didiastato array apo Element*
public:
	Board(unsigned short int);
	Board();
	//~Board();
	int get_size() const;
	Element* at(int, int);			// Epistrefei to stoixeio tou board sth thesh (x, y)
	void push(int, int, Element*);	// Eisagei ena stoixeio sth thesh (x, y) tou board
	void display() const;
	bool legal_move(Player*, Point*);
	bool legal_move(Player*, int, int);
	void move(Player*, int);
	bool check_coordinates(Point&);
	void set_ground(Point);
	bool other_player(Point);
	bool enemy_or_ally(Point&, Element*);	// 1 = enemy, 0 = ally

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
	void change_timer(string);			// Allazei th mera h th nyxta
	void initialize();					// Dhmiourgei tis ontothtes tou board tyxaia
	void team_heal(char);				// Epoulwnei ola ta melh ths omadas tou Avatar
	void avatar_move(int);
	void state_update(int);
	//void delete_players(int);

	void scan_area(int);
	void area_check(Player*);
	Player* get_player(Point, char);			// returns the player on a specific location
	Point set_destination(Player*, int);
	//bool enemy_or_ally(Point&, Element*);	// 1 = enemy, 0 = ally
	bool is_equal(Point, Point);					// looking for allies and enemies (also healing or attacking if necessary)
	void print_info(int);
};