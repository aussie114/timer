#include <gtk/gtk.h>
#include "main.h"

void create_grid(GtkData * data)
{
	data->grid = gtk_grid_new();
	gtk_window_set_child (GTK_WINDOW (data->window), data->grid);
	gtk_widget_set_margin_top           (data->grid,  4);
	gtk_widget_set_margin_end           (data->grid,  4);
	gtk_widget_set_margin_bottom        (data->grid,  4);
	gtk_widget_set_margin_start         (data->grid,  4);
	gtk_grid_set_column_spacing(GTK_GRID(data->grid), 2);
	gtk_grid_set_row_spacing(   GTK_GRID(data->grid), 2);
}
