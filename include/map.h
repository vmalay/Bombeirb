/*******************************************************************************
 * This file is part of Bombeirb.
 * Copyright (C) 2018 by Laurent Reveillere
 ******************************************************************************/
#ifndef MAP_H_
#define MAP_H_

struct map;
struct player;
enum cell_type {
	CELL_EMPTY=0x00,   		//  0000 0000
	CELL_SCENERY=0x10, 		//  0001 0000
	CELL_BOX=0x20,   		//  0010 0000
	CELL_DOOR=0x30,      	//  0011 0000
	CELL_KEY=0x40,       	//  0100 0000
	CELL_BONUS=0x50, 		// 	0101 0000
	CELL_MONSTER=0x60, 		// 	0110 0000
	CELL_BOMB=0x70, 	   	// 	0111 0000
	CELL_FIRE=0x80,		    //  1000 0000
};

enum bonus_type {
	BONUS_EMPTY=0,
	BONUS_BOMB_RANGE_DEC,
	BONUS_BOMB_RANGE_INC,
	BONUS_BOMB_NB_DEC,
	BONUS_BOMB_NB_INC,
	BONUS_MONSTER,
	BONUS_LIFE,
	BONUS_LIFE_DEC,
	BONUS_DEAD,
	BONUS_PUSH,
	BONUS_SHIELD
};

enum scenery_type {
	SCENERY_STONE,     // 0000
	SCENERY_TREE,      // 0010
	SCENERY_PRINCESS,  // 0011
	SCENERY_BANANA,     // 0100
	SCENERY_SNOWMAN,     // 0101
	SCENERY_SNOWBLOCK,  // 0111
};

enum door_type {
	DOOR_CLOSE, // 0
	DOOR_OPEN, // 1
};

enum monster_type {
	MONSTER_GREEN, // 1
	MONSTER_RED,   // 2
	MONSTER_BLUE,  // 3
	MONSTER_BOSS,  // 4
};

enum compose_type {
	CELL_TREE     = CELL_SCENERY | SCENERY_TREE,
	CELL_STONE    = CELL_SCENERY | SCENERY_STONE,
	CELL_PRINCESS = CELL_SCENERY | SCENERY_PRINCESS,
	CELL_BANANA   = CELL_SCENERY | 	SCENERY_BANANA,
	CELL_SNOWMAN  = CELL_SCENERY | 	SCENERY_SNOWMAN,
	CELL_SNOWBLOCK  = CELL_SCENERY | 	SCENERY_SNOWBLOCK,

	CELL_BOX_EMPTY = CELL_BOX | BONUS_EMPTY,
	CELL_BOX_RANGEINC = CELL_BOX | BONUS_BOMB_RANGE_DEC,
	CELL_BOX_RANGEDEC = CELL_BOX | BONUS_BOMB_RANGE_INC,
	CELL_BOX_BOMBINC  = CELL_BOX | BONUS_BOMB_NB_DEC,
	CELL_BOX_BOMBDEC  = CELL_BOX | BONUS_BOMB_NB_INC,
	CELL_BOX_LIFE     = CELL_BOX | BONUS_LIFE,
	CELL_BOX_MONSTER  = CELL_BOX | BONUS_MONSTER,
};

enum bomb_state{
	STATE1, // 0000
	STATE2, // 0001
	STATE3, // 0010
	STATE4 // 0011
};

enum bomb_type {
	CELL_BOMB1 = CELL_BOMB | STATE1,  //0000 0111
	CELL_BOMB2 = CELL_BOMB | STATE2,  //0001 0111
	CELL_BOMB3 = CELL_BOMB | STATE3,  //0010 0111
	CELL_BOMB4 = CELL_BOMB | STATE4,  //0011 0111

};


struct map;

// Create a new empty map
struct map* map_new(int world);
void map_free(struct map* map);


// Return the height and width of a map
unsigned char* map_get_grid(struct map* map);

//
int map_get_world(struct map* map);
void map_set_world(struct map* map, int world);

// Return the type of a cell
enum cell_type map_get_cell_type(struct map* map, int x, int y);
int map_get_sub_type(struct map* map, int x, int y);
int map_get_type(struct map* map, int x, int y);

// Set the type of a cell
void  map_set_cell_type(struct map* map, int x, int y, enum cell_type type);
void  map_set_type(struct map* map, int x, int y, int type);

// Test if (x,y) is within the map
int map_is_inside(struct map* map, int x, int y);

// Display the map on the screen
void map_display(struct map* map, struct player* player);
void display_bonus(struct map* map, int x, int y, unsigned char type);
void display_door(int x, int  y, unsigned char type, int current_level);

// Take the map from a file. Mode is for temporary, normal or save folder.
struct map* map_get(int world, int N, int mode);

// Check if the door is open.
int map_open_door(struct map* map, int x, int y);

// Open a door
void map_open_a_door(struct map* map, int x, int y);

// Save the map in a file.

void map_save_temp(struct map* map, int current_level);
#endif /* MAP_H_ */
