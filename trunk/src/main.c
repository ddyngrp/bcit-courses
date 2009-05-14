/*
 * main.c
 * Copyright (C) 2009 Doug Penner <darwinsurvivor@gmail.com>
 *                    Brendan Neva <bneva1@my.bcit.ca>
 *                    Steffen L. Norgren <ironix@trollop.org>
 *                    Eddie Zhang <edisonhammer@gmail.com>
 * 
 * main.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * main.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "spry.h"
#include "cliopts.h"
#include "generators.h"
#include "callbacks.h"
#include "gui_funcs.h"
#include "browser.h"

/**
 * main:
 * @argc: number of arguments passed in
 * @argv: the arguments passed via the command line
 *
 * Creates a new browser window that points to a URL that was passed
 * in cia @argv
 *
 * Returns: %0 if the operation succeeded, else %1.
 **/

int
main (int argc, char *argv[])
{
    /* Declare conf struct */
	SPRY_CONF*		conf;

	/* sets the gtk locale for the current system */
	gtk_set_locale ();

	/* grap gtk-specific arguments and apply accordingly */
	gtk_init (&argc, &argv);

	/* check for g_thread support */
	if (!g_thread_supported ())
    {
		g_thread_init (NULL);
	}
	
	/* parse command line arguments and return the initial struct */
	conf = parse_args(argc, argv);
    
    /* Create the GUI (main window) */
    conf->gtk_objects = generate_gui(conf);
    
    /* apply gui settings */
    gui_apply_mode(conf);
	
	/* load the web page */
    browser_open(conf, (gchar*)conf->init_url);

	/* Start GTK */
	gtk_main();

	/* done */
	return 0;
}
