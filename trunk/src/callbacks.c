/*
 * callbacks.c
 * Copyright (C) 2009 Doug Penner <darwinsurvivor@gmail.com>
 *                    Brendan Neva <bneva1@my.bcit.ca>
 *                    Steffen L. Norgren <ironix@trollop.org>
 *                    Eddie Zhang <edisonhammer@gmail.com>
 * 
 * callbacks.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * callbacks.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"
#include "callbacks.h"

#include "browser.h"
#include "gui_funcs.h"
#include "spry.h"

/**
 * callback_destroy:
 * @widget: The widget that called the function
 * @data: Any additional data passed to the function
 *
 * Closes the program when the window is closed.
 **/
void
callback_destroy (GtkWidget* widget, gpointer data)
{
    gtk_main_quit ();
}

/**
 * callback_minimize:
 * @widget: The widget that called the function
 * @data: Any additional data passed to the function
 *
 * Minimizes the window.
 **/
void
callback_minimize (GtkWidget* widget, gpointer data)
{
    SPRY_CONF* conf = (SPRY_CONF*) data;
    TOGGLE(conf->mode, MINIMIZE);
    DISABLE(conf->mode, CONTEXT);
    gui_apply_mode(conf);
}

/**
 * callback_back:
 * @widget: The button that was clicked
 * @data: pointer to SPRY_CONF struct
 * 
 * Goes back in history
 **/
void
callback_back (GtkWidget* widget, gpointer data)
{
    SPRY_CONF* conf = (SPRY_CONF*) data;
    browser_back(conf);
    if (conf->mode & CONTEXT)
    {
        DISABLE(conf->mode, CONTEXT);
        gui_apply_mode(conf);
    }
}

/**
 * callback_forward:
 * @widget: The button that was clicked
 * @data: pointer to SPRY_CONF struct
 * 
 * Goes forward in history
 **/
void
callback_forward (GtkWidget* widget, gpointer data)
{
    SPRY_CONF* conf = (SPRY_CONF*) data;
    browser_forward(conf);
    if (conf->mode & CONTEXT)
    {
        DISABLE(conf->mode, CONTEXT);
        gui_apply_mode(conf);
    }
}

/**
 * callback_home:
 * @widget: The button that was clicked
 * @data: pointer to SPRY_CONF struct
 * 
 * Goes to the home page.
 **/
void
callback_home (GtkWidget* widget, gpointer data)
{
    SPRY_CONF* conf = (SPRY_CONF*) data;
    browser_home(conf);
    if (conf->mode & CONTEXT)
    {
        DISABLE(conf->mode, CONTEXT);
        gui_apply_mode(conf);
    }
}

/**
 * callback_fullscreen:
 * @widget: The widget that called the function
 * @data: Spry Config Struct
 *
 * Does nothing on an event (for capturing events)
 **/
void
callback_fullscreen (GtkWidget* widget, gpointer data)
{
    SPRY_CONF* conf = (SPRY_CONF*) data;
    TOGGLE(conf->mode, FULLSCREEN);
    DISABLE(conf->mode, CONTEXT);
    gui_apply_mode(conf);
}

/**
 * callback_context:
 * @widget: The widget that called the function
 * @data: Spry Config Struct
 *
 * Called when the context menu is requested.
 **/
void
callback_context (GtkWidget* widget, gpointer data)
{
    SPRY_CONF* conf = (SPRY_CONF*) data;
    TOGGLE(conf->mode, CONTEXT);
    gui_apply_mode(conf);
}

/**
 * callback_toolbar:
 * @widget: The widget that called the function
 * @data: Spry Config Struct
 *
 * Called when the toolbar is toggled.
 **/
void
callback_toolbar (GtkWidget* widget, gpointer data)
{
    SPRY_CONF* conf = (SPRY_CONF*) data;
    TOGGLE(conf->mode, TOOLBAR);
    DISABLE(conf->mode, CONTEXT);
    gui_apply_mode(conf);
}

/**
 * callback_ignores:
 * @widget: The widget that called the function
 * @data: Spry Config Struct
 *
 * Ignores a signal (basically mutes it).
 **/
void
callback_ignore (GtkWidget* widget, gpointer data)
{
    g_print("signal ignored\n");
}


/**
 * event_button_expose:
 * @draw: unused
 * @event: event containing the window
 * @icon_name: icon filename.
 *
 * Creates a resizable button.
 * TODO: customize and make it our own
 *
 * Returns: FALSE.
 **/
gboolean
event_button_expose(GtkWidget*  draw,
           GdkEventExpose*      event,
           char*                icon_name)
{
    /* declarations */
    gchar*     filename;
    GdkPixbuf* pixbuf;
    gint       pw, ph, dw, dh, x, y;
    GError*    error = NULL;

    /* Create filename from data */
    filename = g_strdup_printf("images/%s.svg", icon_name);

    /* Get drawing area dimensions */
    gdk_drawable_get_size(GDK_DRAWABLE( event->window ), &dw, &dh);

    /* Load pixbuf from file */
    pixbuf = gdk_pixbuf_new_from_file_at_size(filename, dw, dh, &error);
    g_free(filename);
    if(error)
    {
        g_print("Error: %s\n", error->message);
        return(FALSE);
    }

    /* Calculate x and y position to center the image */
    pw = gdk_pixbuf_get_width( pixbuf );
    ph = gdk_pixbuf_get_height( pixbuf );
    x = (dw - pw) / 2;
    y = (dh - ph) / 2;

    /* Draw pixbuf */
    gdk_draw_pixbuf(GDK_DRAWABLE( event->window), NULL, pixbuf, 0, 0,
                     x, y, -1, -1, GDK_RGB_DITHER_NONE, 0, 0);
    g_object_unref(G_OBJECT(pixbuf));

    return(FALSE);
}
