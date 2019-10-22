/*******************************************************************************
* This file is part of Bombeirb.
 * Copyright (C) 2018 by Laurent R
 ******************************************************************************/
#ifndef PLAYER_H_
#define PLAYER_H_

#include <map.h>
#include <constant.h>

struct player;

// Creates a new player with a given number of available bombs
struct player* player_init(int difficulty, int character, int score);

// Free player memory location
void player_free(struct player* player);

// Display the player on the screen
void player_display(struct player* player);

// Player position
void player_set_position(struct player* player, int x, int y);

// Player position x
int player_get_x(struct player* player);
void player_set_x(struct player *player, int x);

// Player position y
int player_get_y(struct player* player);
void player_set_y(struct player *player, int y);

// Player current direction
void player_set_current_direction(struct player* player, enum direction direction);
int player_get_current_direction(struct player* player);

// Player life
int player_get_life(struct player* player);
void player_set_life(struct player* player, int life);
void player_inc_life(struct player * player);
void player_dec_life(struct player * player);

// Player key
int player_get_key(struct player* player);
void player_set_key(struct player* player, int key);
void player_inc_key(struct player* player, struct map* map);
void player_dec_key(struct player* player);

// Player nb_bomb
int  player_get_nb_bomb(struct player * player);
void player_set_nb_bomb(struct player* player, int number_bombs);
void player_inc_nb_bomb(struct player * player);
void player_dec_nb_bomb(struct player * player);

// Player range
int player_get_range(struct player* player);
void player_set_range(struct player* player,int range);

// Player current level
int player_get_current_level(struct player* player);
void player_inc_current_level(struct player* player);
void player_dec_current_level(struct player* player);
void player_set_current_level(struct player* player, int number);

// Player state
int player_get_state(struct player* player);
void player_set_state(struct player* player, int state);

// Player timer
int player_get_timer(struct player* player);
void player_set_timer(struct player* player, int timer);

// Player difficulty
int player_get_difficulty(struct player* player);
void player_set_difficulty(struct player* player, int difficulty);

// Player character
int player_get_character(struct player* player);
void player_set_character(struct player* player, int character);

// Player bomb timer
void player_set_bombtimer(struct player* player,int position, int valeur);
int player_get_bombtimer(struct player* player, int position);

// Player bomb position
int player_get_bomb_position(struct player* player);
void player_inc_bomb_position(struct player* player);

// Player score
int player_get_score(struct player* player);
void player_set_score(struct player* player, int score);
void player_inc_score(struct player* player);

// Player level change.
int player_get_level_change(struct player* player);
void player_set_level_change(struct player* player, int number);

// Player movement, box movement, bonus effect and door decision.
int player_move_box(struct player* player, struct map* map, int x, int y);
int player_bonus_effect(struct player* player, struct map* map, int x, int y);
int player_on_door(struct player* player, struct map* map, int x, int y);

int player_move(struct player* player, struct map* map);

//Load the player with the saved file data/save/player_save
struct player* player_load(int x, int y, int map_level, int bomb_number,int key, int life, int bomb_range, int current_direction, int difficulty, int character, int state, int timer);

#endif /* PLAYER_H_ */



















