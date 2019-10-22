
/*******************************************************************************
 * This file is part of Bombeirb.
 * Copyright (C) 2018 by Laurent Reveillere
 ******************************************************************************/
#include <assert.h>
#include <time.h>

#include <game.h>
#include <misc.h>
#include <constant.h>
#include <window.h>
#include <sprite.h>
#include <player.h>
#include <map.h>
#include <bomb.h>
#include <monster.h>

struct game {
	struct map* maps;       // the game's map
	short multiplayer;
	short game_menu;    // menu when in game
	short system_menu;  // system menu when we launch the game
	short delay; // we save the time when we're on the menu or when the game is paused in order to have the time playing.
	struct player* player;
	struct player* player2;
	struct monster* monster;
	struct bomb* bomb;
};


struct game* game_new(void) {

	// We need a structure to enter inside the menu. But the attributes of this one are erase when we start the game (cf game_start)

	sprite_load(); // load sprite into process memory
	struct game* game = malloc(sizeof(*game));

	game->maps= map_get(1,0,1); // Difficulty/World 1 and level 0.
	game->multiplayer = 0;  // Normal mode.
	game->player = player_init(1,0,0);  // Initially set to NORMAL MODE with CHARACTER BOMBERMAN
	game->player2 = player_init(1,1,0);  // Initially set to NORMAL MODE with CHARACTER MARIO
	player_set_position(game->player, 0, 0); // Set default location of the player
	game->game_menu=-1;  // Initially set to -1 => NO IMAGE (it's the menu in game)
	game->system_menu=0; // Initially set to 0 => IMAGE  (it's the first menu when you open the game)
	game->monster = NULL; // No need to have monster when you're in the menu.
	game->bomb = NULL; // No need to have bomb when you're in the menu.
	game->delay = SDL_GetTicks();
	return game;
}

void game_start(struct game* game, int world) {
	//set new game
	if (game->multiplayer==1){ // Multiplayer Mode.
		game->maps= map_get(4,world,1);         // Map_4 is for multiplayer

		game->player = player_init(2, 0, player_get_score(game_get_player(game)) ); // Player 1
		player_set_position(game_get_player(game), 1, 0);
		player_set_score(game->player,player_get_score(game->player));
		player_set_state(game->player,0);

		game->player2 = player_init(2,1, player_get_score(game_get_player2(game)) );  // Player2
		player_set_position(game_get_player2(game), 10,11);
		player_set_score(game->player2,player_get_score(game->player2));
		player_set_state(game->player2,0);

		game->bomb = NULL;
	}
	else{ // Normal Mode
		game->maps = map_get(world,0,1);
		// Difficulty and Character Skin are already set in the system menu.
		game->player = player_init(player_get_difficulty(game_get_player(game)), player_get_character(game_get_player(game)),0);
		player_set_position(game_get_player(game), 1, 0);
		game->bomb = NULL;
		game->monster=monster_all_initiation(game->monster, game_get_player(game),game_get_current_map(game));
	}

	//No menu when in game.
	game->game_menu=-1;
	game->system_menu=-1;

	//everything that is before the beginning of the game is a delay.
	game->delay = SDL_GetTicks();

}

void game_free(struct game* game) {
	assert(game);
	//free the current map so it can be used in order to set the next map.
	player_free(game->player);
	player_free(game->player2);
	free(game->maps);

}

struct map* game_get_current_map(struct game* game) {
	assert(game);
	return game->maps;
}

struct bomb* game_get_bomb(struct game* game) {
	assert(game);
	return game->bomb;
}

struct monster* game_get_monster(struct game* game){
	assert(game);
	return game->monster;
}

void game_set_monster(struct game* game, struct monster* monster){
	assert(game);
	game->monster=monster;
}

struct player* game_get_player(struct game* game) {
	assert(game);
	return game->player;
}

struct player* game_get_player2(struct game* game) {
	assert(game);
	return game->player2;
}


void game_banner_display(struct game* game, int multiplayer) {

	// Banner position and background display.

	struct player* player = game_get_player(game);
	struct player* player2 = game_get_player2(game);

	int y = (MAP_HEIGHT) * SIZE_BLOC;
	for (int i = 0; i < MAP_WIDTH; i++)
		window_display_image(sprite_get_banner_line(), i * SIZE_BLOC, y);

	int white_bloc = ((MAP_WIDTH * SIZE_BLOC) - 11 * SIZE_BLOC) / 4;
	int x = white_bloc;

	y = (MAP_HEIGHT * SIZE_BLOC) + LINE_HEIGHT;


	if (multiplayer==0){

		// Banner for normal mode.

		window_display_image(sprite_get_banner_life(), x, y);

		int life=player_get_life(player);
		x = white_bloc + SIZE_BLOC;
		window_display_image(sprite_get_number(life), x, y);

		x = 2 * white_bloc + 2 * SIZE_BLOC;
		window_display_image(sprite_get_banner_bomb(), x, y);

		int nb_bomb=player_get_nb_bomb(player);
		x = 2 * white_bloc + 3 * SIZE_BLOC;
		window_display_image(sprite_get_number(nb_bomb), x, y);

		x = 3 * white_bloc + 4 * SIZE_BLOC;
		window_display_image(sprite_get_banner_range(), x, y);

		int nb_range=player_get_range(player);
		x = 3 * white_bloc + 5 * SIZE_BLOC;
		window_display_image(sprite_get_number(nb_range), x, y);

		x = 4 * white_bloc + 6 * SIZE_BLOC;
		window_display_image(sprite_get_key(), x, y);

		int nb_key=player_get_key(player);
		x = 4 * white_bloc + 7 * SIZE_BLOC;
		window_display_image(sprite_get_number(nb_key), x, y);

		x = 5 * white_bloc + 8 * SIZE_BLOC;
		window_display_image(sprite_get_door_opened(1), x, y);

		int nb_level=player_get_current_level(player);
		x = 5 * white_bloc + 9 * SIZE_BLOC;
		window_display_image(sprite_get_number(nb_level), x, y);
	}
	if (multiplayer==1){

		// Banner for multiplayer mode.

		int SIZE_BLOC2=SIZE_BLOC*0.85; // We have more icone to display so we have to reduce the size.

		window_display_image(sprite_get_banner_life(), x, y);

		int life=player_get_life(player);
		x = white_bloc + SIZE_BLOC2;
		window_display_image(sprite_get_number(life), x, y);

		x = 2 * white_bloc + 2 * SIZE_BLOC2;
		window_display_image(sprite_get_banner_bomb(), x, y);

		int nb_bomb=player_get_nb_bomb(player);
		x = 2 * white_bloc + 3 * SIZE_BLOC2;
		window_display_image(sprite_get_number(nb_bomb), x, y);

		x = 3 * white_bloc + 4 * SIZE_BLOC2;
		window_display_image(sprite_get_banner_range(), x, y);

		int nb_range=player_get_range(player);
		x = 3 * white_bloc + 5 * SIZE_BLOC2;
		window_display_image(sprite_get_number(nb_range), x, y);

		x = 4 * white_bloc + 6 * SIZE_BLOC2;
		window_display_image(sprite_get_banner_life(), x, y);

		int life2=player_get_life(player2);
		x = 4 * white_bloc + 7 * SIZE_BLOC2;
		window_display_image(sprite_get_number(life2), x, y);

		x = 5 * white_bloc + 8 * SIZE_BLOC2;
		window_display_image(sprite_get_banner_bomb(), x, y);

		int nb_bomb2=player_get_nb_bomb(player2);
		x = 5 * white_bloc + 9 * SIZE_BLOC2;
		window_display_image(sprite_get_number(nb_bomb2), x, y);

		x = 6 * white_bloc + 10 * SIZE_BLOC2;
		window_display_image(sprite_get_banner_range(), x, y);

		int nb_range2=player_get_range(player2);
		x = 6 * white_bloc + 11 * SIZE_BLOC2;
		window_display_image(sprite_get_number(nb_range2), x, y);


	}

}

