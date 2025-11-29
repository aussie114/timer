#include "main.h"
#include "button_textures.h"
#include "input.h"

static SDL_FRect position = {3,68,82,28};

int paused = 0;

static TTF_Text * texts[2];
int labelOffsets[2] = {23,19};

void createPauseButton(void)
{
	texts[0] = TTF_CreateText(textEngine, buttonFont, "Pause",  0);
	texts[1] = TTF_CreateText(textEngine, buttonFont, "Resume", 0);
	TTF_SetTextColor(texts[0], 210, 216, 225, 255);
	TTF_SetTextColor(texts[1], 210, 216, 225, 255);
}

void processPauseButton(void)
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
			if (timeRemaining > 0)
			{
				paused = !paused;
			}
		}
	}
	else
	{
		SDL_RenderTexture(renderer, buttonTextureNormal,  NULL, &position);
	}
	TTF_DrawRendererText(texts[paused], labelOffsets[paused], 72);
}

void destroyPauseButton(void)
{
	TTF_DestroyText(texts[0]);
	TTF_DestroyText(texts[1]);
}

