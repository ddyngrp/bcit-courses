/*
 * generators.c
 * Copyright (C) 2009 Doug Penner <darwinsurvivor@gmail.com>
 *                    Brendan Neva <bneva1@my.bcit.ca>
 *                    Steffen L. Norgren <ironix@trollop.org>
 *                    Eddie Zhang <edisonhammer@gmail.com>
 * 
 * generators.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * generators.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "generators.h"
#include "callbacks.h"
#include "spry.h"

/**
 * generate_scrolled_window:
 * @conf: pointer to a struct of config settings
 *
 * Creates a scrolled window to put a web_view into.
 *
 * Returns: A pointer to the scrolled window.
 **/
GtkWidget*
generate_scrolled_window(SPRY_CONF* conf) {
    GtkWidget* scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    return scrolled_window;
}

/**
 * generate_main_window:
 * @conf: pointer to a struct of config settings
 *
 * Creates main window.
 *
 * Returns: A pointer to the main window.
 **/
GtkWidget*
generate_main_window(SPRY_CONF* conf) {
	GtkWidget* main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size (GTK_WINDOW (main_window), conf->window_size[0], conf->window_size[1]);
	gtk_widget_set_name (main_window, "Spry");
	g_signal_connect (G_OBJECT (main_window), "destroy", G_CALLBACK (destroy), NULL);
    return main_window;
}

/**
 * generate_web_view:
 * @conf: pointer to a struct of config settings
 *
 * Creates a WebKit web View that holds the WebKit ViewPort.
 *
 * Returns: A pointer to the Web View.
 **/
WebKitWebView*
generate_web_view(SPRY_CONF* conf) {
	WebKitWebView* web_view = WEBKIT_WEB_VIEW (webkit_web_view_new ());
    return web_view;
}
