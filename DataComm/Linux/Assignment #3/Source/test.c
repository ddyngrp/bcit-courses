i/*
  *File name: window.c
  */

#include <gtk/gtk.h>
#include <glib.h>

int main (int argc, char *argv[])
{
	/*-- Declare the GTK Widgets used in the program --*/
	GtkWidget *window;

	/*--  Initialize GTK --*/
	gtk_init (&argc, &argv);

	/*-- Create the new window --*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	/*-- Display the window --*/
	gtk_widget_show(window);

	/*-- Start the GTK event loop --*/
	gtk_main();

	/*-- Return 0 if exit is successful --*/
	return 0;
}
