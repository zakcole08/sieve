#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const char *title = "Sieve - Image Viewer";
const int pix_h = 1, pix_w = 1;
int win_w, win_h;
int x, y;
FILE *pfile;
SDL_Surface *psurface;
SDL_Window *pwindow;
Uint8 r, g, b;
Uint32 colour = 0;

void print_usage() {
	printf("Usage: ./sieve <filename>\n");
}

void draw_p3() {
	
	SDL_Rect pixel = (SDL_Rect){x, y, pix_h, pix_w};
	for (int y = 0; y < win_h; y++) {
		for (int x = 0; x < win_w; x++) {			
			fscanf(pfile, "%hhd %hhd %hhd", &r, &g, &b);
			colour = SDL_MapRGB(psurface->format, r, g, b);
			pixel.x = x;
			pixel.y = y;
			SDL_FillRect(psurface, &pixel, colour);
		}
	}
}

void draw_p6() {
	SDL_Rect pixel = (SDL_Rect){x, y, pix_h, pix_w};
	for (int y = 0; y < win_h; y++) {
		for (int x = 0; x < win_w; x++) {
			r = fgetc(pfile);
			g = fgetc(pfile);
			b = fgetc(pfile);
			colour = SDL_MapRGB(psurface->format, r, g, b);
			pixel.x = x;
			pixel.y = y;
			SDL_FillRect(psurface, &pixel, colour);
		}
	}
}

void launch_window(FILE *pfile) {
	char *pline = calloc(1000, sizeof(char));
	char *pdimensions = calloc(1000, sizeof(char));
	int counter = 0;
	char format[4];

	while (fgets(pline, 1000, pfile) != NULL) {
		// Ignore comments
		if (pline[0] == '#') {
			continue;
		}
		counter++;
		if (counter == 1) {
			// Read first line (specifier P3 or P6)
			strcpy(format, pline);
			printf("line %d: %s", counter, format);
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

	sscanf(pdimensions, "%d %d\n", &win_w, &win_h);
	free(pdimensions);
	printf("w=%d\nh=%d\n", win_w, win_h);

	format[strcspn(format, " \t\r\n")] = '\0';

	pwindow = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		win_w,
		win_h,
		0
	);

	psurface = SDL_GetWindowSurface(pwindow);
	if (strcmp(format, "P3") == 0) {
		draw_p3();
	} else if (strcmp(format, "P6") == 0) {
		draw_p6();
	} else {
		printf("PPM: Invalid format specificer\n");
		exit(1);
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

void launch_home(int win_w, int win_h) {	
	pwindow = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		win_w,
		win_h,
		0
	);
	psurface = SDL_GetWindowSurface(pwindow);

	Uint8 rmin, rmax, gmin, gmax, bmin, bmax;
	r = (Uint8) rand();
	g = (Uint8) rand();
	b = (Uint8) rand();
	SDL_Rect pixel = (SDL_Rect){x, y, pix_h, pix_w};
	for (int y = 0; y < win_h; y++) {
		for (int x = 0; x < win_w; x++) {			
			rmin = r - 1;
			rmax = r + 1;
			gmin = g - 1;
			gmax = g + 1;
			bmin = b - 1;
			bmax = b + 1;
			r = rand() % (rmax - rmin + 1) + rmin;
			g = rand() % (gmax - gmin + 1) + gmin;
			b = rand() % (bmax - bmin + 1) + bmin;
			colour = SDL_MapRGB(psurface->format, r, g, b);
			pixel.x = x;
			pixel.y = y;
			SDL_FillRect(psurface, &pixel, colour);
		}
	}

	SDL_UpdateWindowSurface(pwindow);
	
	SDL_Event event;
	SDL_EventState(SDL_DROPFILE, SDL_ENABLE);

	while (true) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					SDL_DestroyWindow(pwindow);
					exit(0);

				case SDL_DROPFILE:
					pfile = fopen(event.drop.file, "r");
					SDL_free(event.drop.file);

					SDL_DestroyWindow(pwindow);
					launch_window(pfile);
					break;
				default:
					break;
			}
		}
	}
}

int main(int argc, char *argv[]) {
	if (argc > 1) {
		pfile = fopen(argv[1], "r");
		if (!pfile) {
			printf("Unable to open file %s\n", argv[1]);
			print_usage();
			return 1;
		}
	} else {
		win_w = 1200;
		win_h = 800;
		launch_home(win_w, win_h);
	}
	launch_window(pfile);
}

