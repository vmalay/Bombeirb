#include <SDL/SDL_image.h>
#include <assert.h>
#include <player.h>
#include <map.h>
#include <constant.h>

struct monster{
	int x;
	int y;
	enum direction current_direction;
	int speed;  // speed of the monster (increased each level)
	int time;      // time spend in life (current time - birth_time)
	short life;  //number of monster's life
	int birth_time; // when he's spawning
	struct monster* next;

};


struct monster* monster_get_next(struct monster* monster){
	return monster->next;
}
//Get the current direction of a monster
int monster_get_current_direction(struct monster* monster){
	assert(monster);
	return	monster->current_direction;
}

//Set the current direction of a monster
void monster_set_current_direction(struct monster* monster, enum direction direction) {
	assert(monster);
	monster->current_direction = direction;
}

//Get the x position of a monster
int monster_get_x(struct monster* monster){
	assert(monster);
	return monster->x;
}

//Set the x position of a monster
int monster_get_y(struct monster* monster){
	assert(monster);
	return monster->y;
}

void monster_set_time(struct monster* monster,int time){
	assert(monster);
	int current_time = SDL_GetTicks();
	struct monster* current_monster = monster;
	while (current_monster != NULL){
		current_monster->time = current_monster->time + current_time - time;
		current_monster = current_monster->next;
	}
}

void monster_set_speed(struct monster* monster,int speed){
	assert(monster);
	struct monster* current_monster = monster;
	while (current_monster != NULL){
		current_monster->speed = speed;
		current_monster = current_monster->next;
	}
}

struct monster* monster_init(struct monster* monster, struct player* player, int x, int y) {
	// Initialisation of new monsters.
	struct monster* new_monster = malloc(sizeof(*monster));
	new_monster->x = x;
	new_monster->y = y;
	new_monster->current_direction = SOUTH; // Initially west side.
	new_monster->speed=1+0.8*player_get_current_level(player)*player_get_difficulty(player); // Higher is the current level, higher is the speed
	new_monster->time=SDL_GetTicks();
	new_monster->life=1;
	new_monster->next = NULL;
	new_monster->birth_time=SDL_GetTicks();
	if (monster==NULL) // No monster in the game.
		return new_monster;
	else{
		struct monster* tmp = monster;
		while (tmp->next != NULL)
			tmp=tmp->next;
		tmp->next=new_monster; // the monster is put at the end of chain
	}
	return monster;
}

//Check monster position in the map to initialize it
struct monster* monster_all_initiation(struct monster* monster, struct player* player, struct map* map) {
	assert(map);
	//check if the CELL on the map is a monster in order to create/initiate it.
	int i, j;
	for (i = 0; i < MAP_WIDTH; i++) {
		for (j = 0; j < MAP_HEIGHT; j++) {
			if (map_get_cell_type(map, i, j) == CELL_MONSTER) {
				monster=monster_init(monster, player,  i, j);
			}
		}
	}
	return monster;
}


void monster_dec_life(struct monster* monster, int x, int y){
	// x and y are the position of a CELL_FIRE
	struct monster* tmp = monster; // temporary pointer on *monster
	int current_time = SDL_GetTicks();
	// We look all the monster
	while (tmp != NULL){
		// The monster has to remain invincible for 2 sec so he can't be killed by the explosion
		int timer = current_time - tmp->birth_time;
		// If the monster is on a CELL_FIRE he dies
		if (tmp->x == x && tmp->y == y && (timer > 2000)){
			tmp->life -= 1;
		}
		tmp = tmp->next;
	}
}

struct monster* monster_delete(struct monster* monster){
	if(monster == NULL)
		return NULL;
	if(monster->life == 0){ //Delete the element but keep the address of the next element in a temporary pointer
		struct monster* tmp = monster->next;
		free(monster);
		tmp = monster_delete(tmp); 		// Now the list begins with the next element
		return tmp;
	}
	else{ // If the monster is okay, check for the next elements
		monster->next = monster_delete(monster->next);
		return monster;
	}
}

int monster_move_aux(struct monster* monster, struct map* map, int x, int y) {
	if (!map_is_inside(map, x, y))
		return 0;
	//Check the next case case and allow the movement depending on the Cell-type.

	switch (map_get_cell_type(map, x, y)) {
	case CELL_SCENERY:
		return 0;
		break;

	case CELL_BOX:
		return 0;
		break;

	case CELL_BONUS:
		return 0;
		break;

	case CELL_DOOR:
		return 0;
		break;

	case CELL_KEY:
		return 0;
		break;

	case CELL_FIRE:
		return 1;
		break;

	case CELL_BOMB:
		return 0;
		break;

	case CELL_MONSTER:
		return 0;
		break;
	default:
		break;
	}

	//Monster are afraid of door, they can't approach door (by 2 cases)
	if (    (map_is_inside(map, x, y-1) && map_get_cell_type(map, x, y-1)== CELL_DOOR) ||
			(map_is_inside(map, x, y+1) && map_get_cell_type(map, x, y+1)==CELL_DOOR)||
			(map_is_inside(map, x-1, y) && map_get_cell_type(map, x-1, y)==CELL_DOOR) ||
			(map_is_inside(map, x+1, y) && map_get_cell_type(map, x+1, y)==CELL_DOOR )){
		return 0;
	}


	// Monster has moved
	return 1;
}


