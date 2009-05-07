/*
 * browser.c
 * Copyright (C) 2009 Doug Penner <darwinsurvivor@gmail.com>
 *                    Brendan Neva <bneva1@my.bcit.ca>
 *                    Steffen L. Norgren <ironix@trollop.org>
 *                    Eddie Zhang <edisonhammer@gmail.com>
 * 
 * browser.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * browser.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "spry.h"
#include "browser.h"

/**
 * browser_open:
 * @conf: Spry configuration struct
 * @url: The url to open
 *
 * Opens a page.
 **/
void
browser_open (SPRY_CONF* conf, char* url)
{
    webkit_web_view_open (conf->gtk_objects->web_view, (gchar*)url);
}

/**
 * browser_home:
 * @conf: Spry configuration struct
 *
 * Goes to homepage (specified at application launch).
 **/
void
browser_home (SPRY_CONF* conf)
{
    browser_open(conf, conf->init_url);
}

/**
 * browser_back:
 * @conf: Spry configuration struct
 *
 * Goes back in history.
 **/
void browser_back (SPRY_CONF* conf)
{
    webkit_web_view_go_back (conf->gtk_objects->web_view);
}

/**
 * browser_forward:
 * @conf: Spry configuration struct
 *
 * Goes forward in history.
 **/
void browser_forward (SPRY_CONF* conf)
{
    webkit_web_view_go_forward (conf->gtk_objects->web_view);
}
