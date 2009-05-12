/*
 * gui_funcs.c
 * Copyright (C) 2009 Doug Penner <darwinsurvivor@gmail.com>
 *                    Brendan Neva <bneva1@my.bcit.ca>
 *                    Steffen L. Norgren <ironix@trollop.org>
 *                    Eddie Zhang <edisonhammer@gmail.com>
 * 
 * gui_funcs.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gui_funcs.c is distributed in the hope that it will be useful, but
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
 * gui_apply_mode:
 * @conf: Spry configuration struct
 * 
 * Applies settings defined in the configuration struct
 **/
void
gui_apply_mode (SPRY_CONF* conf) {
    /* fullscreen */
    if (conf->mode & FULLSCREEN)
    {
        gtk_window_fullscreen((GtkWindow*) conf->gtk_objects->main_window);
    } else {
        gtk_window_unfullscreen((GtkWindow*) conf->gtk_objects->main_window);
    }
    
    /* context menu */
    if (conf->mode & CONTEXT)
    {
        gtk_widget_show(conf->gtk_objects->context_menu);
        gtk_widget_hide(conf->gtk_objects->scrolled_window);
    } else {
        gtk_widget_show(conf->gtk_objects->scrolled_window);
        gtk_widget_hide(conf->gtk_objects->context_menu);
    }
    
    /* toolbar */
    if (conf->mode & TOOLBAR)
    {
        gtk_widget_show(conf->gtk_objects->toolbar);
        gtk_widget_hide(conf->gtk_objects->toolbar_fullscreen);
    } else {
        gtk_widget_show(conf->gtk_objects->toolbar_fullscreen);
        gtk_widget_hide(conf->gtk_objects->toolbar);
    }
    
    /* minimize */
    if (conf->mode & MINIMIZE)
    {
        gtk_window_iconify((GtkWindow*) conf->gtk_objects->main_window);
        DISABLE(conf->mode, MINIMIZE);
    }
}
