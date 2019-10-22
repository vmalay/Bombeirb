/*******************************************************************************
 * This file is part of Bombeirb.
 * Copyright (C) 2018 by Laurent Reveilerre
 ******************************************************************************/
#include <SDL/SDL_image.h>
#include <assert.h>
#include <stdio.h>

#include <player.h>
#include <sprite.h>
#include <window.h>
#include <misc.h>
#include <constant.h>
#include <map.h>
#include <game.h>


struct player {
	int x, y;
	enum direction current_direction;
	int nb_bombs;
	int key;
	int score; // Multiplayer score.
	int life;
	int range;
	int level_change; // Usefull in order to change the current level.
	int current_level;
	int difficulty; // Easy, Normal, Hard.
	int character; // Character skin: Mario, Naruto, Saitama, Bomberman.
	int state;   // Bonus and invulnerability
	int timer;  // Duration of bonus and invulnerability
	int bombtimer[8]; //The bomb is back to your inventory when it exploses.
	int bomb_position;
};

struct player* player_init(int difficulty, int character, int score) {
	struct player* player = malloc(sizeof(*player));
	if (!player)
		error("Memory error");

	if (difficulty == 0){
		player->life = 6;
		player->nb_bombs = 2;
		player->range = 2;
	}
	if (difficulty == 1){
		player->life = 3;
		player->nb_bombs = 1;
		player->range = 2;
	}
	if (difficulty == 2){
		player->life = 1;
		player->nb_bombs = 1;
		player->range = 1;
	}

	player->current_direction = SOUTH;
	player->level_change = 0;
	player->current_level = 0;
	player->key = 0;
	player->score = score;
	player->difficulty = difficulty; // Difficulty 1 = Easy, 2 = Normal, 3 = Hard.
	player->character= character;  // Bomerman, Mario, Naruto, Saitama.
	player->state = 0;  // For bonus and invulnerability.
	player->timer = 0;  // For the duration of the bonus and invulnerability.
	player->bomb_position = 0;  // When you put a bomb, we need to take it back to your inventory after it exploses.
	for (int i=0; i<8; i++)
		player->bombtimer[i] = 0;
	return player;
}

void player_free(struct player* player) {
	assert(player);
	free(player);
}

void player_display(struct player* player) {
	assert(player);
	window_display_image(sprite_get_player(player->current_direction, player->character, player->state),player->x * SIZE_BLOC, player->y * SIZE_BLOC);
}

void player_set_position(struct player *player, int x, int y) {
	assert(player);
	player->x = x;
	player->y = y;
}

int player_get_state(struct player* player)
{
	assert(player != NULL);
	return player->state;
}

void player_set_state(struct player* player, int state)
{
	assert(player);
	player->state=state;
}

int player_get_timer(struct player* player)
{
	assert(player != NULL);
	return player->timer;
}

void player_set_timer(struct player* player, int timer)
{
	assert(player);
	player->timer=timer;
}


int player_get_difficulty(struct player* player)
{
	assert(player != NULL);
	return player->difficulty;
}


void player_set_difficulty(struct player* player, int difficulty)
{
	assert(player);
	player->difficulty=difficulty;
}
int player_get_character(struct player* player)
{
	assert(player != NULL);
	return player->character;
}
void player_set_character(struct player* player, int character)
{
	assert(player);
	player->character=character;
}


int player_get_x(struct player* player) {
	assert(player != NULL);
	return player->x;
}

int player_get_y(struct player* player) {
	assert(player != NULL);
	return player->y;
}

int player_get_key(struct player* player) {
	assert(player);
	return player->key;
}

void player_inc_key(struct player* player, struct map* map) {
	//The player walk on a key.

	assert(player);
	player->key += 1; // He gets the key.

	// Now, we want the door to be opened automaticaly. So we have to detect all door and choose the good one to open.
	int door_x=0;
	int door_y=0;
	int i, j;
	for (j = 0; j < MAP_HEIGHT; j++){
		for (i = 0; i < MAP_WIDTH; i++){
			if ( map_get_cell_type(map,i,j) == CELL_DOOR ){ // Selecting only the door location.
				door_x=i;
				door_y=j;
				int level=map_get_type(map,  door_x, door_y);
				level = level & 0x0e;
				level = level >>1;
				if ( level == player->current_level && !map_open_door(map, door_x, door_y) ){ // Choosing the next level door.
					map_open_a_door(map, door_x, door_y); // open the door in the position (x,y).
					player->key -= 1 ;
				}


			}

		}
	}
}

void player_dec_key(struct player* player) {
	assert(player);
	if (player->key > 0)
		player->key -= 1;
}

int player_get_score(struct player* player) {
	assert(player);
	return player->score;
}

void player_set_score(struct player* player, int score) {
	assert(player);
	player->score = score;
}

