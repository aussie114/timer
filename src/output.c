#include <stdlib.h>
#include "main.h"
#include "output.h"
#include "time_functions.h"
#include "pause_button.h"

int audioPlaying = 0;
static TTF_Font * outputFont = NULL;
static TTF_Text * text = NULL;

void createOutput(void)
{
	outputFont = TTF_OpenFont("/home/admin/.fonts/ubuntu/UbuntuMono-Regular.ttf", 64);
}

void processOutput()
{
	if (!paused)
	{
		timeRemaining -= delta;
	}
	if (timeRemaining > 0)
	{
		char output[16];
		seconds_to_hms(timeRemaining / 1000, output);
		text = TTF_CreateText(textEngine, outputFont, output, 0);
	}
	else if ((timeRemaining / 500) % 2 == 0)
	{
		text = TTF_CreateText(textEngine, outputFont, "00:00:00", 0);
		if ((timeRemaining / 1000) % 2 == 0 && !audioPlaying && timeRemaining > -60000)
		{
			system("paplay data/beep.mp3 &");
			audioPlaying = 1;
		}
	}
	else
	{
		text = TTF_CreateText(textEngine, outputFont, "  :  :  ", 0);
		audioPlaying = 0;
	}
	TTF_SetTextColor(text, 210, 216, 225, 255);
	TTF_DrawRendererText(text, 0, 0);
	TTF_DestroyText(text);

	if (timeRemaining < -600000)
	{
		running = 0;
	}
}

void destroyOutput(void)
{
	TTF_CloseFont(outputFont);
}
