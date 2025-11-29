#include "main.h"
#include "button_textures.h"
#include "input.h"
#include "pause_button.h"

static SDL_FRect position = {87,68,82,28};
static TTF_Text * text = NULL;

void createReset(void)
{
	text = TTF_CreateText(textEngine, buttonFont, "Reset", 0);
}

void processReset(void)
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
			timeRemaining = totalMS;
			if (paused)
			{
				paused = 0;
			}
		}
	}
	else
	{
		SDL_RenderTexture(renderer, buttonTextureNormal,  NULL, &position);
	}

	TTF_DrawRendererText(text, 108, 72);
}

void destroyReset(void)
{
	TTF_DestroyText(text);
}
