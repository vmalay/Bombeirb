#include <SDL/SDL_image.h>
#include <assert.h>

#include <player.h>
#include <constant.h>
#include <map.h>
#include <monster.h>
#include <bomb.h>
#include <sprite.h>
#include <window.h>

#define MIN(a,b) ((a) < (b) ? (a) : (b))

struct bomb{
	int bomb_x;
	int bomb_y;
	int birthtime; // time when the bomb is set
	int bomb_range;
	struct bomb *next;
	struct bomb *prev;
	int block[4]; // All direction of the bomb.
};


int bomb_get_x( struct bomb* bomb){
	assert(bomb);
	return bomb->bomb_x;
}

int bomb_get_y( struct bomb* bomb){
	assert(bomb);
	return bomb->bomb_y;
}

int bomb_get_range( struct bomb* bomb){
	assert(bomb);
	return bomb->bomb_range;
}

void bomb_set_range( struct bomb* bomb, int bomb_range){
	assert(bomb);
	bomb->bomb_range = bomb_range;
}

struct bomb* bomb_get_next( struct bomb* bomb){
	assert(bomb);
	return bomb->next;
}

void bomb_set_next( struct bomb* bomb){
	assert(bomb);
	bomb->next = NULL;
}

void bomb_set_prev( struct bomb* bomb){
	assert(bomb);
	bomb->prev = NULL;
}


void bomb_set_birthtime( struct bomb* bomb, int number){
	assert(bomb);
	bomb->birthtime = number;
}

int bomb_get_birthtime( struct bomb* bomb){
	assert(bomb);
	return bomb->birthtime;
}


//block position to the map
int bomb_block(int position){  // doit aller de 0 � 11.
	if(position<=0)
		position=0;
	else if (position>=MAP_WIDTH) // 12
		position=MAP_WIDTH-1;
	return position;
}

//set an additional bomb
struct bomb* bomb_init(struct player* player,struct map* map, struct bomb* game_bomb, int x, int y, int range, int birthtime){
	struct bomb* new_bomb = malloc(sizeof(*new_bomb));

	new_bomb->next=NULL;
	new_bomb->prev=NULL;
	new_bomb->bomb_x=x;
	new_bomb->bomb_y=y;
	new_bomb->birthtime=SDL_GetTicks();
	new_bomb->bomb_range = player_get_range(player);
	if (range !=0)
			new_bomb->bomb_range = range;
	if (birthtime !=0)
			new_bomb->birthtime=SDL_GetTicks()-birthtime+500; //+500 because of the pause image duration.
	// The new bomb is the first in the bomb list
	//new_bomb->next=game_bomb;

	if (game_bomb != NULL){
		//
		game_bomb->prev=new_bomb;
		new_bomb->next=game_bomb;
	}

	//map_set_cell_type(map, x, y, CELL_BOMB4);

	player_dec_nb_bomb(player);
	return new_bomb;

}


//Set a new bomb timer
void bomb_set_timer(struct bomb* bomb,int pause_time){
	int current_time = SDL_GetTicks();
	struct bomb* curent_bomb = bomb;
	while (curent_bomb != NULL){
		curent_bomb->birthtime = curent_bomb->birthtime + current_time - pause_time;
		curent_bomb = curent_bomb->next;
	}
}


