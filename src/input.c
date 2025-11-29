#include "main.h"
#include "pause_button.h"

SDL_Event event;
SDL_FPoint mousePosition = {0,0};
int leftMouseButtonReleased = 0;
SDL_MouseButtonFlags mouseState = 0;

void processInput(void)
{
	leftMouseButtonReleased = 0;
	mousePosition.x = 0;
	mousePosition.y = 0;
	while(SDL_PollEvent(&event))
	{
		if (event.key.key == SDLK_ESCAPE)
		{
			running = 0;
		}
		if (event.key.key == SDLK_SPACE && event.type == SDL_EVENT_KEY_UP)
		{
			paused = !paused;
		}
		else if (event.type == SDL_EVENT_MOUSE_MOTION)
		{
		}
		else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP && event.button.button == SDL_BUTTON_LEFT)
		{
			leftMouseButtonReleased = 1;
		}
	}
	mouseState = SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
}
