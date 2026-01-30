#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>

const char *title = "Image Viewer";
const int pix_h = 1, pix_w = 1;

int main() {
	FILE *pfile = stdin;
	char *ptemp = calloc(1000, sizeof(char));
	// Read first line (specifier P3 or P6 - ignore here)
	fgets(ptemp, 1000, pfile);
	// Read second line (comment)
	//fgets(ptemp, 1000, pfile);
	free(ptemp);
	// Read third line (width height)
	char *pdimensions = calloc(1000, sizeof(char));
	fgets(pdimensions, 1000, pfile);
	
	int win_w = -1;
	int win_h = -1;
	sscanf(pdimensions, "%d %d\n", &win_w, &win_h);
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
	r = 0xB5;
	g = 0x7E;
	b = 0xDC;
	Uint32 colour = SDL_MapRGB(psurface->format, r, g, b);
	
	int x = 0, y = 0;
	SDL_Rect pixel = (SDL_Rect){x, y, pix_h, pix_w};
	for (int x = 0; x <= win_w; x++) {
		for (int y = 0; y <= win_h; y++) {
			pixel.x = x;
			pixel.y = y;
			SDL_FillRect(psurface, &pixel, colour);
		}
			if (x % 2 == 0) {
				SDL_UpdateWindowSurface(pwindow);
			}
	}


	//SDL_Delay(3000);

}