void player_inc_score(struct player* player) {
	assert(player);
	player->score += 1;
}

int player_get_level_change(struct player* player){
	assert(player);
	return player->level_change;
}

void player_set_level_change(struct player* player, int number){
	assert(player);
	player->level_change = number;
}


int player_get_current_level(struct player* player) {
	assert(player);
	return player->current_level;
}

void player_inc_current_level(struct player* player) {
	assert(player);
	player->current_level += 1;
}

void player_dec_current_level(struct player* player) {
	assert(player);
	player->current_level -= 1;
}

void player_set_current_level(struct player* player, int number) {
	assert(player);
	player->current_level = number;
}


void player_set_current_direction(struct player* player, enum direction direction) {
	assert(player);
	player->current_direction = direction;
}

int player_get_current_direction(struct player* player){
	assert(player);
	return player->current_direction;
}

int player_get_nb_bomb(struct player* player) {
	assert(player);
	return player->nb_bombs;
}

void player_set_nb_bomb(struct player* player, int number_bombs) {
	assert(player);
	player->nb_bombs=number_bombs;
}


void player_inc_nb_bomb(struct player* player) {
	assert(player);
	if (player->nb_bombs < 8)
		player->nb_bombs += 1;
}

void player_dec_nb_bomb(struct player* player) {
	assert(player);
	if (player->nb_bombs > 0)
		player->nb_bombs--;  // No ">1" condition because we use this function when we set a bomb.
	else
		player->nb_bombs = 0;
}

void player_set_bombtimer(struct player* player,int position, int valeur) {
	assert(player);
	player->bombtimer[position]=valeur;
}

int player_get_bombtimer(struct player* player, int position) {
	assert(player);
	return player->bombtimer[position];
}

int player_get_bomb_position(struct player* player) {
	assert(player);
	return player->bomb_position;
}

void player_inc_bomb_position(struct player* player)
{
	assert(player);
	player->bomb_position++;

	if (player->bomb_position==7){
		player->bomb_position=0;
	}
}

int player_get_range(struct player* player) {
	assert(player);
	return player->range;
}

void player_set_range(struct player* player,int range) {
	assert(player);
	player->range=range;
}

void player_inc_range(struct player* player) {
	assert(player);
	if (player->range < 8)
		player->range += 1;
	else
		player->range=8;
}

void player_dec_range(struct player* player) {
	assert(player);
	if (player->range > 0)
		player->range --;
	else
		player->range = 0;
}

int player_get_life(struct player* player) {
	assert(player);
	return player->life;
}

void player_inc_life(struct player* player) {
	assert(player);
	if (player->life < 8)
		player->life += 1;

}

void player_dec_life(struct player* player) {
	assert(player);

	if ( player_get_state(player) ==3 || player_get_state(player) ==4 ||  player_get_state(player) ==5 ){
    //Else if is needed, i can't figure out why, but i will one day.
	}
	else if (player->life > 0 && (player_get_state(player) !=3 || player_get_state(player) !=4 ||  player_get_state(player) !=5 )){
	// State 3 is the bonus invincible. State 4/5 is blinking.
		player->life -=1;
		player_set_state(player,4);
		player_set_timer(player,SDL_GetTicks());
	}

}

int player_move_box(struct player* player, struct map* map, int x, int y)
{
	// Player move the box

	int type = map_get_type(map, x, y);

	if (map_is_inside(map, x, y-1) && player->current_direction == NORTH && map_get_cell_type(map,x,y-1) == CELL_EMPTY){
		map_set_cell_type(map, x, y, CELL_EMPTY);
		map_set_type(map, x, y-1, type);
		return 1;
	}

	if (map_is_inside(map, x, y+1) && player->current_direction == SOUTH && map_get_cell_type(map,x,y+1) == CELL_EMPTY){
		map_set_cell_type(map, x, y, CELL_EMPTY);
		map_set_type(map, x, y+1, type);
		return 1;
	}

	if (map_is_inside(map, x-1, y) && player->current_direction == WEST && map_get_cell_type(map,x-1,y) == CELL_EMPTY){
		map_set_cell_type(map, x, y, CELL_EMPTY);
		map_set_type(map, x-1, y, type);
		return 1;
	}

	if (map_is_inside(map, x+1, y) && player->current_direction == EAST && map_get_cell_type(map,x+1,y) == CELL_EMPTY){
		map_set_cell_type(map, x, y, CELL_EMPTY);
		map_set_type(map, x+1, y, type);
		return 1;
	}
	return 0;
}

