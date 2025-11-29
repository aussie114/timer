#include "main.h"
#include "button_textures.h"

static int w  = 82;
static int h  = 28;

TTF_Font * buttonFont;
SDL_Texture * buttonTextureNormal  = {0};
SDL_Texture * buttonTextureHover   = {0};
SDL_Texture * buttonTextureClicked = {0};

static void createButtonTexture(SDL_Texture * texture, SDL_Color bodyColour)
{
	SDL_FRect border  = {0, 0,     w, h};
	SDL_FRect body    = {1, 1, w - 2, h - 2};
	SDL_FRect corners[4] = 
	{
		{0    ,     0, 2, 2},
		{w - 2,     0, 2, 2},
		{0    , h - 2, 2, 2},
		{w - 2, h - 2, 2, 2}
	};
	SDL_FRect clips[4] = 
	{
		{0    ,     0, 1, 1},
		{w - 1,     0, 1, 1},
		{0    , h - 1, 1, 1},
		{w - 1, h - 1, 1, 1}
	};

	SDL_SetRenderTarget(renderer, texture);
	SDL_SetRenderDrawColor(renderer, 43, 46, 57, 255);
	SDL_RenderFillRect(renderer, &border);

	SDL_SetRenderDrawColor(renderer, bodyColour.r, bodyColour.g, bodyColour.b, 255);
	SDL_RenderFillRect(renderer, &body);

	SDL_SetRenderDrawColor(renderer, 48, 51, 63, 255);
	SDL_RenderFillRects(renderer, corners, 4);

	SDL_SetRenderDrawColor(renderer, 56, 60, 74, 255);
	SDL_RenderFillRects(renderer, clips, 4);
}

void createButtonTextures(void)
{
	buttonFont = TTF_OpenFont("/home/admin/.fonts/ubuntu/UbuntuMono-Regular.ttf", 16);
	SDL_Color normal  = {68,  74,  88, 255};
	SDL_Color hover   = {80,  86, 102, 255};
	SDL_Color clicked = {82, 148, 226, 255};

	buttonTextureNormal  = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
	buttonTextureHover   = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
	buttonTextureClicked = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);

	createButtonTexture(buttonTextureNormal,   normal);
	createButtonTexture(buttonTextureHover,     hover);
	createButtonTexture(buttonTextureClicked, clicked);

	SDL_SetRenderTarget(renderer, NULL);
}

void destroyButtonTextures(void)
{
	SDL_DestroyTexture(buttonTextureNormal);
	SDL_DestroyTexture(buttonTextureHover);
	SDL_DestroyTexture(buttonTextureClicked);
	TTF_CloseFont(buttonFont);
}

