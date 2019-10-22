#ifndef BOMB_H_
#define BOMB_H_

#include <player.h>
#include <map.h>
#include <monster.h>



struct bomb;

//set a bomb
struct bomb* bomb_init(struct player* player,struct map* map, struct bomb* game_bomb, int x, int y, int range, int birthtime);


// Set the coordinates of the bomb
int bomb_get_birthtime( struct bomb* bomb);
// Set the initial time of the bomb
void bomb_set_time(struct bomb* bomb);

int bomb_get_range( struct bomb* bomb);
//
int bomb_get_owner(struct bomb* bomb);
void bomb_set_owner( struct bomb* bomb, int number);
// Get the initial time of the bomb
int bomb_get_init_time(struct bomb* bomb);

// Get the coordinates of the bomb
int bomb_get_x(struct bomb* bomb);
int bomb_get_y(struct bomb* bomb);
struct bomb* bomb_get_next( struct bomb* bomb);
// Set a new initial timer after a pause
void bomb_set_timer(struct bomb* bomb,int pause_time);

// It's the main fonction for the bombs. Handle the bomb effects.
// It called every game loop.
void bomb_all(struct bomb* bomb, struct map* map, struct player* player, struct monster* monster);

// No more fire.
void bomb_off(int bomb_range, struct map* map, int x, int y);

// Destroy all the bonus from the explosion
void bomb_bonus(int bomb_range, struct map* map, int x, int y,int block[4]);

// Destroy bonus at x and y
void bomb_bonus_xy(struct map* map, int x, int y);

//Handle the explosion with the range and the obstacles
void bomb_fire(struct map* map, int x, int y, struct player* player, int timer, struct monster* monster, int tab[4], int birthtime, int bomb_range);

// Set the CELL_FIRE when bomb explodes and bring the monsters out of the case
void bomb_fire_xy(int birthtime, struct map* map, int x, int y, struct player* player, struct monster* monster);

// Return the range of the explosion that won't face obstacles
int bomb_block_fire(int bomb_range,struct map* map,int x, int y, enum direction direction);



#endif /* BOMB_H_ */


