void game_display_delay(int time_playing){
	// Display of the time. We have to display EACH NUMBER of the numbers
	// for example: "85.71" we have to display 1, then 7, then 5, then 8.
	// This function is use to show the record and the time during the end screen. (game_end function).
	int number1 = time_playing % 10;
	int number2 = (time_playing/10) % 10;
	int number3 = (time_playing/100) % 10;
	int number4= (time_playing/1000) % 10;
	int number5= (time_playing/10000) % 10;
	int number6= (time_playing/100000) % 10;
	if (number6 == 0){
		if (number5==0){
			window_display_image(sprite_get__number(number4),40*4,40*12);
			window_display_image(sprite_virgule(),40*5,40*12);
			window_display_image(sprite_get__number(number3),40*6,40*12);
			window_display_image(sprite_get__number(number2),40*7,40*12);
			window_display_image(sprite_get__number(number1),40*8,40*12);
		}
		else{
			window_display_image(sprite_get__number(number5),40*3,40*12);
			window_display_image(sprite_get__number(number4),40*4,40*12);
			window_display_image(sprite_virgule(),40*5,40*12);
			window_display_image(sprite_get__number(number3),40*6,40*12);
			window_display_image(sprite_get__number(number2),40*7,40*12);
			window_display_image(sprite_get__number(number1),40*8,40*12);
		}
	}
	else{
		window_display_image(sprite_get__number(number6),40*2,40*12);
		window_display_image(sprite_get__number(number5),40*3,40*12);
		window_display_image(sprite_get__number(number4),40*4,40*12);
		window_display_image(sprite_virgule(),40*5,40*12);
		window_display_image(sprite_get__number(number3),40*6,40*12);
		window_display_image(sprite_get__number(number2),40*7,40*12);
		window_display_image(sprite_get__number(number1),40*8,40*12);
	}
}
void game_display_record(int record){
	// Display of the record time. We have to display EACH NUMBER of the numbers
	// for example: "85.71" we have to display 1, then 7, then 5, then 8.
	// This function is use to show the record and the time during the end screen. (game_end function).
	int number1 = record % 10;
	int number2 = (record/10) % 10;
	int number3 = (record/100) % 10;
	int number4= (record/1000) % 10;
	int number5= (record/10000) % 10;
	int number6= (record/100000) % 10;
	if (number6 == 0){
		if (number5==0){
			window_display_image(sprite_get__number(number4),40*4,40*11);
			window_display_image(sprite_virgule(),40*5,40*11);
			window_display_image(sprite_get__number(number3),40*6,40*11);
			window_display_image(sprite_get__number(number2),40*7,40*11);
			window_display_image(sprite_get__number(number1),40*8,40*11);
		}
		else{
			window_display_image(sprite_get__number(number5),40*3,40*11);
			window_display_image(sprite_get__number(number4),40*4,40*11);
			window_display_image(sprite_virgule(),40*5,40*11);
			window_display_image(sprite_get__number(number3),40*6,40*11);
			window_display_image(sprite_get__number(number2),40*7,40*11);
			window_display_image(sprite_get__number(number1),40*8,40*11);
		}
	}
	else{
		window_display_image(sprite_get__number(number6),40*2,40*11);
		window_display_image(sprite_get__number(number5),40*3,40*11);
		window_display_image(sprite_get__number(number4),40*4,40*11);
		window_display_image(sprite_virgule(),40*5,40*11);
		window_display_image(sprite_get__number(number3),40*6,40*11);
		window_display_image(sprite_get__number(number2),40*7,40*11);
		window_display_image(sprite_get__number(number1),40*8,40*11);
	}
}

void game_record_and_end_display(struct game* game){
	FILE* fichier = NULL;
	int time_playing=SDL_GetTicks()-game->delay;
	int time_record=999999;
	fichier = fopen("data/save/record", "r+"); // Read the record in the file data/save/record
	if (fichier !=NULL){
		fscanf(fichier, "%d", &time_record);
		fclose(fichier);
	}
	if (time_playing < time_record){
		fichier = fopen("data/save/record", "w+"); // Save the record in the same file.
		if (fichier !=NULL){
			time_record=time_playing;
			fprintf(fichier,"%d\n",time_record);
			fclose(fichier);
		}
	}
	window_display_image(sprite_get_game_win(),0,0); // Display win image
	game_display_delay(time_playing);  // Display actual time
	game_display_record(time_record); // Display record time
	if (time_playing==time_record){
		window_display_image(sprite_record_victory(),40*2,40*5); // Display image "new record"
	}
	window_refresh();
	SDL_Delay(3000);
	game->delay=SDL_GetTicks();
}

