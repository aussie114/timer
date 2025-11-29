#ifndef BUTTON_TEXTURES_H
#define BUTTON_TEXTURES_H
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
extern TTF_Font * buttonFont;
extern SDL_Texture * buttonTextureNormal;
extern SDL_Texture * buttonTextureHover;
extern SDL_Texture * buttonTextureClicked;
void createButtonTextures(void);
void destroyButtonTextures(void);
#endif
