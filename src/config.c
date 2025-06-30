#include <gtk/gtk.h>
#include "main.h"
#include "time_functions.h"

void config(GtkEventController * controller)
{
	// Window
	gtk_window_set_title        ( GTK_WINDOW (widgets.window), "Timer");
	gtk_window_set_resizable    ( GTK_WINDOW (widgets.window), FALSE);

	// grid
	gtk_window_set_child (GTK_WINDOW (widgets.window), widgets.grid);
	gtk_widget_set_margin_top           (widgets.grid,  4);
	gtk_widget_set_margin_end           (widgets.grid,  4);
	gtk_widget_set_margin_bottom        (widgets.grid,  4);
	gtk_widget_set_margin_start         (widgets.grid,  4);
	gtk_grid_set_column_spacing(GTK_GRID(widgets.grid), 2);
	gtk_grid_set_row_spacing(   GTK_GRID(widgets.grid), 2);

	gtk_widget_set_size_request(widgets.pause_button, 80, -1);
	gtk_widget_set_size_request(widgets.quit_button,  80, -1);

	gtk_widget_add_css_class(widgets.output, "monospace");
	GtkCssProvider * provider = gtk_css_provider_new();
	gtk_css_provider_load_from_string(provider,
		".monospace { font-family: monospace; font-size: 28pt; }");
	gtk_style_context_add_provider_for_display(
		gdk_display_get_default(),
		GTK_STYLE_PROVIDER(provider),
		GTK_STYLE_PROVIDER_PRIORITY_USER);

	gtk_widget_add_controller(widgets.window, controller);

}
