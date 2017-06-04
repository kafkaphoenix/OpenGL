#include <SDL.h>
#include <iostream>

int main(int argc, char ** argv) {
	bool leftMouseButtonDown = false;
	bool quit = false;
	int color = 0;
	int grosor = 1;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window = SDL_CreateWindow("SDL 2 Pixel Drawing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, 640, 480);
	Uint32 *pixels = new Uint32[640 * 480];
	memset(pixels, 255, 640 * 480 * sizeof(Uint32));

	while (!quit) {
		SDL_UpdateTexture(texture, NULL, pixels, 640 * sizeof(Uint32));

		SDL_WaitEvent(&event);

		switch (event.type)
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) 
			{
				case SDLK_ESCAPE:
					quit = true;
					break;
				case SDLK_DELETE:
					memset(pixels, 255, 640 * 480 * sizeof(Uint32));
					break;
				case SDLK_n:
					color = 0;
					break;
				case SDLK_r:
					color = 1;
					break;
				case SDLK_g:
					color = 2;
					break;
				case SDLK_b:
					color = 3;
					break;
				case SDLK_1:
					grosor = 1;
					break;
				case SDLK_2:
					grosor = 2;
					break;
				case SDLK_3:
					grosor = 3;
					break;
				case SDLK_4:
					grosor = 4;
					break;
				case SDLK_5://Brocha 2
					grosor = 5;
					break;
				case SDLK_6://Brocha 2
					grosor = 6;
					break;
				case SDLK_7://Cuadrado
					grosor = 7;
					break;
				case SDLK_w:
					color = 4;
					break;
				case SDLK_i:
					SDL_ShowSimpleMessageBox(0, "Help",
						"Grosor: 1, 2, 3, 4\nNuevo: Supr\nBorrar: w\nColor: r(rojo),g(verde),b(azul),n(negro)\nBrocha: 5, 6\nBrocha Cuadrada: 7\nSalir: Esc"
						, window);
					break;
			}
			break;
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
				leftMouseButtonDown = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) 
				leftMouseButtonDown = true;
		case SDL_MOUSEMOTION:
			if (leftMouseButtonDown)
			{
				int mouseX = event.motion.x;
				int mouseY = event.motion.y;
				Uint32 pixel = pixels[mouseY * 640 + mouseX];

				Uint8 r = pixel >> 16 & 0xFF;
				Uint8 g = pixel >> 8 & 0xFF;
				Uint8 b = pixel & 0xFF;

				switch (color)
				{
					case 0:
						r = 0;
						g = 0;
						b = 0;
						break;
					case 1:
						r = 0;
						g = 0;
						b = 255;
						break;
					case 2:
						r = 0;
						g = 255;
						b = 0;
						break;
					case 3:
						r = 255;
						g = 0;
						b = 0;
						break;
					case 4:
						r = 255;
						g = 255;
						b = 255;
						break;
				}

				pixel = (0xFF << 24) | (r << 16) | (g << 8) | b;

				switch (grosor)
				{
					case 1:
						pixels[mouseY * 640 + mouseX] = pixel;
						break;
					case 2:
						//center
						pixels[mouseY * 640 + mouseX] = pixel;
						//up
						pixels[(mouseY - 1) * 640 + mouseX] = pixel;
						//left
						pixels[mouseY * 640 + (mouseX - 1)] = pixel;
						//corner 2
						pixels[(mouseY - 1) * 640 + (mouseX - 1)] = pixel;
						break;
					case 3:
						//center
						pixels[mouseY * 640 + mouseX] = pixel;
						//up
						pixels[(mouseY - 1) * 640 + mouseX] = pixel;
						//left
						pixels[mouseY * 640 + (mouseX - 1)] = pixel;
						//corner 2
						pixels[(mouseY - 1) * 640 + (mouseX - 1)] = pixel;

						//down
						pixels[(mouseY + 1) * 640 + mouseX] = pixel;
						//corner 3
						pixels[(mouseY + 1) * 640 + (mouseX - 1)] = pixel;

						//right
						pixels[mouseY * 640 + (mouseX + 1)] = pixel;
						//corner 1
						pixels[(mouseY - 1) * 640 + (mouseX + 1)] = pixel;

						//up_left
						pixels[(mouseY - 1) * 640 + (mouseX-2)] = pixel;
						//left_left
						pixels[mouseY * 640 + (mouseX - 2)] = pixel;

						//up_up
						pixels[(mouseY - 2) * 640 + mouseX] = pixel;
						//corner 2_up
						pixels[(mouseY - 2) * 640 + (mouseX - 1)] = pixel;
						break;
					case 4:
						//center
						pixels[mouseY * 640 + mouseX] = pixel;
						//up
						pixels[(mouseY - 1) * 640 + mouseX] = pixel;
						//left
						pixels[mouseY * 640 + (mouseX - 1)] = pixel;
						//corner 2
						pixels[(mouseY - 1) * 640 + (mouseX - 1)] = pixel;

						//down
						pixels[(mouseY + 1) * 640 + mouseX] = pixel;
						//corner 3
						pixels[(mouseY + 1) * 640 + (mouseX - 1)] = pixel;
						//down2
						pixels[(mouseY + 2) * 640 + mouseX] = pixel;
						//corner 3_2
						pixels[(mouseY + 2) * 640 + (mouseX - 1)] = pixel;

						//right
						pixels[mouseY * 640 + (mouseX + 1)] = pixel;
						//corner 1
						pixels[(mouseY - 1) * 640 + (mouseX + 1)] = pixel;
						//right2
						pixels[mouseY * 640 + (mouseX + 2)] = pixel;
						//corner 1_2
						pixels[(mouseY - 1) * 640 + (mouseX + 2)] = pixel;

						//up_left
						pixels[(mouseY - 1) * 640 + (mouseX - 2)] = pixel;
						//left_left
						pixels[mouseY * 640 + (mouseX - 2)] = pixel;
						//up_left2
						pixels[(mouseY - 1) * 640 + (mouseX - 3)] = pixel;
						//left_left2
						pixels[mouseY * 640 + (mouseX - 3)] = pixel;

						//up_up
						pixels[(mouseY - 2) * 640 + mouseX] = pixel;
						//corner 2_up
						pixels[(mouseY - 2) * 640 + (mouseX - 1)] = pixel;
						//up_up2
						pixels[(mouseY - 3) * 640 + mouseX] = pixel;
						//corner 2_up_2
						pixels[(mouseY - 3) * 640 + (mouseX - 1)] = pixel;
						
						//down_corner(corner 4)
						pixels[(mouseY + 1) * 640 + (mouseX + 1)] = pixel;
						//corner 3_corner
						pixels[(mouseY + 1) * 640 + (mouseX - 2)] = pixel;
						//up_left2_corner
						pixels[(mouseY - 2) * 640 + (mouseX - 2)] = pixel;
						//up_up_corner
						pixels[(mouseY - 2) * 640 + (mouseX + 1)] = pixel;
						
						break;
					case 5:
						//center
						pixels[mouseY * 640 + mouseX] = pixel;
						//up
						pixels[(mouseY - 1) * 640 + mouseX] = pixel;
						//left
						pixels[mouseY * 640 + (mouseX - 1)] = pixel;
						//corner 2
						pixels[(mouseY - 1) * 640 + (mouseX - 1)] = pixel;
						
						//center
						pixels[mouseY * 640 + (mouseX -2)] = pixel;
						//up
						pixels[(mouseY - 1) * 640 + (mouseX - 2)] = pixel;
						//left
						pixels[mouseY * 640 + (mouseX - 3)] = pixel;
						//corner 2
						pixels[(mouseY - 1) * 640 + (mouseX - 3)] = pixel;

						//center
						pixels[mouseY * 640 + (mouseX + 2)] = pixel;
						//up
						pixels[(mouseY - 1) * 640 + (mouseX + 2)] = pixel;
						//left
						pixels[mouseY * 640 + (mouseX + 1)] = pixel;
						//corner 2
						pixels[(mouseY - 1) * 640 + (mouseX + 1)] = pixel;
						break;
					case 6:
						//center
						pixels[mouseY * 640 + mouseX] = pixel;
						//up
						pixels[(mouseY - 1) * 640 + mouseX] = pixel;
						//left
						pixels[mouseY * 640 + (mouseX - 1)] = pixel;
						//corner 2
						pixels[(mouseY - 1) * 640 + (mouseX - 1)] = pixel;

						//center
						pixels[mouseY * 640 + (mouseX - 2)] = pixel;
						//up
						pixels[(mouseY - 1) * 640 + (mouseX - 2)] = pixel;
						//left
						pixels[mouseY * 640 + (mouseX - 3)] = pixel;
						//corner 2
						pixels[(mouseY - 1) * 640 + (mouseX - 3)] = pixel;

						//center
						pixels[mouseY * 640 + (mouseX + 2)] = pixel;
						//up
						pixels[(mouseY - 1) * 640 + (mouseX + 2)] = pixel;
						//left
						pixels[mouseY * 640 + (mouseX + 1)] = pixel;
						//corner 2
						pixels[(mouseY - 1) * 640 + (mouseX + 1)] = pixel;

						//center_up
						pixels[(mouseY - 2) * 640 + mouseX] = pixel;
						//up_up
						pixels[(mouseY - 3) * 640 + mouseX] = pixel;
						//left_up
						pixels[(mouseY - 2) * 640 + (mouseX - 1)] = pixel;
						//corner 2_up
						pixels[(mouseY - 3) * 640 + (mouseX - 1)] = pixel;

						//center_up
						pixels[(mouseY - 2) * 640 + (mouseX - 2)] = pixel;
						//up_up
						pixels[(mouseY - 3) * 640 + (mouseX - 2)] = pixel;
						//left_up
						pixels[(mouseY - 2) * 640 + (mouseX - 3)] = pixel;
						//corner 2_up
						pixels[(mouseY - 3) * 640 + (mouseX - 3)] = pixel;

						//center_up
						pixels[(mouseY - 2) * 640 + (mouseX + 2)] = pixel;
						//up_up
						pixels[(mouseY - 3) * 640 + (mouseX + 2)] = pixel;
						//left_up
						pixels[(mouseY - 2) * 640 + (mouseX + 1)] = pixel;
						//corner 2_up
						pixels[(mouseY - 3) * 640 + (mouseX + 1)] = pixel;
						break;
					case 7:
						//center4
						pixels[mouseY * 640 + mouseX] = pixel;
						//up
						pixels[(mouseY - 1) * 640 + mouseX] = pixel;
						//left
						pixels[mouseY * 640 + (mouseX - 1)] = pixel;
						//corner 2
						pixels[(mouseY - 1) * 640 + (mouseX - 1)] = pixel;
						
						//center3
						pixels[mouseY * 640 + (mouseX - 2)] = pixel;
						//up
						pixels[(mouseY - 1) * 640 + (mouseX - 2)] = pixel;
						//left
						pixels[mouseY * 640 + (mouseX - 3)] = pixel;
						//corner 2
						pixels[(mouseY - 1) * 640 + (mouseX - 3)] = pixel;

						//center2
						pixels[(mouseY - 2) * 640 + (mouseX - 2)] = pixel;
						//up
						pixels[(mouseY - 3) * 640 + (mouseX - 2)] = pixel;
						//left
						pixels[(mouseY - 2) * 640 + (mouseX - 3)] = pixel;
						//corner 2
						pixels[(mouseY - 3) * 640 + (mouseX - 3)] = pixel;

						//center1
						pixels[(mouseY - 2) * 640 + mouseX] = pixel;
						//up
						pixels[(mouseY - 3) * 640 + mouseX] = pixel;
						//left
						pixels[(mouseY - 2) * 640 + (mouseX - 1)] = pixel;
						//corner 2
						pixels[(mouseY - 3) * 640 + (mouseX - 1)] = pixel;
						break;
				}
			}
			break;
		}

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
		
	}

	delete[] pixels;
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}