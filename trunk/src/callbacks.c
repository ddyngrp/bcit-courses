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

#include "spry.h"
#include "callbacks.h"
#include "browser.h"
#include "gui_funcs.h"

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
	gui_minimize ((SPRY_CONF*)data);
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
    browser_back((SPRY_CONF*) data);
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
    browser_forward((SPRY_CONF*) data);
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
    gui_fullscreen(data);
}
