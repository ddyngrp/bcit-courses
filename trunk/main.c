/**
 * SECTION:main
 * @short_description: The main entry point for the #Spry web browser
 *
 * #Spry is a WebKit browser based on Gtk+ meant for the ARM processor.
 */

#include <gtk/gtk.h>
#include <webkit/webkit.h>

/**
 * destroy_cb:
 * @widget: pointer to the widget being destroyed
 * @data: additional parameter data
 *
 * Called when the GtkWidget is closed
 **/
static void
destroy_cb (GtkWidget* widget, gpointer data)
{
	gtk_main_quit ();
}

/**
 * main:
 * @argc: number of arguments passed in
 * @argv: the arguments passed via the command line
 *
 * Creates a new browser window that points to a URL that was passed
 * in cia @argv
 *
 * Returns: %0 if the operation succeeded, else %1.
 **/
int
main (int argc, char* argv[])
{
	GtkWidget* scrolled_window;
	WebKitWebView* web_view;
	GtkWidget* main_window;
	
	/* grap gtk-specific arguments and apply accordingly */
	gtk_init (&argc, &argv);
	
	/* check for g_thread support */
	if (!g_thread_supported ()) {
		g_thread_init (NULL);
	}
	
	/* verify address was given */
	if (argc < 2) {
		g_print("No Address Specified\n");
		return 1;
	}

	/* create main window */
	main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size (GTK_WINDOW (main_window), 800, 600);
	gtk_widget_set_name (main_window, "Spry");
	g_signal_connect (G_OBJECT (main_window), "destroy", G_CALLBACK (destroy_cb), NULL);
	
	/* create scrolled window (viewport) and add to main window*/
	scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_container_add (GTK_CONTAINER (main_window), scrolled_window);

	/* create web view and add to scrolled window */
	web_view = WEBKIT_WEB_VIEW (webkit_web_view_new ());
	gtk_container_add (GTK_CONTAINER (scrolled_window), GTK_WIDGET (web_view));
	
	/* load web page */
	webkit_web_view_open (web_view, (gchar*)argv[1]);

	/* make everything visible and start gtk */
	gtk_widget_grab_focus (GTK_WIDGET (web_view));
	gtk_widget_show_all (main_window);
	gtk_main ();

	/* done */
	return 0;
}
