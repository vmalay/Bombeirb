/*******************************************************************************
 * This file is part of Bombeirb.
 * Copyright (C) 2018 by Laurent R
 ******************************************************************************/
#ifndef SPRITE_H_
#define SPRITE_H_

#include <SDL/SDL.h>
#include <map.h>
#include <constant.h>

// load game's sprites
void sprite_load();
void sprite_free();
SDL_Surface* sprite_get_player(enum direction direction, int character, int state);
SDL_Surface* sprite_get_monster(enum direction direction, int world, int sub_type);
SDL_Surface* sprite_get_bonus(enum bonus_type bonus_type);
SDL_Surface* sprite_get_bomb(int bomb_state);
SDL_Surface* sprite_get_fire();
SDL_Surface* sprite_get_tree(int world);
SDL_Surface* sprite_get_box(int world);
SDL_Surface* sprite_get_key();
SDL_Surface* sprite_get_stone(int world);
SDL_Surface* sprite_get_princess();
SDL_Surface* sprite_get_banana();
SDL_Surface* sprite_get_snowman();
SDL_Surface* sprite_get_snowblock();
SDL_Surface* sprite_get_door_opened();
SDL_Surface* sprite_get_door_opened2();
SDL_Surface* sprite_get_door_closed();

SDL_Surface* sprite_get_player_win(short number);
SDL_Surface* sprite_get_number(short number);
SDL_Surface* sprite_get__number(short number);
SDL_Surface* sprite_get_banner_life();
SDL_Surface* sprite_get_banner_bomb();
SDL_Surface* sprite_get_banner_line();
SDL_Surface* sprite_get_banner_range();
//Change 2
SDL_Surface* sprite_record_victory();
SDL_Surface* sprite_virgule();

SDL_Surface* sprite_get_system_menu(int number);
SDL_Surface* sprite_get_menu(int number);
SDL_Surface* sprite_get_saving();
SDL_Surface* sprite_get_quickpause();
SDL_Surface* sprite_get_quicksave();
SDL_Surface* sprite_get_quickload();

SDL_Surface*sprite_get_game_over();
SDL_Surface*sprite_get_game_win();

SDL_Surface* sprite_get_fond(int world);

#endif /* SPRITE_H_ */



