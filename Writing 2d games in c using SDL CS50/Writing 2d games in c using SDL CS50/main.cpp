#include <iostream>
#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <cmath>

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)

#define SCROLL_SPEED (300)
#define SPEED (300) //PIXELS PER SECOND

int main(int argc, char ** argv)
{
	SDL_Event event;

	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0)
	{
		std::cout << "Error initializing SDL: " << SDL_GetError();
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("Hello, CS50",
											SDL_WINDOWPOS_CENTERED,
											SDL_WINDOWPOS_CENTERED,
											640, 480, 0);
	if (!window)
	{
		std::cout << "error creating window: " << SDL_GetError();
		SDL_Quit();
		return 1;
	}

	Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	SDL_Renderer *rend = SDL_CreateRenderer(window, -1, render_flags);
	if (!rend)
	{
		std::cout << "error creating renderer: " << SDL_GetError();
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	SDL_Surface *surface = IMG_Load("resources/cs50.png");
	if (!surface)
	{
		std::cout << "error creating surface\n";
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	SDL_Texture *tex = SDL_CreateTextureFromSurface(rend, surface);
	SDL_FreeSurface(surface);
	if (!tex)
	{
		std::cout << "error creating texture: " << SDL_GetError();
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	SDL_Rect dest;

	SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
	//Subir texto
	////centrar la textura
	//dest.x = (WINDOW_WIDTH - dest.w) / 2;
	//float y_pos = WINDOW_HEIGHT;
	//dest.y = (int) y_pos;

	//scale de dimension of texture
	dest.w /= 4;
	dest.h /= 4;

	//start sprite in center of screen
	float x_pos = (WINDOW_WIDTH - dest.w) / 2;
	float y_pos = (WINDOW_WIDTH - dest.h) / 2;

	//float x_vel = SPEED;
	//float y_vel = SPEED;
	float x_vel = 0;
	float y_vel = 0;

	int up = 0;
	int down = 0;
	int left = 0;
	int right = 0;

	int close_requested = 0;

	//while (dest.y >= -dest.h)
	while (!close_requested)
	{
		//SDL_RenderClear(rend);

		//dest.y = (int) y_pos;

		//SDL_RenderCopy(rend, tex, NULL, &dest);
		//SDL_RenderPresent(rend);

		////sube la imagen
		//y_pos -= (float) SCROLL_SPEED / 60;

		//SDL_Delay(1000/60);
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				close_requested = 1;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_W:
				case SDL_SCANCODE_UP:
					up = 1;
					break;
				case SDL_SCANCODE_A:
				case SDL_SCANCODE_LEFT:
					left = 1;
					break;
				case SDL_SCANCODE_S:
				case SDL_SCANCODE_DOWN:
					down = 1;
					break;
				case SDL_SCANCODE_D:
				case SDL_SCANCODE_RIGHT:
					right = 1;
					break;
				}
				break;
			case SDL_KEYUP:
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_W:
				case SDL_SCANCODE_UP:
					up = 0;
					break;
				case SDL_SCANCODE_A:
				case SDL_SCANCODE_LEFT:
					left = 0;
					break;
				case SDL_SCANCODE_S:
				case SDL_SCANCODE_DOWN:
					down = 0;
					break;
				case SDL_SCANCODE_D:
				case SDL_SCANCODE_RIGHT:
					right = 0;
					break;
				}
				break;
			}
		}

		int mouse_x, mouse_y;
		int buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

		int target_x = mouse_x - dest.w / 2;//center of image
		int target_y = mouse_y - dest.h / 2;
		float delta_x = target_x - x_pos;
		float delta_y = target_y - y_pos;
		float distance = sqrt(delta_x * delta_x + delta_y * delta_y);

		//prevent jitter
		if (distance < 5)
		{
			x_vel = y_vel = 0;
		}
		else
		{
			x_vel = delta_x * SPEED / distance;
			y_vel = delta_y * SPEED / distance;
		}

		if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			x_vel = -x_vel;
			y_vel = -y_vel;
		}

		//x_vel = y_vel = 0;//Para que se mueva libremente al inicio
		if (up && !down) y_vel = -SPEED;
		if (down && !up) y_vel = SPEED;
		if (left && !right) x_vel = -SPEED;
		if (right && !left) x_vel = SPEED;

		x_pos += x_vel / 60;
		y_pos += y_vel / 60;

		//izquierda
		if (x_pos <= 0)
		{
			x_pos = 0;
		}
		//arriba
		if (y_pos <= 0)
		{
			y_pos = 0;
		}
		//derecha
		if (x_pos >= WINDOW_WIDTH - dest.w)
		{
			x_pos = WINDOW_WIDTH - dest.w;
		}
		//abajo
		if (y_pos >= WINDOW_HEIGHT - dest.h)
		{
			y_pos = WINDOW_HEIGHT - dest.h;
		}

		////izquierda
		//if (x_pos <= 0)
		//{
		//	x_pos = 0;
		//	x_vel = -x_vel;
		//}
		////arriba
		//if (y_pos <= 0)
		//{
		//	y_pos = 0;
		//	y_vel = -y_vel;
		//}
		////derecha
		//if (x_pos >= WINDOW_WIDTH - dest.w)
		//{
		//	x_pos = WINDOW_WIDTH - dest.w;
		//	x_vel = -x_vel;
		//}
		////abajo
		//if (y_pos >= WINDOW_HEIGHT - dest.h)
		//{
		//	y_pos = WINDOW_HEIGHT - dest.h;
		//	y_vel = -y_vel;
		//}

		/*x_pos += x_vel / 60;
		y_pos += y_vel / 60;*/

		dest.x = (int)x_pos;
		dest.y = (int)y_pos;

		SDL_RenderClear(rend);

		SDL_RenderCopy(rend, tex, NULL, &dest);
		SDL_RenderPresent(rend);

		SDL_Delay(1000 / 60);
	}

	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}