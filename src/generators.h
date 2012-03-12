/*
 * callbacks.h
 * Copyright (C) 2009 Doug Penner <darwinsurvivor@gmail.com>
 *                    Brendan Neva <bneva1@my.bcit.ca>
 *                    Steffen L. Norgren <ironix@trollop.org>
 *                    Eddie Zhang <edisonhammer@gmail.com>
 * 
 * generators.h is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * generators.h is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef generators_h
#define generators_h

#include "config.h"

#include "spry.h"

SPRY_GTK_OBJECTS*   generate_gui            (SPRY_CONF* conf);
GtkWidget*          generate_main_window    (SPRY_CONF* conf);
GtkWidget*          generate_context_menu   (SPRY_CONF* conf);
GtkWidget*          generate_toolbar        (SPRY_CONF* conf);
GtkWidget*          generate_thinbar        (SPRY_CONF* conf);
GtkWidget*          generate_button         (char* icon_name);

#endif
