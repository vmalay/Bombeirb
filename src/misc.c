/*******************************************************************************
 * This file is part of Bombeirb.
 * Copyright (C) 2018 by Laurent R
 ******************************************************************************/
#include <SDL/SDL_image.h> // IMG_Load
#include <misc.h>

void error(const char *s, ...) {
	va_list ap;
	va_start(ap, s);

	vfprintf(stderr, s, ap);
	va_end(ap);
	exit(EXIT_FAILURE);
}

SDL_Surface* load_image(const char* filename) {
	SDL_Surface* img = IMG_Load(filename);
	if (!img)
		error("IMG_Load: %s\n", IMG_GetError());

	return img;
}