void game_level_change(struct game* game){

	// This function deals with up/down level.

	//level_change is set to 1 when the player change the current level (when he pass on an open door or press SPACE)
	if (player_get_level_change(game->player) == 1){

		struct player* player = game_get_player(game);
		struct map* map = game_get_current_map(game);

		int level=map_get_type(map, player_get_x(player), player_get_y(player));

		level = level & 0x0e;
		level = level >>1; // Value: 1, 3, 5, etc.. corresponding to your current level (3 mean your current level is 2).

		map_save_temp(map,player_get_current_level(player)); // we temporary saved the map before loading the next map in /data/temp/

		// We set the new level of the player. Example: Player can go lv1 to lv7, lv7 to lv3, it depends on the number of the door.
		if (level == player_get_current_level(player))
			player_set_current_level(player, level+1);
		else
			player_set_current_level(player, level);
		int next_level=player_get_current_level(player);
		int world=map_get_world(game->maps);
		free(game->monster);
		free(game->bomb);
		game->monster=NULL;
		game->bomb=NULL;
		FILE* fichier = NULL;
		char tmp[500];
		int mode;
		sprintf(tmp,"data/temp/map_%d_%d", world,next_level);
		fichier = fopen(tmp, "r+");
		if (fichier == NULL)  // If it's your first time in this level, we have to load the normal save.
			mode=1;
		else                  // If you have already visited this level, we have to load from the temporary save.
			mode=2;

		fclose(fichier);
		game->maps=map_get(world,next_level, mode);
		//game->maps=map_get_temp(world,next_level);

		game->monster=monster_all_initiation(game->monster, player, game_get_current_map(game));
		player_set_level_change(player,0); //level_change is set to 0 he just pass the door and we don't want everything to reset again.
	}
}




void game_end(struct game* game){
	struct player* player = game_get_player(game);
	struct player* player2 = game_get_player2(game);
	/// Game Over
	if ((game->multiplayer == 0) & (player_get_life(player) == 0)){
		// Back to the menu
		player_inc_life(player);
		game->system_menu=0;
		player_set_state(player,3);
		game->monster=NULL;
		game->bomb=NULL;
		window_display_image(sprite_get_game_over(),0,0); // Display image of game over
		window_refresh();
		SDL_Delay(3000);
		game->multiplayer=0;
		map_set_world(game->maps,1);

	}

	/// Game Win and write record/time
	if (player_get_state(player) == 6){
		game->system_menu=0;  // Back to the menu
		player_set_state(player,0);
		game->monster=NULL;
		game->bomb=NULL;
		map_set_world(game->maps,1);
		game_record_and_end_display(game);


	}
	// Game win when we're in MULTIPLAYER mode.

	if (game->multiplayer==1){
		if (player_get_score(player2)+player_get_score(player) == 3){ //If score=3 (end of the game)
			if (player_get_score(player2)>player_get_score(player))
				window_display_image(sprite_get_player_win(1),0,0);
			else
				window_display_image(sprite_get_player_win(0),0,0);
			window_refresh();
			SDL_Delay(3000);
			game->multiplayer=0;
			game->game_menu=-1;
			game->system_menu=0;
			player_set_score(player2,0);
			player_set_score(player,0);
			player_set_difficulty(player,1);
			game->monster = NULL;
			game->bomb = NULL;
		}
		if (player_get_life(player) == 0){ // If player1 is dead.
			player_inc_life(player);
			player_inc_score(player2); // short key is used for the score of the player. (because it's useless in multiplayer mode)
			if (player_get_score(player2)+player_get_score(player) == 1){
				window_display_image(sprite_get_player_win(3),0,0);
				window_display_image(sprite_get__number(player_get_score(player)),40*4+20,40*8+12);
				window_display_image(sprite_get__number(player_get_score(player2)),40*4+20,40*9+17);
				window_refresh();
				SDL_Delay(2000);
				game_start(game,1);
				map_set_world(game->maps,2);
			}


			if  (player_get_score(player2)+player_get_score(player) == 2){ //If score < 3, then the game continue.
				window_display_image(sprite_get_player_win(3),0,0);
				window_display_image(sprite_get__number(player_get_score(player)),40*4+20,40*8+12);
				window_display_image(sprite_get__number(player_get_score(player2)),40*4+20,40*9+17);
				window_refresh();
				SDL_Delay(2000);
				game_start(game,2);
				map_set_world(game->maps,3);

			}
		}
		else if ( player_get_life(player2) == 0) { // If player2 is dead.
			player_inc_score(player);
			player_inc_life(player2);
			if (player_get_score(player2)+player_get_score(player) == 1){
				window_display_image(sprite_get_player_win(2),0,0);
				window_display_image(sprite_get__number(player_get_score(player)),40*9-5,40*8+8);
				window_display_image(sprite_get__number(player_get_score(player2)),40*9-5,40*9+12);
				window_refresh();
				SDL_Delay(2000);
				game_start(game,1);
				map_set_world(game->maps,2);
			}

			if (player_get_score(player2)+player_get_score(player) == 2){
				window_display_image(sprite_get_player_win(2),0,0);
				window_display_image(sprite_get__number(player_get_score(player)),40*9-5,40*8+8);
				window_display_image(sprite_get__number(player_get_score(player2)),40*9-5,40*9+12);
				window_refresh();
				SDL_Delay(2000);
				game_start(game, 2);
				map_set_world(game->maps,3);
			}

		}


	}
}

