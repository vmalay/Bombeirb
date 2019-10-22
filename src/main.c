/*******************************************************************************
 * This file is part of Bombeirb.
 * Copyright (C) 2018 by Laurent Reveillere
 ******************************************************************************/
#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <constant.h>
#include <game.h>
#include <window.h>
#include <misc.h>

int main(int argc, char *argv[]) {



	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		error("Can't init SDL:  %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	//clean tmp files
	//system("rm -R data/temp/*");


	struct game* game = game_new();
	int MAP_WIDTH1=12;
	int MAP_HEIGHT1=12;
	window_create(SIZE_BLOC * MAP_WIDTH1, SIZE_BLOC * MAP_HEIGHT1 + BANNER_HEIGHT + LINE_HEIGHT);

	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

	// to obtain the DEFAULT_GAME_FPS, we have to reach a loop duration of (1000 / DEFAULT_GAME_FPS) ms
	int ideal_speed = 1000 / DEFAULT_GAME_FPS;
	int timer, execution_speed;
	// game loop, static time rate implementation
	int done = 0;
	while (!done) {
		timer = SDL_GetTicks();

		done = game_update(game);
		game_display(game);

		execution_speed = SDL_GetTicks() - timer;
		if (execution_speed < ideal_speed)
			SDL_Delay(ideal_speed - execution_speed); // we are ahead of ideal time. let's wait.
	}

	game_free(game);

	SDL_Quit();

	return EXIT_SUCCESS;
}
