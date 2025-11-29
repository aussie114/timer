#include "main.h"
#include "button_textures.h"
#include "input.h"

static SDL_FRect position = {171, 68, 82, 28};
static TTF_Text * text = NULL;

void createQuit(void)
{
	text = TTF_CreateText(textEngine, buttonFont, "Quit", 0);
}

void processQuit(void)
{
	if (SDL_PointInRectFloat(&mousePosition, &position))
	{
		if (mouseState == SDL_BUTTON_LEFT)
		{
			SDL_RenderTexture(renderer, buttonTextureClicked,  NULL, &position);
		}
		else
		{
			SDL_RenderTexture(renderer, buttonTextureHover,  NULL, &position);
		}
		if (leftMouseButtonReleased == 1)
		{
			running = 0;
		}
	}
	else
	{
		SDL_RenderTexture(renderer, buttonTextureNormal, NULL, &position);
	}

	TTF_DrawRendererText(text, 196, 72);
}

void destroyQuit(void)
{
	TTF_DestroyText(text);
}