void bomb_all(struct bomb* bomb, struct map* map, struct player* player, struct monster* monster){
	if(bomb != NULL) {
		struct bomb* curent_bomb = bomb;
		struct bomb* tmp = malloc(sizeof(*tmp));
		while (curent_bomb != NULL){
			int current_time = SDL_GetTicks();
			int x = bomb_get_x(curent_bomb);
			int y = bomb_get_y(curent_bomb);

			// We get the timer of the bomb
			int timer = (current_time - bomb_get_birthtime(curent_bomb));

			if (map_get_cell_type(map, x, y)==CELL_FIRE && timer < 2850)
				bomb_set_birthtime(curent_bomb,current_time-2850);


			// First bomb image
			if (0<timer && timer<700){
				map_set_type(map, x, y, CELL_BOMB4);
			}

			// Second bomb image
			else if (700<timer && timer<1400){
				map_set_type(map, x, y, CELL_BOMB3);
			}

			// Third bomb image
			else if (1400<timer && timer<2100){
				map_set_type(map, x, y, CELL_BOMB2);
			}

			// Four bomb image
			else if (2100<timer && timer<2900){
				map_set_type(map, x, y, CELL_BOMB1);

				// Blocks of every possibility of fire range
				if(2850<timer){
					curent_bomb->block[SOUTH]=bomb_block_fire(curent_bomb->bomb_range, map, x, y, SOUTH);  // South Blocks
					curent_bomb->block[NORTH]=bomb_block_fire(curent_bomb->bomb_range, map, x, y, NORTH);  // North Blocks
					curent_bomb->block[EAST]=bomb_block_fire(curent_bomb->bomb_range, map, x, y, EAST);    // East Blocks
					curent_bomb->block[WEST]=bomb_block_fire(curent_bomb->bomb_range, map, x, y, WEST);    // West Blocks

					bomb_bonus(curent_bomb->bomb_range, map, x, y,curent_bomb->block);

				}
			}
			else if (2900<timer && timer<3500){

				//Explosion begin
				map_set_type(map, x, y, CELL_FIRE);

				//Player take damage
				if (player_get_x(player) == x && player_get_y(player) == y)
						player_dec_life(player);;

				if(monster != NULL)
					//monster is on the bomb so he die.
					monster_dec_life(monster, x, y);

				bomb_fire(map, x, y, player, timer, monster, curent_bomb->block, curent_bomb->birthtime, curent_bomb->bomb_range);

			}
			else if (3500< timer && timer< 3600){
				bomb_off(curent_bomb->bomb_range,map,x,y);//end the explosion

				//Management of the bomb list
				if (curent_bomb->next == NULL && curent_bomb->prev != NULL){
					tmp = curent_bomb;
					(curent_bomb->prev)->next=NULL;
					free(tmp);
					//free(curent_bomb);
				}
			}

			curent_bomb = curent_bomb->next;

		}

	}
}



//Propagation of the bomb explosion
int bomb_block_fire(int bomb_range,struct map* map,int x, int y, enum direction direction){

	// Initialization block_at over >9 (bomb range) so it can't be [1,9]
	int block_at=10;
	x = bomb_block(x);
	y = bomb_block(y);
	if (direction == NORTH){
		for (int i=1; i<=bomb_range; i++){
			if (!map_is_inside(map, x, y-i)){
				return i-1;
			}
			else{
				if ((map_get_cell_type(map, x, y-i) == CELL_BOX) || (map_get_cell_type(map, x, y-i) == CELL_SCENERY) || (map_get_cell_type(map, x, y-i) == CELL_DOOR)){
					block_at = i;
					break;
				}
			}
		}
	}else if (direction == EAST){

		for (int j=1; j<=bomb_range; j++){
			if (!map_is_inside(map, x+j, y))
				return j-1;
			else{
				if ((map_get_cell_type(map, x+j, y) == CELL_BOX) || (map_get_cell_type(map, x+j, y) == CELL_SCENERY) || (map_get_cell_type(map, x+j, y) == CELL_DOOR)){
					block_at = j;
					break;
				}
			}
		}
	}else if (direction == SOUTH){

		for (int k=1 ; k<=bomb_range; k++){
			if (!map_is_inside(map, x, y+k))
				return k-1;
			else{
				if ((map_get_cell_type(map, x, y+k) == CELL_BOX) || (map_get_cell_type(map, x, y+k) == CELL_SCENERY) || (map_get_cell_type(map, x, y+k) == CELL_DOOR)){
					block_at = k;
					break;
				}
			}
		}
	}else if (direction == WEST){

		for (int l=1; l<=bomb_range; l++){
			if (!map_is_inside(map, x-l, y))
				return l-1;
			else {
				if ((map_get_cell_type(map, x-l, y) == CELL_BOX) || (map_get_cell_type(map, x-l, y) == CELL_SCENERY) || (map_get_cell_type(map, x-l, y) == CELL_DOOR)){
					block_at = l;
					break;
				}
			}
		}
	}
	return block_at;
}

//Set the bonus destruction
void bomb_bonus(int bomb_range, struct map* map, int x, int y, int block[4]){
	for (int j=0; j<=MIN(block[SOUTH],bomb_range); j++){
		if (map_get_cell_type(map, x, y+j) == CELL_BONUS)
			map_set_cell_type(map, x, y+j, CELL_EMPTY);
	}
	for (int j=0; j<=MIN(block[NORTH],bomb_range); j++){
		if (map_get_cell_type(map, x, y-j) == CELL_BONUS)
			map_set_cell_type(map, x, y-j, CELL_EMPTY);
	}
	for (int j=0; j<=MIN(block[EAST],bomb_range); j++){
		if (map_get_cell_type(map, x+j, y) == CELL_BONUS)
			map_set_cell_type(map, x+j, y, CELL_EMPTY);
	}
	for (int j=0; j<=MIN(block[WEST],bomb_range); j++){
		if (map_get_cell_type(map, x-j, y) == CELL_BONUS)
			map_set_cell_type(map, x-j, y, CELL_EMPTY);
	}
}



