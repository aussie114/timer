#include <gtk/gtk.h>
#include "main.h"
#include "time_functions.h"
#include <stdlib.h>

gboolean on_key_pressed(GtkEventControllerKey * controller, guint keyval, guint keycode, GdkModifierType state, gpointer user_data)
{
    (void)controller;
    (void)keycode;
    (void)state;
	if (keyval == GDK_KEY_Escape) 
	{
		gtk_window_destroy(GTK_WINDOW(user_data));
		return true;
	}
		return false;
}

void on_paused_pressed(GtkWidget * caller, gpointer data)
{
	(void) caller; (void) data;
	if (is_paused)
	{
		is_paused = false;
		gtk_button_set_label(GTK_BUTTON(widgets.pause_button), "Pause");
	}
	else
	{
		is_paused = true;
		gtk_button_set_label(GTK_BUTTON(widgets.pause_button), "Resume");
	}
}

void on_quit_pressed(GtkWidget * caller, gpointer data)
{
	(void) caller; (void) data;
	gtk_window_destroy(GTK_WINDOW(widgets.window));
}


gboolean on_timeout(gpointer user_data)
{
	(void)user_data;
	gint64 time_remaining = end_time - get_unix_time();

	if (time_remaining < 0)
	{
		system("mpv /usr/share/sounds/freedesktop/stereo/alarm-clock-elapsed.oga");
		return false;
	}

	if (is_paused)
	{
		end_time += 1;
	}
	else 
	{
		gchar * output = seconds_to_hms(time_remaining);
		gtk_label_set_label(GTK_LABEL(widgets.output), output);
		g_free(output);
	}

	return true;
}

void connect_signals(GtkEventController * controller)
{
	on_timeout(NULL);
	g_timeout_add(1000, on_timeout, NULL);
	g_signal_connect(widgets.pause_button, "clicked", G_CALLBACK(on_paused_pressed), NULL);
	g_signal_connect(widgets.quit_button,  "clicked", G_CALLBACK(on_quit_pressed),   NULL);
	g_signal_connect(controller, "key-pressed", G_CALLBACK(on_key_pressed), widgets.window);
}
