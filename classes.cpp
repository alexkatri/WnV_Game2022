

struct Point {
	unsigned short int x;
	unsigned short int y;

public:
	Point(unsigned short int a, unsigned short int b) : x(a), y(b) {};
};


class Element {
	Point point;
	//	char symbol;

public:
	void set_point(const Point& p) {
		point = p;
	}
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
	Element(const Point& p) : point(p) {};
	//	virtual void set_symbol() = 0;
};

class Player : Element {

private:
	unsigned short int power;
	unsigned short int health;

public:
	virtual void attack() {};
	Player(const Point& p) {
		set_point(p);
	};
	//	void set_symbol() {
	//		symbol = '.';
	//	};

};

class Werewolve : public Player, public Element {

public:
	void attack() {};
	//	void set_symbol() {
	//		symbol = 'W';
	//	}
};

class Vampire : public Player, public Element {

public:
	void attack() {};
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

class Board {
	Player** board;
	unsigned short int size;

public:
	Board(unsigned short int n) : size(n) {
		board = new Player * [n];
		for (int i = 0; i < n; i++) {
			board[i] = new Player[n];
		}
	};

	~Board() {
		for (int i = 0; i < size; i++) {
			delete[] board[i];
		}
		delete[] board;
	}

};

class State {
	Board board;
	bool day;

};
