#include <gtk/gtk.h>
#include "window.h"
#include "create.h"
#include "time_functions.h"

gint64 end_time;
static gboolean is_paused = false;
static gboolean timer_ended = false;
static gboolean display = false;
static gchar * display_labels[] = {"        ", "00:00:00"};
static gchar * button_labels[] = {"Pause", "Resume"};
static GtkWidget * output; 
static GtkWidget * pause_button;
static GtkWidget * quit_button;

static gboolean time_loop(gpointer user_data)
{
	(void)user_data;

	if (timer_ended)
	{
		display = !display;
		gtk_label_set_label(GTK_LABEL(output), display_labels[display]);
		return true;
	}

	gint64 time_remaining = end_time - get_unix_time();
	if (time_remaining < 0)
	{
		GtkMediaStream * alarm_sound = gtk_media_file_new_for_filename("/usr/share/sounds/freedesktop/stereo/alarm-clock-elapsed.oga");
		gtk_media_stream_play(alarm_sound);
		gtk_label_set_label(GTK_LABEL(output), display_labels[display]);
		timer_ended = true;
		g_timeout_add(500, time_loop, NULL);
		return false;
	}

	if (is_paused)
	{
		end_time += 1;
		return true;
	}

	gchar * output_text = seconds_to_hms(time_remaining);
	gtk_label_set_label(GTK_LABEL(output), output_text);
	g_free(output_text);
	return true;
}

static void on_paused_pressed(GtkWidget * caller, gpointer data)
{
	(void) caller; (void) data;
	is_paused = !is_paused;
	gtk_button_set_label(GTK_BUTTON(pause_button), button_labels[is_paused]);
}

static void on_quit_pressed(GtkWidget * caller, gpointer data)
{
	(void) caller; (void) data;
	gtk_window_destroy(GTK_WINDOW(window));
}

void create_timer()
{
	output       = create(gtk_label_new("00:00:00"),          0,  0,  2,  1);
	pause_button = create(gtk_button_new_with_label("Pause"), 0,  1,  1,  1);
	quit_button  = create(gtk_button_new_with_label("Quit"),  1,  1,  1,  1);

	gtk_widget_set_size_request(pause_button, 80, -1);
	gtk_widget_set_size_request(quit_button,  80, -1);

	gtk_widget_add_css_class(output, "monospace");
	GtkCssProvider * provider = gtk_css_provider_new();
	gtk_css_provider_load_from_string(provider, ".monospace { font-family: monospace; font-size: 28pt; }");
	gtk_style_context_add_provider_for_display(gdk_display_get_default(),GTK_STYLE_PROVIDER(provider),GTK_STYLE_PROVIDER_PRIORITY_USER);

	g_signal_connect(pause_button, "clicked", G_CALLBACK(on_paused_pressed), NULL);
	g_signal_connect(quit_button,  "clicked", G_CALLBACK(on_quit_pressed),   NULL);

	time_loop(NULL);
	g_timeout_add(1000, time_loop, NULL);
}
