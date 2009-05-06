

/*
 * bui_funcs.c
 * Copyright (C) 2009 Doug Penner <darwinsurvivor@gmail.com>
 *                    Brendan Neva <bneva1@my.bcit.ca>
 *                    Steffen L. Norgren <ironix@trollop.org>
 *                    Eddie Zhang <edisonhammer@gmail.com>
 * 
 * bui_funcs.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * bui_funcs.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "spry.h"
#include "gui_funcs.h"

/**
 * gui_fullscreen:
 * @conf: Spry configuration struct
 *
 * Toggles fullscreen
 **/
void
gui_fullscreen (SPRY_CONF* conf)
{
    g_print("Now toggling fullscreen: ");
    if (conf->fullscreen)
    {
        g_print("Restoring\n");
        conf->fullscreen = FALSE;
        gtk_widget_show(conf->gtk_objects->toolbar);
        gtk_widget_hide(conf->gtk_objects->toolbar_fullscreen);
        gtk_window_unfullscreen((GtkWindow*) conf->gtk_objects->main_window);
    } else {
        g_print("Fullscreening\n");
        conf->fullscreen = TRUE;
        gtk_widget_show(conf->gtk_objects->toolbar_fullscreen);
        gtk_widget_hide(conf->gtk_objects->toolbar);
        gtk_window_fullscreen((GtkWindow*) conf->gtk_objects->main_window);
    }
}

/**
 * toggle_fullscreen:
 * @conf: Spry configuration struct
 *
 * Toggles fullscreen
 **/
void
gui_minimize (SPRY_CONF* conf)
{
    g_print("Minimize\n");
}

/**
 * toggle_context:
 * @conf: Spry configuration struct
 *
 * Toggles the context menu
 **/
void
gui_context (SPRY_CONF* conf)
{
    g_print("Context Menu\n");
    printf("conf: %p\n", conf);
    printf("toggle: %i\n", conf->context_menu);
    if (conf->context_menu)
    {
        gtk_widget_hide(conf->gtk_objects->context_menu);
        gtk_widget_show(conf->gtk_objects->scrolled_window);
        conf->context_menu = FALSE;
    } else {
        gtk_widget_hide(conf->gtk_objects->scrolled_window);
        gtk_widget_show(conf->gtk_objects->context_menu);
        conf->context_menu = TRUE;
    }
}
