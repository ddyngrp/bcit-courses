/*
 * spry.h
 * Copyright (C) 2009 Doug Penner <darwinsurvivor@gmail.com>
 *                    Brendan Neva <bneva1@my.bcit.ca>
 *                    Steffen L. Norgren <ironix@trollop.org>
 *                    Eddie Zhang <edisonhammer@gmail.com>
 * 
 * spry.h is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * spry.h is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * SECTION:spry
 * @short_description: the spry module
 * @stability: Stable
 *
 * This module handles all WebKitGtk browser navigation functions.
 */

#ifndef spry_h
#define spry_h

#include "config.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <webkit/webkit.h>


/**
 * SPRY_GTK_OBJECTS:
 * @main_window: the main container window #GtkWidget*
 * @v_box: the virtical container box for the #GtkWidget*
 * @toolbar: the top toolbar #GtkWidget*
 * @toolbar_fullscreen: the fullscreen toolbar #GtkWidget*
 * @context_menu: the context menu #GtkWidget*
 * @web_view_container: the container for the web view #GtkWidget*
 * @web_view: the actual web view #WebKitWebView*
 *
 * This holds main gtk objects used in the window
 */
typedef struct _spry_gtk_objects {
	/*< public >*/
    GtkWidget*      main_window;
    GtkWidget*      v_box;
    GtkWidget*      toolbar;
    GtkWidget*      toolbar_fullscreen;
    GtkWidget*      context_menu;
    GtkWidget*      web_view_container;
    WebKitWebView*  web_view;
    
} SPRY_GTK_OBJECTS;

/**
 * SPRY_CONF:
 * @init_url: initial url #char*
 * @features: a bitmask holding all browser features #int
 * @mode: whether the browser is in fullscreen or not #int[2]
 * @window_size: the size of the browser window #int[2]
 * @toolbar_height: the height of the normal toolbar #int
 * @toolbar_fullscreen_height: the height of a fullscreen toolbar #int
 * @gtk_objects: pointer to the Gtk+ object struct #SPRY_GTK_OBJECTS
 *
 * This holds all command-line option settings as well as general configuration
 */
typedef struct _spry_conf {
	/*< public >*/
    char    *init_url;
    int     features;
	int		mode;
    int     window_size[2];
    int     toolbar_height;
    int     toolbar_fullscreen_height;
    SPRY_GTK_OBJECTS* gtk_objects;
} SPRY_CONF;

/**
 * ENABLE:
 * @x:  the #SPRY_CONF %features to be modified 
 * @y:  the %features to enable
 *
 * Enables one of the following #SPRY_CONF %features
 * #FULLSCREEN_ENABLED, #SCROLLBARS_ENABLED, #CONTEXT_MENU_ENABLED,
 * #RESIZE_ENABLED, #TOOLBAR_ENABLED, #TOOLBAR_FULLSCREEN_ENABLED,
 * #HIGHLIGHTING_ENABLED
 */
#define ENABLE(x, y)    x->features |= y;

/**
 * DISABLE:
 * @x:  the #SPRY_CONF %features to be modified 
 * @y:  the %features to disable
 *
 * Disables one of the following #SPRY_CONF %features
 * #FULLSCREEN_ENABLED, #SCROLLBARS_ENABLED, #CONTEXT_MENU_ENABLED,
 * #RESIZE_ENABLED, #TOOLBAR_ENABLED, #TOOLBAR_FULLSCREEN_ENABLED,
 * #HIGHLIGHTING_ENABLED
 */
#define DISABLE(x, y)   x->features &= ~y;

/**
 * ENABLED:
 * @x:  the #SPRY_CONF %features to be checked 
 * @y:  the %features to check if enabled
 *
 * Checks to see if one of the following #SPRY_CONF %features is enabled
 * #FULLSCREEN_ENABLED, #SCROLLBARS_ENABLED, #CONTEXT_MENU_ENABLED,
 * #RESIZE_ENABLED, #TOOLBAR_ENABLED, #TOOLBAR_FULLSCREEN_ENABLED,
 * #HIGHLIGHTING_ENABLED
 *
 * Returns: a boolean value
 */
#define ENABLED(x, y)   (x->features & y)   

/**
 * DISABLED:
 * @x:  the #SPRY_CONF %features to be checked 
 * @y:  the %features to check if disabled
 *
 * Checks to see if one of the following #SPRY_CONF %features is disabled
 * #FULLSCREEN_ENABLED, #SCROLLBARS_ENABLED, #CONTEXT_MENU_ENABLED,
 * #RESIZE_ENABLED, #TOOLBAR_ENABLED, #TOOLBAR_FULLSCREEN_ENABLED,
 * #HIGHLIGHTING_ENABLED
 *
 * Returns: a boolean value
 */
#define DISABLED(x, y)  (!(x->features & y))

/**
 * TOGGLE:
 * @x:  the #SPRY_CONF %mode to be modified 
 * @y:  the %mode to toggle to
 *
 * Toggles between #FULLSCREEN, #TOOLBAR, #CONTEXT, and #MINIMIZE %mode
 */
#define TOGGLE(x, y)    x = ((x & y) ? (x & ~y) : (x | y));

/**
 * SHOW:
 * @x:  the #SPRY_CONF %mode to be set to visible 
 * @y:  the %mode to initiate to visible
 *
 * Sets one of the following #SPRY_CONF %mode to visible
 * #FULLSCREEN, #TOOLBAR, #CONTEXT, #MINIMIZE
 */
#define SHOW(x, y)      x->mode |= y;

/**
 * HIDE:
 * @x:  the #SPRY_CONF %mode to be set to hidden 
 * @y:  the %mode to initiate to hidden
 *
 * Sets one of the following #SPRY_CONF %mode to hidden
 * #FULLSCREEN, #TOOLBAR, #CONTEXT, #MINIMIZE
 */
#define HIDE(x, y)      x->mode &= ~y;

/**
 * VISIBLE:
 * @x:  the #SPRY_CONF %mode to check
 * @y:  the %mode to check if visible
 *
 * Checks one of the following #SPRY_CONF %mode for visibility
 * #FULLSCREEN, #TOOLBAR, #CONTEXT, #MINIMIZE
 *
 * Returns: a boolean value
 */
#define VISIBLE(x, y)   (x->mode & y)

/**
 * HIDDEN:
 * @x:  the #SPRY_CONF %mode to check
 * @y:  the %mode to check if hidden
 *
 * Checks one of the following #SPRY_CONF %mode for visibility
 * #FULLSCREEN, #TOOLBAR, #CONTEXT, #MINIMIZE
 *
 * Returns: a boolean value
 */
#define HIDDEN(x, y)    (!(x->mode & y))

/* defaults */
#define DEFAULT_TOOLBAR_HEIGHT            30;
#define DEFAULT_TOOLBAR_FULLSCREEN_HEIGHT 10;
#define DEFAULT_WIDTH                     320;
#define DEFAULT_HEIGHT                    240;

/* modes */
#define FULLSCREEN  0x1
#define TOOLBAR     0x2
#define CONTEXT     0x4
#define MINIMIZE    0x8

/* features_enabled */
#define FULLSCREEN_ENABLED          0x1
#define SCROLLBARS_ENABLED          0x2
#define CONTEXT_MENU_ENABLED        0x4
#define RESIZE_ENABLED              0x8
#define TOOLBAR_ENABLED             0x10
#define TOOLBAR_FULLSCREEN_ENABLED  0x20
#define HIGHLIGHTING_ENABLED        0x40

#endif
