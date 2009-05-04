/*
 * main.c
 * Copyright (C) 2009 Doug Penner <darwinsurvivor@gmail.com>
 *                    Brendan Neva <bneva1@my.bcit.ca>
 *                    Steffen L. Norgren <ironix@trollop.org>
 *                    Eddie Zhang <edisonhammer@gmail.com>
 * 
 * main.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * main.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <config.h>

#include <gtk/gtk.h>
#include <webkit/webkit.h>

#include "spry.h"
#include "callbacks.h"
#include "cliopts.h"
#include "generators.h"


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
main (int argc, char *argv[])
{
	GtkWidget*		scrolled_window;
	GtkWidget*		main_window;
	WebKitWebView*	web_view;
	SPRY_CONF*		conf;

	/* sets the gtk locale for the current system */
	gtk_set_locale ();

	/* grap gtk-specific arguments and apply accordingly */
	gtk_init (&argc, &argv);

	/* check for g_thread support */
	if (!g_thread_supported ()) {
		g_thread_init (NULL);
	}
	
	/* parse command line arguments and return the initial struct */
	conf = parse_args(argc, argv);
    
    /* THIS SHOULD BE HANDLED INSIDE PARSE_ARGS: REMOVE WHEN DONE!!!! */
    if (argc < 2) {
        g_print("No Website Specified\n");
        return 1;
    }
    conf->init_url = argv[1];
    

    /* Create GTK Objects */
	main_window = generate_main_window(conf);   /* Main Window */
	scrolled_window = generate_scrolled_window(conf);   /* Scrolled Window */
	web_view = generate_web_view(conf); /* WebKit ViewPort */
    
    /* Connect Signals */
	g_signal_connect (G_OBJECT (main_window), "destroy", G_CALLBACK (destroy), NULL);
	
	/* Put GTK Objects inside each-other and make them visible */
	gtk_container_add (GTK_CONTAINER (main_window), scrolled_window);
	gtk_container_add (GTK_CONTAINER (scrolled_window), GTK_WIDGET (web_view));
	gtk_widget_grab_focus (GTK_WIDGET (web_view));
	gtk_widget_show_all (main_window);
	
	/* load web page */
	webkit_web_view_open (web_view, (gchar*)conf->init_url);

	/* Start GTK */
	gtk_main ();

	/* done */
	return 0;
}
