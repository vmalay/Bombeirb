/*******************************************************************************
 * This file is part of Bombeirb.
 * Copyright (C) 2018 by Laurent Reveillere
 ******************************************************************************/
#include <SDL/SDL_image.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <player.h>
#include <map.h>
#include <constant.h>
#include <misc.h>
#include <sprite.h>
#include <window.h>
#include <monster.h>

struct map {
	unsigned char* grid;
	int world;
};

#define CELL(i,j) ( (i) + (j) * MAP_WIDTH)

struct map* map_new(int world)
{
	struct map* map = malloc(sizeof *map);
	if (map == NULL )
		error("map_new : malloc map failed");


	map->grid = malloc(MAP_HEIGHT * MAP_WIDTH);
	if (map->grid == NULL) {
		error("map_new : malloc grid failed");
	}

	// Grid cleaning
	int i, j;
	for (i = 0; i < MAP_WIDTH; i++)
		for (j = 0; j < MAP_HEIGHT; j++)
			map->grid[CELL(i,j)] = CELL_EMPTY;


	map->world=world;
	return map;
}

int map_is_inside(struct map* map, int x, int y)
{
	if ((y<0 || y>=MAP_HEIGHT) || (x<0 || x>=MAP_WIDTH))
		return 0;
	return 1;
}

int map_get_world(struct map* map)
{
	assert(map != NULL);
	return map->world;
}

void map_set_world(struct map* map, int world)
{
	assert(map != NULL);
	map->world=world;
}


unsigned char* map_get_grid(struct map* map)
{
	assert(map);
	return map->grid;
}

void map_free(struct map *map)
{
	if (map == NULL )
		return;
	free(map_get_grid(map));
	free(map);
}

enum cell_type map_get_cell_type(struct map* map, int x, int y)
{
	assert(map && map_is_inside(map, x, y));
	return map->grid[CELL(x,y)] & 0xf0;
}

int map_get_sub_type(struct map* map, int x, int y)
{
	assert(map && map_is_inside(map, x, y));
	return map->grid[CELL(x,y)] & 0x0f;
}

int map_get_type(struct map* map, int x, int y)
{
	assert(map && map_is_inside(map, x, y));
	return map->grid[CELL(x,y)];
}

void  map_set_cell_type(struct map* map, int x, int y, enum cell_type type)
{
	assert(map && map_is_inside(map, x, y));
	map->grid[CELL(x,y)] = type;
}

void  map_set_type(struct map* map, int x, int y, int type)
{
	assert(map && map_is_inside(map, x, y));
	map->grid[CELL(x,y)] = type;
}

void map_open_a_door(struct map* map, int x, int y)
{
	assert(map && map_is_inside(map, x, y));
	map->grid[CELL(x,y)]++;
}



void display_bonus(struct map* map, int x, int y, unsigned char type)
{
	// bonus is encoded with the 4 most significant bits

	switch (type & 0x0f) {
	case BONUS_BOMB_RANGE_INC:
		window_display_image(sprite_get_bonus(BONUS_BOMB_RANGE_INC), x, y);
		break;

	case BONUS_BOMB_RANGE_DEC:
		window_display_image(sprite_get_bonus(BONUS_BOMB_RANGE_DEC), x, y);
		break;

	case BONUS_BOMB_NB_DEC:
		window_display_image(sprite_get_bonus(BONUS_BOMB_NB_DEC), x, y);
		break;

	case BONUS_BOMB_NB_INC:
		window_display_image(sprite_get_bonus(BONUS_BOMB_NB_INC), x, y);
		break;

	case BONUS_MONSTER:
		window_display_image(sprite_get_monster(SOUTH,map_get_world(map),0), x, y);
		break;

	case BONUS_LIFE:
		window_display_image(sprite_get_bonus(BONUS_LIFE), x, y);
		break;

		// New bonus: decrease a life (image: a black hearth)

	case BONUS_LIFE_DEC:
		window_display_image(sprite_get_bonus(BONUS_LIFE_DEC), x, y);
		break;

		// Random movement during 5s.

	case BONUS_DEAD:
		window_display_image(sprite_get_bonus(BONUS_DEAD), x, y);
		break;

	case BONUS_PUSH:
		window_display_image(sprite_get_bonus(BONUS_PUSH), x, y);
		break;

	case BONUS_SHIELD:
		window_display_image(sprite_get_bonus(BONUS_SHIELD), x, y);
		break;
	}
}

void display_scenery(struct map* map, int x, int  y, unsigned char type)
{
	switch (type & 0x0f) { // avoir les bits de poids faibles.
	case SCENERY_STONE:
		window_display_image(sprite_get_stone(map_get_world(map)), x, y);
		break;

	case SCENERY_TREE:
		window_display_image(sprite_get_tree(map_get_world(map)), x, y);
		break;

	case SCENERY_PRINCESS:
		window_display_image(sprite_get_princess(), x, y);
		break;

	case SCENERY_BANANA:
		window_display_image(sprite_get_banana(), x, y);
		break;

	case SCENERY_SNOWMAN:
		window_display_image(sprite_get_snowman(), x, y);
		break;

	case SCENERY_SNOWBLOCK:
		window_display_image(sprite_get_snowblock(), x, y);
	}
}

