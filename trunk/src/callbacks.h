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

#include "config.h"

#include "spry.h"

/* signal callbacks */
void callback_destroy       (GtkWidget*, gpointer);
void callback_minimize      (GtkWidget*, gpointer);
void callback_back          (GtkWidget*, gpointer);
void callback_home          (GtkWidget*, gpointer);
void callback_forward       (GtkWidget*, gpointer);
void callback_fullscreen    (GtkWidget*, gpointer);
void callback_forward       (GtkWidget*, gpointer);
void callback_context       (GtkWidget*, gpointer);
void callback_toolbar       (GtkWidget*, gpointer);

/* event callbacks */
gboolean event_button_expose(GtkWidget*, GdkEventExpose*, char*);

#endif
