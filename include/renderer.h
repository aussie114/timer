#ifndef RENDERER_H
#define RENDERER_H
#include <ncurses.h>
void render(WINDOW * digits[], char * time_label, int seconds, bool flash, bool redraw);
#endif

