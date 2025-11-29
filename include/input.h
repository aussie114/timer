#ifndef INPUT_H
#define INPUT_H
#include <SDL3/SDL.h>
extern SDL_FPoint mousePosition;
extern int leftMouseButtonReleased;
extern SDL_MouseButtonFlags mouseState;
void processInput(void);
#endif