int player_bonus_effect(struct player* player, struct map* map, int x, int y)
// Bonus decision, we choose the effect of the bonus.
{
	switch (map_get_sub_type(map,x,y)){

	case BONUS_BOMB_RANGE_DEC:
		player_dec_range(player);
		map_set_cell_type(map, x, y, CELL_EMPTY);
		return 1;
		break;
	case BONUS_BOMB_RANGE_INC:
		player_inc_range(player);
		map_set_cell_type(map, x, y, CELL_EMPTY);
		return 1;
		break;
	case BONUS_BOMB_NB_DEC:
		if (player_get_nb_bomb(player)>1)
			player_dec_nb_bomb(player);
		map_set_cell_type(map, x, y, CELL_EMPTY);
		return 1;
		break;
	case BONUS_BOMB_NB_INC:
		player_inc_nb_bomb(player);
		map_set_cell_type(map, x, y, CELL_EMPTY);
		return 1;
		break;
	case BONUS_LIFE:
		player_inc_life(player);
		map_set_cell_type(map, x, y, CELL_EMPTY);
		return 1;
		break;
	case BONUS_LIFE_DEC:
		player_dec_life(player);
		map_set_cell_type(map, x, y, CELL_EMPTY);
		return 1;
		break;
	case BONUS_PUSH: //Pass through box, state player = 3
		player_set_state(player,1);
		player_set_timer(player,SDL_GetTicks());
		map_set_cell_type(map, x, y, CELL_EMPTY);
		return 1;
		break;
	case BONUS_DEAD: //Inverse keyboard, state player = 2
		player_set_state(player,2);
		player_set_timer(player,SDL_GetTicks());
		map_set_cell_type(map, x, y, CELL_EMPTY);
		return 1;
		break;
	case BONUS_SHIELD: //Invulnerability, state player = 3
		player_set_state(player,3);
		player_set_timer(player,SDL_GetTicks());
		map_set_cell_type(map, x, y, CELL_EMPTY);
		return 1;
		break;
	default:
		break;
	}
	return 1;
}


int player_on_door(struct player* player, struct map* map, int x, int y)
// Door decision
{
	if (!map_open_door(map, x, y) && player->key==0){
		return 1;
	}
	if (!map_open_door(map, x, y) && player->key>0){
		map_open_a_door(map,x,y);
		player_dec_key(player);
		return 1;
	}

	else if (map_open_door(map, x, y)){ // door open (meaning it's impair)
		player_set_level_change(player,1);

	}
	return 1;

}


static int player_move_aux(struct player* player, struct map* map, int x, int y) {
	// Player movement decision
	if (!map_is_inside(map, x, y))
		return 0;

	switch (map_get_cell_type(map, x, y)) {

	case CELL_SCENERY:
		if (map_get_type(map,x,y) == CELL_PRINCESS)
			player_set_state(player,6);
		return 0;
		break;
	case CELL_BOX:
		if (player_get_state(player)==1)
			return 1;
		else
			return player_move_box(player, map, x, y);
		break;
	case CELL_BONUS:
		return player_bonus_effect(player, map, x, y);
		break;
	case CELL_DOOR:
		player_on_door(player, map, x, y);
		break;
	case CELL_MONSTER:
		player_dec_life(player);
		return 1;
		break;
	case CELL_BOMB:
		return 0;
		break;
	case CELL_FIRE:
		player_dec_life(player);
		return 1;
		break;
	case CELL_KEY:
		player_inc_key(player, map);
		map_set_cell_type(map, x, y, CELL_EMPTY);
		return 1;
		break;

	default:
		break;
	}

	// Player has moved
	return 1;
}

int player_move(struct player* player, struct map* map) {
	//Player movement x and y
	int x = player->x;
	int y = player->y;
	int move = 0;

	switch (player->current_direction) {
	case NORTH:
		if (player_move_aux(player, map, x, y - 1)) {
			player->y--;
			move = 1;
		}
		break;

	case SOUTH:
		if (player_move_aux(player, map, x, y + 1)) {
			player->y++;
			move = 1;
		}

		break;

	case WEST:
		if (player_move_aux(player, map, x - 1, y)) {
			player->x--;
			move = 1;
		}
		break;

	case EAST:
		if (player_move_aux(player, map, x + 1, y)){
			player->x++;
			move = 1;
		}
		break;
	}

	return move;
}

struct player* player_load(int x, int y, int map_level, int bomb_number,int key, int life, int bomb_range, int current_direction, int difficulty, int character, int state, int timer){
	//Initialising player after a save.

	struct player* player = malloc(sizeof(*player));
	if (!player)
		error("Memory error");

	player->x = x;
	player->y = y;
	player->nb_bombs = bomb_number;
	player->key = key;
	player->life = life;
	player->range = bomb_range;
	player->current_level = map_level;
	player->current_direction = current_direction;
	player->difficulty = difficulty;
	player->state=state;
	player->timer=timer;
	int m=0;
	for (m=0;m<8;m++)
		player->bombtimer[m]=0;
	player->bomb_position=0;
	player->character=character;

	return player;
}