void bomb_fire(struct map* map, int x, int y, struct player* player, int timer, struct monster* monster,int block[4], int birthtime, int bomb_range){


	//Manage the range of the explosion, MIN is used in order to stop the fire directly when he meets an obstacle.
	//Example: range=3 >>> EMPTY / STONE / BOMB if it's not minimum the first cell empty would be in fire.

	//For all the case on the top line (NORTH)
	for (int i=1; i<=MIN(block[SOUTH],bomb_range); i++){
		bomb_fire_xy(birthtime, map, x, y+i, player,monster);
	}
	//For all the case on the bottom line (SOUTH)
	for (int i=1; i<=MIN(block[NORTH],bomb_range); i++){
		bomb_fire_xy(birthtime, map, x, y-i, player,monster);
	}
	//For all the case on the right line (EAST)
	for (int i=1; i<=MIN(block[EAST],bomb_range); i++){
		bomb_fire_xy(birthtime, map, x+i, y, player,monster);
	}
	//For all the case on the left line (WEST)
	for (int i=1; i<=MIN(block[WEST],bomb_range); i++){
		bomb_fire_xy(birthtime, map, x-i, y, player,monster);
	}
}

//Set the fire in position xy which kill monster/hurt player or destroy bonus or boxes
void bomb_fire_xy(int birthtime, struct map* map, int x, int y, struct player* player, struct monster* monster){
	int type = map_get_cell_type(map, x, y);
	int current_time;
	// position of block
	x = bomb_block(x);
	y = bomb_block(y);

	//the fire is killing the monster
	if(monster != NULL)
		monster_dec_life(monster, x, y);

	//the fire is hurting the player
	if (player_get_x(player) == x && player_get_y(player) == y){
		current_time = SDL_GetTicks();
		//It has to correspond with the time of the apparition of the fire (here it's [2900, 3500])
		if(current_time - birthtime - 2900 < 100)
				player_dec_life(player);

	}
	switch(type){
	case CELL_EMPTY:
		current_time = SDL_GetTicks();
		// we display the fire on a cell empty
		if(current_time - birthtime - 2900 < 100){
			map_set_cell_type(map, x, y, CELL_FIRE);
		}
		break;

	case CELL_BOMB:
		current_time = SDL_GetTicks();
		// we display the fire on a cell empty
		if(current_time - birthtime - 2900 < 100){
			map_set_cell_type(map, x, y, CELL_FIRE);
		}
		break;


	case CELL_MONSTER:
		current_time = SDL_GetTicks();
		// we display the fire on a monster
		if(current_time - birthtime - 2900 < 100){
			map_set_cell_type(map, x, y, CELL_FIRE);
		}
		break;

	case CELL_BOX:
		// we display the bonus of the box (an empty box is a box with a bonus empty)

		// if the bonus is a monster (no luck !)

		if (map_get_sub_type(map, x, y) > 0) {
			map_set_type(map, x, y, CELL_BONUS | map_get_sub_type(map, x, y));

		}
		else if (map_get_sub_type(map, x, y) == CELL_BOX_MONSTER)
			monster_init(monster, player, x, y);
		else
			map_set_cell_type(map,x, y, CELL_FIRE);


		break;

	default:
		break;
	}
}


//Set the Cell empty when the fire is done
void bomb_off(int bomb_range, struct map* map, int x, int y){
	for (int i=0; i<=bomb_range; i++){
		// we have to not exceed the map length/width when we use "map_get_cell_type".
		if (map_is_inside(map, x, y+i))
			if ((map_get_cell_type(map, x, y+i) == CELL_FIRE) || (map_get_cell_type(map, x, y+i) == CELL_MONSTER))
				map_set_cell_type(map, x, y+i, CELL_EMPTY);
		if (map_is_inside(map, x, y-i))
			if ((map_get_cell_type(map, x, y-i) == CELL_FIRE) || (map_get_cell_type(map, x, y-i) == CELL_MONSTER))
				map_set_cell_type(map, x, y-i, CELL_EMPTY);
		if (map_is_inside(map, x+i, y))
			if ((map_get_cell_type(map, x+i, y) == CELL_FIRE) || (map_get_cell_type(map, x+i, y) == CELL_MONSTER))
				map_set_cell_type(map, x+i, y, CELL_EMPTY);
		if (map_is_inside(map, x-i, y))
			if ((map_get_cell_type(map, x-i, y) == CELL_FIRE) || (map_get_cell_type(map, x-i, y) == CELL_MONSTER))
				map_set_cell_type(map, x-i, y, CELL_EMPTY);

	}

}
