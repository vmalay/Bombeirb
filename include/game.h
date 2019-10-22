/*******************************************************************************
 * This file is part of Bombeirb.
 * Copyright (C) 2018 by Laurent R
 ******************************************************************************/
#ifndef GAME_H_
#define GAME_H_

#include <player.h>
#include <map.h>

// Abstract data type
struct game;
// Create a new game
struct game* game_new();


// Basics of the game.
void game_free(struct game* game);
void game_start(struct game* game, int world);
void game_level_change(struct game* game);

// Return the current structure of the game
struct player* game_get_player(struct game* game);
struct player* game_get_player2(struct game* game);
struct bomb* game_get_bomb(struct game* game);
struct map* game_get_current_map(struct game* game);
struct monster* game_get_monster(struct game* game);

// Mechanics

void bonus_meca(struct game* game);
void game_end_meca(struct game* game);
void game_meca(struct game* game);

// Display and update the game on the screen
void game_display(struct game* game);
int game_update(struct game* game);


#endif /* GAME_H_ */
