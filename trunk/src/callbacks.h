/*
 * callbacks.h
 * Copyright (C) 2009 Doug Penner <darwinsurvivor@gmail.com>
 *                    Brendan Neva <bneva1@my.bcit.ca>
 *                    Steffen L. Norgren <ironix@trollop.org>
 *                    Eddie Zhang <edisonhammer@gmail.com>
 * 
 * callbacks.h is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * callbacks.h is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _CALLBACKS_H
#define _CALLBACKS_H

#include "spry.h"

/* signal callbacks */
void callback_destroy       (GtkWidget* widget, gpointer data);
void callback_minimize      (GtkWidget* widget, gpointer data);
void callback_back          (GtkWidget* widget, gpointer data);
void callback_home          (GtkWidget* widget, gpointer data);
void callback_forward       (GtkWidget* widget, gpointer data);
void callback_fullscreen    (GtkWidget* widget, gpointer data);
void callback_forward       (GtkWidget* widget, gpointer data);
void callback_context       (GtkWidget* widget, gpointer data);
void callback_toolbar       (GtkWidget* widget, gpointer data);
void callback_ignore        (GtkWidget* widget, gpointer data);

/* event callbacks */
gboolean event_button_expose(GtkWidget *draw, GdkEventExpose *event, char* icon_name );

#endif
