#ifndef MAIN_H
#define MAIN_H
typedef struct
{
	GtkWidget * window;
	GtkWidget * grid;
	GtkWidget * output;
	GtkWidget * pause_button;
	GtkWidget * quit_button;
	gint64 end_time;
	gboolean display;
	gboolean is_paused;
	gboolean timer_ended;
} GtkData;
#endif
