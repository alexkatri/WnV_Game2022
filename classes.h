#pragma once
#include <string>
#include <vector>

using namespace std;

struct Point {
	int x = 0;
	int y = 0;
	Point(int, int);
	Point() {};

	bool near_points(Point);
	bool equal(Point&);
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
	int health = 5;
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

	void initialize();						// Arxikopoiei ta epipeda power, defence kai first_aid_kit me tyxaies times
	
	void attack(Player*);					// Gia antipalo paixth
	void heal(Player*);						// Gia sympaixth
	void health_decrease(Player*, Player*);
	void health_increase();
	
	bool move_or_stay();					// true = move, false = stay
	bool enemy(Element*);					// true = enemy, false = ally
	
	void move_up();
	void move_down();
	void move_right();
	void move_left();
	void move_NW();
	void move_NE();
	void move_SW();
	void move_SE();
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
	Element*** board;					// Didiastato array apo Element*
public:
	Board(unsigned short int);
	Board();

	int get_size() const;
	Element*** get_board();
	Element* at(int, int);				// Epistrefei to stoixeio tou board sth thesh (x, y)
	void push(int, int, Element*);		// Eisagei ena stoixeio sth thesh (x, y) tou board
	void display() const;				// printing the board
	bool legal_move(Player*, int, int);	// making sure the location (x, y) is valid or empty 
	void move(Player*, int);
	void kill(int, int);				// Diagrafei to stoixeio apo ton xarth
	void board_delete();				// Memory deallocation
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
	
	void change_timer(string);				// Allazei th mera h th nyxta
	void print() const;						
	void initialize();						// Dhmiourgei tis ontothtes tou board tyxaia
	void team_heal(char);					// Epoulwnei ola ta melh ths omadas tou Avatar
	void avatar_move(int);
	void state_update();					// Metakinei tous paixtes kai tautoxrona kanei attack/ heal
	bool gameover() const;					// Elegxos gia gameover
	void key_control(bool&, bool&, char);	// Elegxos tou plhktrologiou
	void print_info();						// Ektupwnei ta stoixeia tou kathe paikti otan patietai to "SPACE"
	bool is_health_full(char);				// 1 = not full, 0 = full
	void state_delete();					// Memory deallocation

};