//Intelligent movement of monster, they can turn away from boxes
int better_move(struct monster* monster, struct map* map, struct player* player){ //Fares
	int x,y,x1,y1,dist,dist1;
	x = monster_get_x(monster);
	y = monster_get_y(monster);
	x1 = player_get_x(player);
	y1 = player_get_y(player);
	dist = abs(x-x1);
	dist1 = abs(y-y1);
	//Check next case to anticipate the shifting
	if (x>0){
		if (dist!=0 && x1<x && map_get_type(map, x-1, y) == CELL_EMPTY){
			if (dist<dist1){
				return 2;
			}
			if (dist1 == 0){
				return 2;
			}
			if (dist>dist1){
				if(y>0){
					if (map_get_type(map, x, y-1) != CELL_EMPTY && y>y1){
						return 2;
					}
				}
				if(y<11){
					if (map_get_type(map, x, y+1) != CELL_EMPTY && y<y1){
						return 2;
					}
				}
			}
		}
	}
	if(x<11){
		if (dist!=0 && x1>x && map_get_type(map, x+1, y) == CELL_EMPTY){
			if (dist<dist1){
				return 3;
			}
			if (dist>dist1){
				if(y>0){
					if (map_get_type(map, x, y-1) != CELL_EMPTY && y>y1){
						return 3;
					}
				}
				if (dist1 == 0){
					return 3;
				}
				if(y<11){
					if (map_get_type(map, x, y+1) != CELL_EMPTY && y<y1){
						return 3;
					}
				}
			}
		}
	}
	if(y<11){
		if (dist1!=0 && y1>y && map_get_type(map, x, y+1) == CELL_EMPTY){
			if (dist1<dist){
				return 1;
			}
			if (dist == 0){
				return 1;
			}
			if (dist1>dist){
				if(x>0){
					if ( map_get_type(map, x-1, y) != CELL_EMPTY && x>x1){
						return 1;
					}
				}
				if(x<11){
					if ( map_get_type(map, x+1, y) != CELL_EMPTY && x<x1){
						return 1;
					}
				}
			}
		}
	}
	if(y>0){
		if (dist1!=0 && y1<y && map_get_type(map, x, y-1) == CELL_EMPTY){
			if (dist1<dist){
				return 0;
			}
			if (dist == 0){
				return 0;
			}
			if (dist1>dist){
				if(x>0){
					if (map_get_type(map, x-1, y) != CELL_EMPTY && x>x1){
						return 0;
					}
				}
				if(x<11){
					if (map_get_type(map, x+1, y) != CELL_EMPTY && x<x1){
						return 0;
					}
				}
			}
		}
	}
	return rand()%4; // random number for the random direction of the monsters when there's no other choice.
}

//Shifting of the monster thanks to the previous function
int monster_move(struct monster* monster, struct map* map, struct player* player) {
	int x = monster->x;
	int y = monster->y;
	int type = map_get_type(map, x, y);
	int move = 0;
	int current_time = SDL_GetTicks();
	int timer = (current_time - (monster->time))*(monster->speed);// coefficient to make the monster quicker than before

	if (timer>3000){
		monster->current_direction = better_move(monster, map, player);
		switch (monster->current_direction) {
		case NORTH:
			if (monster_move_aux(monster, map, x, y - 1)) {
				map_set_cell_type(map, x, y , CELL_EMPTY);
				monster->y--;
				move = 1;
				monster->time=SDL_GetTicks();
				if (player_get_x(player) == x && player_get_y(player) == y){
					player_dec_life(player);
				}
				break;
			}
			break;

		case SOUTH:
			if (monster_move_aux(monster, map, x, y + 1)) {
				map_set_cell_type(map, x, y , CELL_EMPTY);
				monster->y++;
				move = 1;
				monster->time=SDL_GetTicks();
				if (player_get_x(player) == x && player_get_y(player) == y)
					player_dec_life(player);
				break;
			}
			break;

		case WEST:
			if (monster_move_aux(monster, map, x - 1, y)) {
				map_set_cell_type(map, x, y , CELL_EMPTY);
				monster->x--;
				move = 1;
				monster->time=SDL_GetTicks();
				if (player_get_x(player) == x && player_get_y(player) == y)
					player_dec_life(player);
				break;
			}
			break;

		case EAST:
			if (monster_move_aux(monster, map, x + 1, y)) {
				map_set_cell_type(map, x, y , CELL_EMPTY);
				monster->x++;
				move = 1;
				monster->time=SDL_GetTicks();
				if (player_get_x(player) == x && player_get_y(player) == y)
					player_dec_life(player);
				break;
			}
			break;

		}

	}
	//Set the map cell type: monster
	if (move) {
		map_set_type(map, monster->x, monster->y, type);
	}

	return move;

}



