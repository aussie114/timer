#ifndef MAIN_H
#define MAIN_H
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
extern int running;
extern unsigned int delta;
extern int totalMS;
extern int timeRemaining;
extern SDL_Renderer * renderer;
extern TTF_TextEngine * textEngine;
#endif
