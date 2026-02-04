#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const char *title = "Image Viewer";
const int pix_h = 1, pix_w = 1;

void print_usage() {
	printf("Usage: ./sieve <filename>\n");
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("You must specify an image file.\n");
		print_usage();
		exit(1);
	}
	FILE *pfile = fopen(argv[1], "r");
	if (pfile == NULL) {
		printf("Unable to open file %s\n", argv[1]);
		print_usage();
		exit(1);
	}
	char *pline = calloc(1000, sizeof(char));
	char *pdimensions = calloc(1000, sizeof(char));
	int counter = 0;

	while (fgets(pline, 1000, pfile) != NULL) {
		// Ignore comments
		if (pline[0] == '#') {
			continue;
		}
		counter++;
		if (counter == 1) {
			// Read first line (specifier P3 or P6 - ignore here)
			printf("line %d: %s", counter, pline);
			continue;
		} else if (counter == 2) {
			// Read second line (width height)
			strcpy(pdimensions, pline);
			printf("dimensions: %s", pdimensions);
			continue;
		} else if (counter == 3) {
			// Read third line (max colour value - ignore for now)
			printf("line %d: %s", counter, pline);
			break;
		}
	}
	free(pline);

	int win_w = -1;
	int win_h = -1;
	sscanf(pdimensions, "%d %d\n", &win_w, &win_h);
	free(pdimensions);
	printf("w=%d\nh=%d\n", win_w, win_h);

  SDL_Window *pwindow = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		win_w,
		win_h,
		0
	);

	SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

	Uint8 r, g, b;
	int x = 0, y = 0;
	Uint32 colour = 0;
	
	SDL_Rect pixel = (SDL_Rect){x, y, pix_h, pix_w};
	for (int y = 0; y <= win_h; y++) {
		for (int x = 0; x <= win_w; x++) {
			r = fgetc(pfile);
			g = fgetc(pfile);
			b = fgetc(pfile);
			colour = SDL_MapRGB(psurface->format, r, g, b);
			pixel.x = x;
			pixel.y = y;
			SDL_FillRect(psurface, &pixel, colour);
		}
	}
		
	SDL_UpdateWindowSurface(pwindow);

	bool app_running = true;
	while (app_running) {
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type) {
				case SDL_QUIT:
					app_running = false;
					break;
				default:
					SDL_Delay(10);
			}
		}
	}
}
