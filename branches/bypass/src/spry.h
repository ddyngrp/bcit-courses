/*
 * spry.h
 * Copyright (C) 2009 Doug Penner <darwinsurvivor@gmail.com>
 *                    Brendan Neva <bneva1@my.bcit.ca>
 *                    Steffen L. Norgren <ironix@trollop.org>
 *                    Eddie Zhang <edisonhammer@gmail.com>
 * 
 * cliopts.h is free software: you can redistribute it and/or modify it
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

#ifndef _SPRY_H_
#define _SPRY_H_

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
 * SPRY_CONF:
 * @init_url: initial url #char*
 * @fullscreen: fullscreen mode enabled #int
 * @context_menu: context menu enabled #int
 * @scrollbars: scrollbars enabled #int
 * @has_past: whether there is a previous URL #int
 * @has_future: whether there is a next URL #int
 * @window_size: the size of the browser window #int[2]
 *
 * This holds all command-line option settings as well as general configuration
 */

typedef struct _spry_gtk_objects {
    GtkWidget*      main_window;
    GtkWidget*      v_box;
    GtkWidget*      toolbar;
    GtkWidget*      toolbar_fullscreen;
    GtkWidget*      context_menu;
    GtkWidget*      scrolled_window;
    WebKitWebView*  web_view;
    
} SPRY_GTK_OBJECTS, *pSPRY_GTK_OBJECTS;

typedef struct _spry_conf {
	char	*init_url;
	int		fullscreen,
			context_menu,
			scrollbars,
			resizable,
			has_past,
			has_future;
	int		window_size[2];
    SPRY_GTK_OBJECTS* gtk_objects;
} SPRY_CONF, *pSPRY_CONF;

#endif
