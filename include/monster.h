#ifndef MONSTER_H_
#define MONSTER_H_

#include <map.h>
#include <player.h>

struct monster;

// Add a new monster in x,y
struct monster* monster_init(struct monster* monster, struct player* player, int x, int y);

// Direction of the monster.
void monster_set_current_direction(struct monster* monster, enum direction direction);
int monster_get_current_direction(struct monster* monster);

// Position of the monster.
int monster_get_x(struct monster* monster);
int monster_get_y(struct monster* monster);

// Return the next monster in the list
struct monster* monster_get_next(struct monster* monster);

// Set new time after pause/load/save.
void monster_set_time(struct monster* monster,int time);

// Set new speed.
void monster_set_speed(struct monster* monster,int speed);

// Decrease the life of the monster
void monster_dec_life(struct monster* monster, int x, int y);

// Check if the monster can move or not
int monster_move_aux(struct monster* monster, struct map* map, int x, int y);

// Search a CELL_MONSTER on the map and give birth to a monster on it
struct monster* monster_all_initiation(struct monster* monster, struct player* player, struct map* map);

//Move the monster randomly
int monster_move(struct monster* monster, struct map* map, struct player* player);

//Intelligent movement.
int better_move(struct monster* monster, struct map* map, struct player* player);

//Delete monsters in the list when life=0
struct monster* monster_delete(struct monster* monster);

#endif /* MONSTER_H_ */
