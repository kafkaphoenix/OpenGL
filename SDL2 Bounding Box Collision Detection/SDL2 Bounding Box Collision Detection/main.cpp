#include <SDL.h>

int main(int argc, char **argv) 
{
	bool quit = false;
	SDL_Event event;
	int x = 288;
	int y = 208;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *window = SDL_CreateWindow("SDL2 Bounding Box Colliction Detection", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_Rect rect1 = { x, y, 100, 100 };
	SDL_Rect rect2 = { 50, 50, 100, 80 };

	while (!quit)
	{
		SDL_Delay(5);
		SDL_PollEvent(&event);

		switch (event.type)
		{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_LEFT: rect1.x--; break;
					case SDLK_RIGHT: rect1.x++; break;
					case SDLK_UP: rect1.y--; break;
					case SDLK_DOWN: rect1.y++; break;
					case SDLK_ESCAPE: quit = true; break;
				}
				break;
		}

		SDL_bool collision = SDL_HasIntersection(&rect1, &rect2);

		SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255);
		SDL_RenderClear(renderer);

		if (collision) {
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		}
		else {
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
		}
		SDL_RenderFillRect(renderer, &rect1);

		if (collision) {
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		}
		else {
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		}
		SDL_RenderFillRect(renderer, &rect2);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}