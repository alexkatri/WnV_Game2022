#include <iostream>
#include "classes.h"
#include <cstdlib>
#include <vector>

using namespace std;

//////////////////////////
Move::Move() {};

int Move::set_direction(char player) {
	if (player == 'w') {
		return rand() % 4;
	}
	else if (player == 'v') {
		return rand() % 8;
	}
	return -1;
}
Point Move::set_destination(Point& old_p, int direction) {
	Point new_p;
	switch (direction) {
	case 0:												// UP
		new_p.x = old_p.x;
		new_p.y = --old_p.y;
		break;
	case 1:												// DOWN
		new_p.x = old_p.x;
		new_p.y = ++old_p.y;
		break;
	case 2:												// RIGHT
		new_p.x = ++old_p.x;
		new_p.y = old_p.y;
		break;
	case 3:												// LEFT
		new_p.x = --old_p.x;
		new_p.y = old_p.y;
		break;
	case 4:												// NE
		new_p.x = ++old_p.x;
		new_p.y = --old_p.y;
		break;
	case 5:												// NW
		new_p.x = --old_p.x;
		new_p.y = --old_p.y;
		break;
	case 6:												// SE
		new_p.x = ++old_p.x;
		new_p.y = ++old_p.y;
		break;
	case 7:												// SW
		new_p.x = --old_p.x;
		new_p.y = ++old_p.y;
	}
	return new_p;
}
bool Move::move_or_stay() { 
	return rand() % 2;
}
void Move::move(Board& b, Point& old_p, Player* player, int direction) {
	Point new_p = set_destination(old_p, direction);
	if (b.legal_move(new_p)) {
		player->set_point(new_p);
		b.push(new_p.x, new_p.y, player);

		b.set_ground(old_p);

	}
}
bool Move::give_medicine() {
	return rand() % 2;
}
bool Move::enemy_or_ally(Board& b, Point& p, Element* element) {					
	char ally, enemy;
	if (element->get_symbol() == 'w') {
		ally = 'w';
		enemy = 'v';
	}
	else if (element->get_symbol() == 'v') {
		ally = 'v';
		enemy = 'w';
	}
	if (b.at(p.x, p.y)->get_symbol() == ally) {
		return 0;
	}
	else if (b.at(p.x, p.y)->get_symbol() == enemy) {
		return 1;
	}
}

void Move::area_check(Board& b, Point& p, Player* player) {
	Point area;													// location to check
	for (int i = 0; i < 8; i++) {
		area = set_destination(p, i);
		if (b.check_coordinates(area)) {
			if (b.at(area.x, area.y)->get_symbol() == 'w' || b.at(area.x, area.y)->get_symbol() == 'v') {
				if (enemy_or_ally(b, area, player)) {
					//attack_enemy(player, ...);					// doesn't always attack enemy
				}
				else {
					//heal_ally(player, ...);						// doesn't necessarily heal ally
				}
			}

		}
	}
}

void Move::attack_enemy(Player* player, Player* enemy) {
	if (player->get_power() >= enemy->get_power()) {
		enemy->health_decrease(player, enemy);
	}
}
void Move::heal_ally(Player* player, Player* ally) {
	int ally_health = ally->get_health();
	if (player->first_aid_kit != 0 && ally_health < 10) {
		if (give_medicine()) {
			player->first_aid_kit_decrease();
			ally->health_increase();
		}
	}
}

void Move::werewolves_move(Board& b, State state) {
	for (int i = 0; i < state.get_num_of_werewolves(); i++) {
		if (move_or_stay()) {
			Point old_p;
			old_p = state.werewolves_vector[i]->get_point();
			move(b, old_p, state.werewolves_vector[i], set_direction('w'));
			//.player_vector.push_back(state.werewolves_vector[i]->get_point());
		}
	}
}
void Move::vampires_move(Board& b, State state) {
	for (int i = 0; i < state.get_num_of_vampires(); i++) {
		if (move_or_stay()) {
			Point old_p;
			old_p = state.vampires_vector[i]->get_point();
			move(b, old_p, state.vampires_vector[i], set_direction('v'));
			//state.player_vector.push_back(state.vampires_vector[i]->get_point());
		}
	}
}
