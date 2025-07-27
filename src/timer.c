#include <gtk/gtk.h>
#include "main.h"
#include "create.h"
#include "time_functions.h"

static void on_paused_pressed(GtkWidget * caller, gpointer caller_data)
{
	(void) caller; 
	GtkData * data = (GtkData *)caller_data;
	data->is_paused = !data->is_paused;
	if (data->is_paused)
	{
		gtk_button_set_label(GTK_BUTTON(data->pause_button), "Pause");
	}
	else
	{
		gtk_button_set_label(GTK_BUTTON(data->pause_button), "Resume");
	}
}

static void on_quit_pressed(GtkWidget * caller, gpointer caller_data)
{
	(void) caller; 
	GtkData * data = (GtkData *)caller_data;
	gtk_window_destroy(GTK_WINDOW(data->window));
}

static gboolean time_loop(gpointer caller_data)
{
	GtkData * data = (GtkData *)caller_data;

	if (data->timer_ended)
	{
		data->display = !data->display;
		if (data->display)
		{
			gtk_label_set_label(GTK_LABEL(data->output), "00:00:00");
		}
		else
		{
			gtk_label_set_label(GTK_LABEL(data->output), "        ");
		}
		return true;
	}

	gint64 time_remaining = data->end_time - get_unix_time();
	if (time_remaining < 0)
	{
		GtkMediaStream * alarm_sound = gtk_media_file_new_for_filename("/usr/share/sounds/freedesktop/stereo/alarm-clock-elapsed.oga");
		gtk_media_stream_play(alarm_sound);
		gtk_label_set_label(GTK_LABEL(data->output), "        ");
		data->timer_ended = true;
		g_timeout_add(500, time_loop, data);
		return false;
	}

	if (data->is_paused)
	{
		data->end_time += 1;
		return true;
	}

	gchar * output_text = seconds_to_hms(time_remaining);
	gtk_label_set_label(GTK_LABEL(data->output), output_text);
	g_free(output_text);
	return true;
}

void create_timer(GtkData * data)
{
	data->output =       create(gtk_label_new("00:00:00"),          0,  0,  2,  1, data);
	data->pause_button = create(gtk_button_new_with_label("Pause"), 0,  1,  1,  1, data);
	data->quit_button  = create(gtk_button_new_with_label("Quit"),  1,  1,  1,  1, data);

	// Set font
	gtk_widget_add_css_class(data->output, "monospace");
	GtkCssProvider * provider = gtk_css_provider_new();
	gtk_css_provider_load_from_string(provider, ".monospace { font-family: monospace; font-size: 28pt; }");
	gtk_style_context_add_provider_for_display(gdk_display_get_default(),GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_widget_set_size_request(data->pause_button, 80, -1);
	gtk_widget_set_size_request(data->quit_button,  80, -1);

	g_signal_connect(data->pause_button, "clicked", G_CALLBACK(on_paused_pressed), data);
	g_signal_connect(data->quit_button,  "clicked", G_CALLBACK(on_quit_pressed),   data);

	time_loop(data);
	g_timeout_add(1000, time_loop, data);
}