void display_bomb(struct map* map, int x, int y,  unsigned char type){
	switch (type & 0x0f) {
	case STATE1:
		window_display_image(sprite_get_bomb(1), x, y);
		break;
	case STATE2:
		window_display_image(sprite_get_bomb(2), x, y);
		break;
	case STATE3:
		window_display_image(sprite_get_bomb(3), x, y);
		break;
	case STATE4:
		window_display_image(sprite_get_bomb(4), x, y);
		break;
	}

}

void display_door(int x, int  y, unsigned char type, int current_level)
{
	int level=type-48;
	if (47<type && type<64 && type%2==0)  // PAIR => CLOSE
		window_display_image(sprite_get_door_closed(), x, y);
	else if ((47<type && type<64) && (level/2) == current_level )  // If you want to go to the next map level.)   // IMPAIR => OPEN
		window_display_image(sprite_get_door_opened(2), x, y);

	else if ((47<type && type<64) && (level/2) != current_level )
		window_display_image(sprite_get_door_opened(1), x, y);
}


void map_display(struct map* map, struct player* player)
{
	assert(map != NULL);
	assert(MAP_HEIGHT > 0 && MAP_WIDTH > 0);
	int current_level=player_get_current_level(player);
	int x, y;
	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int j = 0; j < MAP_HEIGHT; j++) {
			x = i * SIZE_BLOC;
			y = j * SIZE_BLOC;

			unsigned char type = map->grid[CELL(i,j)];

			display_door(x, y, type, current_level);

			switch (type & 0xf0) {

			case CELL_SCENERY:
				display_scenery(map, x, y, type);
				break;
			case CELL_BOX:
				window_display_image(sprite_get_box(map_get_world(map)), x, y);
				break;
			case CELL_BONUS:
				display_bonus(map, x, y, type);
				break;
			case CELL_KEY:
				window_display_image(sprite_get_key(), x, y);
				break;
			case CELL_BOMB:
				display_bomb(map,x,y,type);
				break;
			case CELL_FIRE:
				window_display_image(sprite_get_fire(), x, y);
				break;
			case CELL_PRINCESS:
				window_display_image(sprite_get_princess(), x, y);
				break;
			}
		}
	}
}

struct map* map_get(int world, int N, int mode){
	//We charge the mapworld_N (example: map_1_2)
	FILE* fichier = NULL;
	char mapname[40];

	if (mode ==1) // Mode 1 is normal
		sprintf(mapname,"data/world%d/map_%d_%d",world, world, N);
	else if (mode==2) // Mode 2 is temporary map
		sprintf(mapname,"data/temp/map_%d_%d",world, N);
	else if (mode==3) // Mode 3 is saving map
		sprintf(mapname,"data/save/map_save");

	fichier = fopen(mapname, "r+");
	int width = MAP_WIDTH;
	int height = MAP_HEIGHT;
	//We get the width and the height from a file.
	fscanf(fichier, "%d:%d" , &width , &height);
	struct map* map = map_new(world);
	//struct map* map = malloc(sizeof *map);
	//We browse the file and each number are put in the map->grid
	int i, j , number;
	for (i = 0; i < width; i++){
		for (j = 0; j < height; j++){
			fscanf(fichier, "%d" , &number);
			map->grid[CELL(j,i)] = number;
		}
	}
	fclose(fichier);
	return map;
}

int map_open_door(struct map* map, int x, int y)
{
	int type = map->grid[CELL(x,y)];
	if (47<type && type<64 && type%2==0) // Pair = CLOSED
		return 0;
	else if (47<type && type<64) // Impair = OPENED
		return 1;
	return 0;
}

void map_save_temp(struct map* map, int current_level){

	FILE* fichier = NULL;

	int width = MAP_WIDTH;
	int height = MAP_HEIGHT;
	unsigned char* grid = map_get_grid(map); //Load the current state of the map


	int world=map_get_world(map);

	char tmp[500];
	sprintf(tmp,"data/temp/map_%d_%d", world, current_level);
	fichier = fopen(tmp, "w+");
	fprintf(fichier,"%d:%d \n", width, height);


	//Print each value of the map in the file
	int i, j , number;
	for (j = 0; j < height; j++){
		for (i = 0; i < width; i++){
			int N = i + j * width;
			if ( map_get_cell_type(map,i,j) == CELL_BOMB )
				grid [N] = CELL_EMPTY;
			if ( map_get_cell_type(map,i,j) == CELL_FIRE )
				grid [N] = CELL_EMPTY;
			number = grid[N] ;
			fprintf(fichier, "%d " , number);
		}
		fprintf(fichier, " \n");
	}

	fclose(fichier);
}



