#include <gtk/gtk.h>
#include "main.h"
#include "config.h"
#include "logic.h"
#include "time_functions.h"

Widgets widgets;
gint64 end_time;
gboolean is_paused = false;

GtkWidget * create(GtkWidget * widget, int x, int y, int w, int h)
{
	gtk_grid_attach(GTK_GRID(widgets.grid), widget, x, y, w, h);
	return widget;
}

void activate(GtkApplication * app, gpointer user_data)
{
	(void)user_data;

	widgets.window       = gtk_application_window_new(app);
	widgets.grid         = gtk_grid_new();
	widgets.output       = create(gtk_label_new("00:00:00"),          0,  0,  2,  1);
	widgets.pause_button = create(gtk_button_new_with_label("Pause"), 0,  1,  1,  1);
	widgets.quit_button  = create(gtk_button_new_with_label("Quit"),  1,  1,  1,  1);

	GtkEventController * controller = gtk_event_controller_key_new();
	
	config(controller);
	connect_signals(controller);

	gtk_window_present (GTK_WINDOW (widgets.window));
}

int main (int argc, char ** argv)
{
	GtkApplication * program;
	int status;

	if (argc > 1)
	{
		if (g_utf8_strlen(argv[1], -1) > 8)
		{
			g_print("Usage:\n\ttimer HH:MM:SS\n\ttimer MM:SS\n\ttimer SS\n");
			return -1;
		}
		end_time = get_unix_time() + hms_to_seconds(argv[1]);
		argc = 1;
	}
	else
	{
		g_print("Usage:\n\ttimer HH:MM:SS\n\ttimer MM:SS\n\ttimer SS\n");
		return -2;
	}

	program = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (program, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (program), argc, argv);
	g_object_unref (program);
	return status;
}


