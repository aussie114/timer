#include <main.h>
#include "time_functions.h"
#include "input.h"
#include "output.h"
#include "button_textures.h"
#include "pause_button.h"
#include "reset_button.h"
#include "quit_button.h"

int running = 1;
unsigned int delta = 0;
int totalMS;
int timeRemaining;
SDL_Renderer * renderer;
TTF_TextEngine * textEngine;

int main(int argc, char* argv[]) 
{
	if (argc > 1)
	{
		totalMS = hms_to_seconds(argv[1]) * 1000;
		timeRemaining = totalMS;
	}
	else
	{
		return -1;
	}

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	SDL_Window * window = SDL_CreateWindow("sticky notes", 256, 98, 0);
	renderer = SDL_CreateRenderer(window, NULL);
	textEngine = TTF_CreateRendererTextEngine(renderer);

	createOutput();
	createButtonTextures();
	createPauseButton();
	createReset();
	createQuit();

	unsigned int lastFrame = 0;
	while (running) 
	{
		delta = SDL_GetTicks() - lastFrame;
		lastFrame = SDL_GetTicks();

		SDL_SetRenderDrawColor(renderer, 56, 60, 74, 255);
		SDL_RenderClear(renderer);

		processInput();
		processOutput();
		processPauseButton();
		processReset();
		processQuit();

		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}

	TTF_DestroyRendererTextEngine(textEngine);
	destroyOutput();
	destroyButtonTextures();
	destroyPauseButton();
	destroyReset();
	destroyQuit();
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();

    return 0;
}
