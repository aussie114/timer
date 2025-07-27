#include "gtk/gtk.h"
#include "main.h"
//#include "grid.h"

GtkWidget * create(GtkWidget * widget, int x, int y, int w, int h, GtkData * data)
{
	gtk_grid_attach(GTK_GRID(data->grid), widget, x, y, w, h);
	return widget;
}