void game_player_state(struct game* game){
	// Function about state and bonus. The player has different states corresponding to different bonus.

	struct player* player = game_get_player(game);
	struct player* player2 = game_get_player2(game);

	//Bonus GHOST & Bonus INVINCIBLE & Malus SKULL.
	if (player_get_state(player) == 1 || player_get_state(player) == 2 || player_get_state(player) == 3 ){
		int timer= SDL_GetTicks()-player_get_timer(player);
		if (timer > 5000){
			player_set_state(player,0);
			player_set_timer(player,0);
		}
	}
	//Blinking Character (State=4 or 5 are used for blinking).
	if (player_get_state(player) == 4 || player_get_state(player) == 5){
		int timer =  SDL_GetTicks() -  player_get_timer(player);
		if ( 0 < timer && timer < 200 )
			player_set_state(player,5);
		else if ( 200 < timer && timer < 400 )
			player_set_state(player,4);
		else if ( 400 < timer && timer < 600 )
			player_set_state(player,5);
		else if ( 600 < timer && timer < 800 )
			player_set_state(player,4);
		else if ( 800 < timer && timer < 1000 )
			player_set_state(player,5);
		else if ( 1000 < timer && timer < 1200 )
			player_set_state(player,5);
		else if ( 1200 < timer && timer < 1400 )
			player_set_state(player,4);
		else if ( 1400 < timer && timer < 1600 )
			player_set_state(player,5);
		else if ( 1600 < timer && timer < 1800 )
			player_set_state(player,4);
		else if ( 1800 < timer && timer < 2000 )
			player_set_state(player,5);
		else if ( 2000 < timer && timer < 2200 )
			player_set_state(player,5);
		else if ( 2200 < timer && timer < 2400 )
			player_set_state(player,4);
		else if ( 2400 < timer && timer < 2600 )
			player_set_state(player,5);
		else if ( 2600 < timer && timer < 2800 )
			player_set_state(player,4);
		else if ( 2800 < timer && timer < 3000 )
			player_set_state(player,5);
		else if ( timer > 3000 )
			player_set_state(player,0);

	}

	if (game->multiplayer==1){
		//During multiplayer

		//Bonus GHOST & Bonus INVINCIBLE & Malus SKULL.
		if (player_get_state(player2) == 1 || player_get_state(player2) == 2 || player_get_state(player2) == 3 ){
			int timer= SDL_GetTicks()-player_get_timer(player2);
			if (timer > 6000){
				player_set_state(player2,0);
				player_set_timer(player2,0);
			}
		}
		//Blinking Character (State=4 or 5 are used for blinking).
		if (player_get_state(player2) == 4 || player_get_state(player2) == 5){
			int timer =  SDL_GetTicks() -  player_get_timer(player2);
			if ( 0 < timer && timer < 200 )
				player_set_state(player2,5);
			else if ( 200 < timer && timer < 400 )
				player_set_state(player2,4);
			else if ( 400 < timer && timer < 600 )
				player_set_state(player2,5);
			else if ( 600 < timer && timer < 800 )
				player_set_state(player2,4);
			else if ( 800 < timer && timer < 1000 )
				player_set_state(player2,5);
			else if ( 1000 < timer && timer < 1200 )
				player_set_state(player2,5);
			else if ( 1200 < timer && timer < 1400 )
				player_set_state(player2,4);
			else if ( 1400 < timer && timer < 1600 )
				player_set_state(player2,5);
			else if ( 1600 < timer && timer < 1800 )
				player_set_state(player2,4);
			else if ( 1800 < timer && timer < 2000 )
				player_set_state(player2,5);
			else if ( 2000 < timer && timer < 2200 )
				player_set_state(player2,5);
			else if ( 2200 < timer && timer < 2400 )
				player_set_state(player2,4);
			else if ( 2400 < timer && timer < 2600 )
				player_set_state(player2,5);
			else if ( 2600 < timer && timer < 2800 )
				player_set_state(player2,4);
			else if ( 2800 < timer && timer < 3000 )
				player_set_state(player2,5);
			else if ( timer > 3000 )
				player_set_state(player2,0);

		}
	}
}

void game_all(struct game* game){

	// This funcion is updating every structure (bomb, monster, player, state, map..) in the time.
	// When there's a modification, it's applied here.

	assert(game);


	struct map* map = game_get_current_map(game);
	struct player* player = game_get_player(game);
	//Background of the map
	window_display_image(sprite_get_fond(map_get_world(game_get_current_map(game))), 0, 0);

	//Prepare the next map,monster,bomb.
	game_level_change(game);
	game_player_state(game);
	game_end(game);

	//Set the next game
	bomb_all(game->bomb, game->maps, game->player, game->monster);

	//Bomb function for player2
	if (game->multiplayer==1)
		bomb_all(game->bomb, map, game->player2, game->monster);

	//Increase number of bomb by 1 when player is using a bomb. (it gives back the used bomb)
	for (int i=0; i<8; i++){
		int bombtimer=player_get_bombtimer(player, i);
		if (bombtimer != 0 && (SDL_GetTicks()-bombtimer) > 3500){
			player_inc_nb_bomb(player);
			player_set_bombtimer(player,i, 0);
		}
	}
	//Increase number of bomb by 1 when player2 is using a bomb. (it gives back the used bomb)
	if (game->multiplayer==1){
		for (int i=0; i<8; i++){
			int bombtimer2=player_get_bombtimer(game->player2, i);
			if (bombtimer2 != 0 && (SDL_GetTicks()-bombtimer2) > 3500){
				player_inc_nb_bomb(game->player2);
				player_set_bombtimer(game->player2,i, 0);
			}
		}
	}


	//The monster is save in a temporary pointer
	struct monster* tmp = game->monster;

	//All monsters are managed independently
	while(tmp!=NULL){
		monster_move(tmp, map, player);

		//Monster first apparition on a new case.
		int position=monster_get_current_direction(tmp);
		int world=map_get_world(map);
		int monster_type=map_get_sub_type(map,monster_get_x(tmp),monster_get_y(tmp));
		int type = map_get_type(map,monster_get_x(tmp),monster_get_y(tmp));

		//New monster position set
		map_set_type(map,monster_get_x(tmp),monster_get_y(tmp), type);

		//Display monster
		window_display_image(sprite_get_monster(position,world,monster_type), monster_get_x(tmp)*SIZE_BLOC, monster_get_y(tmp)*SIZE_BLOC);

		tmp = monster_get_next(tmp);
	}

	// If monster take damage, he's dead.
	game->monster = monster_delete(game->monster);
}

