#ifndef MAIN_H
#define MAIN_H

typedef struct 
{
    GtkWidget * window;
    GtkWidget * grid;
    GtkWidget * output;
	GtkWidget * pause_button;
	GtkWidget * quit_button;
} Widgets;

extern Widgets widgets;
extern gint64 end_time;
extern gboolean is_paused;
#endif
