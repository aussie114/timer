#include <gtk/gtk.h>
#include "time_functions.h"
#include "window.h"
#include "grid.h"
#include "timer.h"

void activate(GtkApplication * app, gpointer user_data)
{
	(void)user_data;

	create_window(app);
	create_grid();
	create_timer();
	gtk_window_present (GTK_WINDOW (window));
}

int main (int argc, char ** argv)
{
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

	GtkApplication * program;
	int status;

	program = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (program, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (program), argc, argv);
	g_object_unref (program);
	return status;
}