void game_display(struct game* game){
	assert(game);
	window_clear();
	struct player* player = game_get_player(game);
	game_all(game); //monster, bomb and bonus in box display
	game_banner_display(game,game->multiplayer); // banner display
	map_display(game_get_current_map(game), game_get_player(game)); //map display
	player_display(player);  //player display

	if (game->multiplayer==1){
		//player2 display
		player_display(game->player2);
	}
	if (game->game_menu != -1){
		// menu in game display
		window_display_image(sprite_get_menu(game->game_menu),0,0);
	}
	if (game->system_menu != -1){
		// system menu display
		window_display_image(sprite_get_system_menu(game->system_menu),0,0);
	}


	window_refresh();
}



int game_pause(){
	//Pause the game, everything stop because time is not increasing outside this function.
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_p:
				return 1;
				break;
			case SDLK_ESCAPE:
				return 1;
				break;
			default:
				break;
			}
			break;
		}
	}
	return 0;
}

void game_save(struct game* game){
	struct map* map = game_get_current_map(game);
	struct bomb* all_bomb = game_get_bomb(game);
	struct player* player = game_get_player(game);
	char tmp[100];
	int p=0;
	for (p=0; p<9; p++){
		sprintf(tmp,"data/save/bomb_save_%d",p);
		remove(tmp);
	}

	FILE* fichier = NULL;


	int k=0;
	int bomb_supp=0;
	while (all_bomb != NULL){
		char bomb_id[500];
		sprintf(bomb_id,"data/save/bomb_save_%d", k);

		fichier = fopen(bomb_id, "w+"); //Save the info of the game in the file "player_save"
		int bomb_x = bomb_get_x(all_bomb);
		int bomb_y = bomb_get_y(all_bomb);
		int birthtime = SDL_GetTicks()-bomb_get_birthtime(all_bomb);
		int bomb_range= bomb_get_range(all_bomb);
		fprintf(fichier,"%d\n",bomb_x);
		fprintf(fichier,"%d\n",bomb_y);
		fprintf(fichier,"%d\n",birthtime);
		fprintf(fichier,"%d\n",bomb_range);
		all_bomb = bomb_get_next(all_bomb);
		if (birthtime<3500)
			bomb_supp++;
		fclose(fichier);
		k++;

	}


	fichier = fopen("data/save/player_save", "w+"); //Save the info of the game in the file "player_save"

	int width = MAP_WIDTH;
	int height = MAP_HEIGHT;
	int world = map_get_world(map);
	unsigned char* grid = map_get_grid(map); //Load the current state of the map
	int map_level = player_get_current_level(player);
	int x = player_get_x(player);
	int y = player_get_y(player);
	int current_direction = player_get_current_direction(player);
	int nb_bomb = player_get_nb_bomb(player)+bomb_supp;
	int key = player_get_key(player);
	int life = player_get_life(player);
	int bomb_range = player_get_range(player);
	int difficulty = player_get_difficulty(player);
	int state = player_get_state(player);
	int character = player_get_character(player);
	int timer = player_get_timer(player);

	fprintf(fichier,"%d\n",map_level);
	fprintf(fichier,"%d\n",x);
	fprintf(fichier,"%d\n",y);
	fprintf(fichier,"%d\n",current_direction);
	fprintf(fichier,"%d\n",nb_bomb);
	fprintf(fichier,"%d\n",key);
	fprintf(fichier,"%d\n",life);
	fprintf(fichier,"%d\n",bomb_range);
	fprintf(fichier,"%d\n",world);
	fprintf(fichier,"%d\n",difficulty);
	fprintf(fichier,"%d\n",state);
	fprintf(fichier,"%d\n",character);
	fprintf(fichier,"%d\n",timer);
	fclose(fichier);



	fichier = fopen("data/save/map_save", "w+"); // Save the map in a different file (map_save)
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

void game_load(struct game* game){
	struct player* player = malloc(sizeof(player));
	struct map* map  = malloc(sizeof(map));
	if (game->bomb!=NULL)
		free(game->bomb);
	FILE* fichier = NULL;
	fichier = fopen("data/save/player_save", "r+"); // Load the file with all the game info

	if (fichier == NULL){
		window_display_image(sprite_get_system_menu(35),0,0);
		window_refresh();
		SDL_Delay(4000);
		game->system_menu=0;
	}

	else{

		int map_level;
		int x;
		int y;
		int current_direction;
		int nb_bomb;
		int key;
		int life;
		int bomb_range;
		int world;
		int difficulty;
		int state;
		int character;
		int timer;

		//Extract the data from the file
		fscanf(fichier,"%d",&map_level);
		fscanf(fichier,"%d",&x);
		fscanf(fichier,"%d",&y);
		fscanf(fichier,"%d",&current_direction);
		fscanf(fichier,"%d",&nb_bomb);
		fscanf(fichier,"%d",&key);
		fscanf(fichier,"%d",&life);
		fscanf(fichier,"%d",&bomb_range);
		fscanf(fichier,"%d",&world);
		fscanf(fichier,"%d",&difficulty);
		fscanf(fichier,"%d",&state);
		fscanf(fichier,"%d",&character);
		fscanf(fichier,"%d",&timer);

		fclose(fichier);

		//Load the map from a different file (map_save) with the ID=99
		game->player = player_load(x, y, map_level, nb_bomb ,key, life, bomb_range, current_direction, difficulty, character, state,  timer);
		map = map_get(world,1,3); //Mode 3 is for "saving"
		game->maps = map;
		game->monster = NULL;
		game->monster=monster_all_initiation(game->monster, player, game_get_current_map(game));
		monster_set_time(game->monster,SDL_GetTicks());
		monster_set_speed(game->monster,2);
		game->system_menu=-1;
		game->game_menu=-1;


		int k=0;
		struct bomb* prev_bomb=NULL;
		for (k=0; k<9; k++){
			char bomb_id[500];
			FILE* fichier2 = NULL;
			sprintf(bomb_id,"data/save/bomb_save_%d",k);
			fichier2 = fopen(bomb_id, "r+"); // Load the file with all the game info
			int bomb_x;
			int bomb_y;
			int birthtime;
			int bomb_range;
			if (fichier2 != NULL){

				//Extract the data from the file
				fscanf(fichier2,"%d",&bomb_x);
				fscanf(fichier2,"%d",&bomb_y);
				fscanf(fichier2,"%d",&birthtime);
				fscanf(fichier2,"%d",&bomb_range);
				fclose(fichier2);
				game->bomb=bomb_init(player,map,prev_bomb, bomb_x, bomb_y, bomb_range, birthtime);
				player_inc_nb_bomb(player);
				prev_bomb=game_get_bomb(game);
			}
			fclose(fichier2);
		}

	}

}


static short input_keyboard(struct game* game) {

	// Sytem Menu, In Game Menu, Movement, Bomb initialisation, Pause, Load, Save, Exit.

	SDL_Event event;
	struct player* player = game_get_player(game);
	struct player* player2 = game_get_player2(game);
	struct map* map = game_get_current_map(game);
	struct bomb* bomb = game_get_bomb(game);
	struct monster* monster = game_get_monster(game);
	int done=0;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			return 1;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_l:
				//Load a saved game
				if (game->multiplayer==0){ // Disabled in multiplayer
					if (game->system_menu ==-1){ // Disabled on menu.
						window_display_image(sprite_get_quickload(), 0, 0);
						window_refresh();
						SDL_Delay(800);
						game_load(game);
						int loading_time;
						loading_time = SDL_GetTicks();

						//We stop bomb-monster timers while doing the load.
						if (monster != NULL)
							monster_set_time(monster,loading_time);
						if (bomb != NULL)
							bomb_set_timer(bomb,loading_time);
						window_refresh();
					}
				}
				break;

			case SDLK_p:
				// Pause the game.
				if (game->multiplayer==0){ // Disabled in multiplayer
					if (game->system_menu ==-1){ // Disabled on menu.
						window_display_image(sprite_get_quickpause(), 0, 0);
						window_refresh();
						int timer=SDL_GetTicks();
						while(!done)
							done = game_pause();
						int pause_time;
						int pause_delay=SDL_GetTicks()-timer;
						game->delay=game->delay+pause_delay;
						pause_time = SDL_GetTicks();
						if (monster != NULL)
							monster_set_time(monster,pause_time);
						else
							game->monster=monster_all_initiation(game->monster, game_get_player(game),game_get_current_map(game));
						if (bomb != NULL)
							bomb_set_timer(bomb,pause_time);
						else
							game->bomb=NULL;
					}
				}
				break;

			case SDLK_a:
				//Save a game.
				if (game->multiplayer==0){ // Disabled in multiplayer
					if (game->system_menu ==-1){ // Disabled on menu.
						window_display_image(sprite_get_quicksave(), 0, 0);
						window_refresh();
						SDL_Delay(600);

						//We stop bomb-monster timers while doing the save.

						game_save(game);
						int saving_time;
						saving_time = SDL_GetTicks();
						if (monster != NULL)
							monster_set_time(monster,saving_time);
						else
							game->monster=monster_all_initiation(game->monster, game_get_player(game),game_get_current_map(game));
						if (bomb != NULL)
							bomb_set_timer(bomb,saving_time);
						else
							game->bomb=NULL;
					}
				}
				break;

			case SDLK_UP:
				//////// IN GAME MENU ///////
				if (game->game_menu !=-1 && game->system_menu == -1){ // In game menu is open
					if (game->game_menu==0) //menu position 0
						game->game_menu=3;
					else
						game->game_menu--;
				}

				else if (game->system_menu !=-1 && game->system_menu <= 4){  // System menu first page is open
					if (game->system_menu==0)
						game->system_menu=4;
					else
						game->system_menu--;
				}
				//////// START GAME MENU ///////
				else if (game->system_menu >4 && game->system_menu <= 9){   // System menu second page is open with world 1
					if (game->system_menu==6 || game->system_menu==5 )  // Button 1 to Button 4 for a loop
						game->system_menu=9;
					else
						game->system_menu--;
				}

				else if (game->system_menu >9 && game->system_menu <= 13 ){   // System menu second page is open with world 2
					if (game->system_menu==10)  // Button 1 to Button 4 for a loop
						game->system_menu=13;
					else
						game->system_menu--;
				}

				else if (game->system_menu >20 && game->system_menu <= 24 ){   // System menu second page is open with world 3
					if (game->system_menu==21)  // Button 1 to Button 4 for a loop
						game->system_menu=24;
					else
						game->system_menu--;
				}
				//////// OPTION MENU ///////
				else if (game->system_menu >13 && game->system_menu <=19){
					if (game->system_menu%2==0)
						game->system_menu++;
					else
						game->system_menu--;
				}

				//////// CHARACTER SELECTION MENU ///////

				else if (game->system_menu == 30)
					game->system_menu=27;
				else if (game->system_menu == 31)
					game->system_menu=28;
				else if (game->system_menu == 32)
					game->system_menu=29;
				else if (game->system_menu == 27)
					game->system_menu=30;
				else if (game->system_menu == 28)
					game->system_menu=31;
				else if (game->system_menu == 29)
					game->system_menu=32;
				else if (game->system_menu == 33)
					game->system_menu=34;
				else if (game->system_menu == 34)
					game->system_menu=33;



				/// PLAYER MOVEMENT ///
				else if (player_get_state(player) == 2) {
					player_set_current_direction(player, SOUTH);
					player_move(player, map);
				}


				else if (game->system_menu==-1 && game->game_menu==-1) {
					player_set_current_direction(player, NORTH);
					player_move(player, map);
				}

				break;
			case SDLK_DOWN:

				//////// IN GAME MENU ///////
				if (game->game_menu != -1 && game->system_menu == -1){ // In game menu is open
					if (game->game_menu==3)
						game->game_menu=0;
					else
						game->game_menu++;
				}
				//////// SYSTEM MENU ///////
				else if (game->system_menu != -1 && game->system_menu <= 4){ // System menu first page is open
					if (game->system_menu==4)
						game->system_menu=0;
					else
						game->system_menu++;
				}
				//////// START GAME MENU ///////
				else if (game->system_menu >4 && game->system_menu <= 9){   // System menu second page is open with world 1
					if (game->system_menu==9 || game->system_menu==5 )  // Button 4 to Button 1 for a loop
						game->system_menu=6;
					else
						game->system_menu++;
				}

				else if (game->system_menu >9 && game->system_menu <= 13 ){   // System menu second page is open with world 2
					if (game->system_menu==13)   // Button 4 to Button 1 for a loop
						game->system_menu=10;
					else
						game->system_menu++;
				}

				else if (game->system_menu >20 && game->system_menu <= 24 ){   // System menu second page is open with world 3
					if (game->system_menu==24)  // Button 4 to Button 1 for a loop
						game->system_menu=21;
					else
						game->system_menu++;
				}
				//////// OPTION MENU ///////
				else if (game->system_menu >13 && game->system_menu <=19){
					if (game->system_menu%2==0)
						game->system_menu++;
					else
						game->system_menu--;
				}
				//////// CHARACTER SELECTION MENU ///////
				else if (game->system_menu == 27)
					game->system_menu=30;
				else if (game->system_menu == 28)
					game->system_menu=31;
				else if (game->system_menu == 29)
					game->system_menu=32;
				else if (game->system_menu == 30)
					game->system_menu=27;
				else if (game->system_menu == 31)
					game->system_menu=28;
				else if (game->system_menu == 32)
					game->system_menu=29;
				else if (game->system_menu == 33)
					game->system_menu=34;
				else if (game->system_menu == 34)
					game->system_menu=33;

				/// PLAYER MOVEMENT ///

				else if (player_get_state(player) == 2) {
					player_set_current_direction(player, NORTH);
					player_move(player, map);
				}

				else if (game->system_menu==-1 && game->game_menu==-1) {
					player_set_current_direction(player, SOUTH);
					player_move(player, map);
				}
				break;
			case SDLK_RIGHT:
				/// START MENU --- Choose your World
				//  world1=7 => world2=11 => world3=22
				if (game->system_menu==7){
					game->system_menu=11;
					map_set_world(map,2);
				}

				else if (game->system_menu==11){
					game->system_menu=22;
					map_set_world(map,3);
				}

				else if (game->system_menu==22){
					game->system_menu=7;
					map_set_world(map,1);
				}

				/// OPTION MENU ---  Choose your Difficulty
				else if (game->system_menu == 18){
					game->system_menu = 14;
					player_set_difficulty(player,0);
				}
				else if (game->system_menu == 14){
					game->system_menu=16;
					player_set_difficulty(player,1);
				}
				else if (game->system_menu == 16){
					game->system_menu=18;
					player_set_difficulty(player,2);
				}

				/// CHARACTER MENU ---  Choose your character
				else if (game->system_menu == 33){
					game->system_menu=27;
					player_set_character(player,0);
				}
				else if (game->system_menu == 27){
					game->system_menu = 28;
					player_set_character(player,1);
				}
				else if (game->system_menu == 28){
					game->system_menu=29;
					player_set_character(player,2);
				}
				else if (game->system_menu == 29){
					game->system_menu=33;
					player_set_character(player,3);
				}


				///// PLAYER MOVEMENT ////

				else if (player_get_state(player) == 2) {
					player_set_current_direction(player, WEST);
					player_move(player, map);
				}

				else if (game->system_menu==-1 && game->game_menu==-1) {
					player_set_current_direction(player, EAST);
					player_move(player, map);
				}
				break;
			case SDLK_LEFT:
				/// START MENU --- Choose your World
				if (game->system_menu==7){
					game->system_menu=22;
					map_set_world(map,3);
				}
				else if (game->system_menu==22){
					game->system_menu=11;
					map_set_world(map,2);
				}

				else if (game->system_menu==11){
					game->system_menu=7;
					map_set_world(map,1);
				}


				/// OPTION MENU ---  Choose your Difficulty
				else if (game->system_menu == 14){
					game->system_menu=18;
					player_set_difficulty(player,2);
				}
				else if (game->system_menu == 18){
					game->system_menu = 16;
					player_set_difficulty(player,1);
				}
				else if (game->system_menu == 16){
					game->system_menu=14;
					player_set_difficulty(player,0);
				}

				// CHARACTER MENU --- Choose your character
				else if (game->system_menu == 33){
					game->system_menu=29;
					player_set_character(player,2);
				}
				else if (game->system_menu == 29){
					game->system_menu = 28;
					player_set_character(player,1);
				}
				else if (game->system_menu == 28){
					game->system_menu=27;
					player_set_character(player,0);
				}
				else if (game->system_menu == 27){
					game->system_menu=33;
					player_set_character(player,3);
				}



				/// Player movement


				else if (player_get_state(player) == 2) {
					// If player state=2 > malus sick (skull), inverse the keyboard.
					player_set_current_direction(player, EAST);
					player_move(player, map);
				}

				else if (game->system_menu==-1 && game->game_menu==-1) {
					player_set_current_direction(player, WEST);
					player_move(player, map);
				}
				break;
			case SDLK_SPACE:
				//Bomb Set
				if (map_get_type(map,player_get_x(player),player_get_y(player))==CELL_EMPTY && player_get_nb_bomb(player)>0 ){
					game->bomb=bomb_init(player,map,bomb, player_get_x(player), player_get_y(player),0,0);
					int time=SDL_GetTicks();
					int position=player_get_bomb_position(player);
					player_set_bombtimer(player,position,time); //Bomb timer
					player_inc_bomb_position(player);  //Bomb position in player1
				}
				if (map_open_door(map,player_get_x(player),player_get_y(player) ) ){
					player_set_level_change(player,1);

				}
				break;
			case SDLK_ESCAPE:
				//Game Menu
				if (game->system_menu == -1 || game->game_menu != -1)
					game->game_menu=0;
				game->monster = NULL;
				game->bomb = NULL;

				break;
			case SDLK_RETURN:

				//////////// IN GAME MENU //////////////////

				if (game->game_menu==0){ //Back to the system menu when you're in game.
					game->game_menu=-1;
					game->system_menu=0;
					game->multiplayer=0;
					game->monster = NULL;
					game->bomb = NULL;
					map_set_world(map,1);
					player_set_difficulty(player,1);


				}


				else if (game->game_menu==1){ //Continue
					game->game_menu=-1;
					game->monster=monster_all_initiation(game->monster, player,game_get_current_map(game));

				}
				else if (game->game_menu==2){ //Save
					if (game->multiplayer==0){
						game_save(game);
						window_display_image(sprite_get_saving(), 0, 0);
						window_refresh();
						SDL_Delay(3000);
						game->game_menu=0;
					}
				}
				else if (game->game_menu==3){ //Exit
					return 1;
				}

				//////////// SYSTEM MENU //////////////////

				else if (game->system_menu==0 ){ // Start game setup
					game->multiplayer=0;

					// Menu corresponding to the world choosen.
					if (map_get_world(map)==1)
						game->system_menu=6;
					if (map_get_world(map)==2)
						game->system_menu=10;
					if (map_get_world(map)==3)
						game->system_menu=21;
				}

				else if (game->system_menu==1){ //Multiplayer
					game->system_menu=-1;
					game->multiplayer=1;
					player=player_init(2,0,0);
					player2=player_init(2,0,0);
					player_set_score(game->player2,0);
					player_set_score(game->player,0);
					free(game->maps);
					game_start(game,0);
				}

				else if (game->system_menu==2){ //Options
					if (player_get_difficulty(player)==0)
						game->system_menu=14;
					if (player_get_difficulty(player)==1)
						game->system_menu=16;
					if (player_get_difficulty(player)==2)
						game->system_menu=18;

				}

				else if (game->system_menu==3){ //Exit
					return 1;
				}

				else if (game->system_menu==4){ //Credits
					game->system_menu=20;
				}

				else if (game->system_menu==20){ //Back (Credits)
					game->system_menu=0;
				}

				//////////// OPTIONS MENU ////////////

				else if (game->system_menu==15 || game->system_menu==17 || game->system_menu==19) // Back
					game->system_menu=2;


				////////// START GAME MENU //////////

				else if (game->system_menu==6 || game->system_menu==10 || game->system_menu==21){ // Character Menu
					game->system_menu=27;
				}

				else if (game->system_menu==8 || game->system_menu==12 || game->system_menu==23){     //Load Game
					if (game->multiplayer==0){
						window_refresh();
						SDL_Delay(400);
						game_load(game);
						int loading_time;
						loading_time = SDL_GetTicks();
						if (monster != NULL)
							monster_set_time(monster,loading_time);
						else
							game->monster=monster_all_initiation(game->monster, game_get_player(game),game_get_current_map(game));
						if (bomb != NULL)
							bomb_set_timer(bomb,loading_time);
						else
							game->bomb=NULL;
						window_refresh();
					}
				}

				else if (game->system_menu==9 || game->system_menu==13 || game->system_menu==24) { // Back
					game->system_menu=0;
				}

				//////////// CHARACTER SELECTION MENU ////////////

				else if (game->system_menu==30 || game->system_menu==31 || game->system_menu==32 || game->system_menu==34 ) // Back
					game->system_menu=6;

				else if (game->system_menu==7 || game->system_menu==11 || game->system_menu==22 || game->system_menu==27 || game->system_menu==28 || game->system_menu==29 || game->system_menu==33){ // New Game
					char tmp2[50];
					char tmp3[50];
					char tmp[50];
					int i=0;
					for (i=0; i<9; i++){
						sprintf(tmp,"data/temp/map_1_%d",i);
						remove(tmp);
						sprintf(tmp2,"data/temp/map_2_%d",i);
						remove(tmp2);
						sprintf(tmp3,"data/temp/map_3_%d",i);
						remove(tmp3);
					}
					free(game->maps);
					game->multiplayer=0;
					game_start(game,map_get_world(map));
					game->delay=SDL_GetTicks();
				}
				break;

				///// Same movement keyboard but for player2 /////

			case SDLK_z:

				if (player_get_state(player2) == 2) {
					player_set_current_direction(player2, SOUTH);
					player_move(player2, map);
				}
				else {
					player_set_current_direction(player2, NORTH);
					player_move(player2, map);
				}
				break;

			case SDLK_s:

				if (player_get_state(player2) == 2) {
					player_set_current_direction(player2,NORTH);
					player_move(player2, map);
				}

				else {
					player_set_current_direction(player2, SOUTH);
					player_move(player2, map);
				}
				break;

			case SDLK_q:

				if (player_get_state(player2) == 2) {
					player_set_current_direction(player2,EAST);
					player_move(player2, map);
				}

				else {
					player_set_current_direction(player2, WEST);
					player_move(player2, map);
				}
				break;

			case SDLK_d:

				if (player_get_state(player2) == 2) {
					player_set_current_direction(player2,WEST);
					player_move(player2, map);
				}

				else {
					player_set_current_direction(player2, EAST);
					player_move(player2, map);
				}

				break;

			case SDLK_x:
				if (map_get_cell_type(map,player_get_x(player2),player_get_y(player2))!=CELL_BOX && player_get_nb_bomb(player2)>0){
					game->bomb=bomb_init(player2,map,bomb, player_get_x(player2), player_get_y(player2),0,0);
					int time=SDL_GetTicks();
					int position=player_get_bomb_position(player2);
					player_set_bombtimer(player2,position,time);
					player_inc_bomb_position(player2);
				}
				break;

			default:
				break;
			}

			break;
		}
	}
	return 0;
}

int game_update(struct game* game) {
	if (input_keyboard(game))
		return 1; // exit game

	return 0;
}
