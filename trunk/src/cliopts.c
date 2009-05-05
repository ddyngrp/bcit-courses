/*
 * cliopts.c
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
 * cliopts.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "spry.h"
#include "cliopts.h"

SPRY_CONF* parse_args (int argc, char *argv[])
{
	SPRY_CONF *conf;
	int	c, option_index = 0;
	static struct option long_options[] =
	{
		{"fullscreen", no_argument, 0, 'f'},
		{"no-context-menu", no_argument, 0, 'c'},
		{"no-scrollbars", no_argument, 0, 's'},
		{"fixed-size", no_argument, 0, 'z'},
		{"width", required_argument, 0, 'w'},
		{"height", required_argument, 0, 'h'},
		{0, 0, 0, 0}
	};

	conf = malloc (sizeof (SPRY_CONF));
	init_spry_conf (conf);

	while (1) {
		c = getopt_long (argc, argv, "fcszw:h:", long_options, &option_index);

		if (c == -1) {
			spry_usage ();
			break;
		}

		switch (c)
		{
			case 0:
				if (long_options[option_index].flag != 0) {
					spry_usage ();
					break;
				}
				printf ("option %s", long_options[option_index].name);
				break;
			default:
				spry_usage ();
				break;
		}
	}

	return conf;
}

void init_spry_conf (SPRY_CONF* conf)
{
	conf->init_url = "http://www.google.ca";
	conf->fullscreen = 0;
	conf->context_menu = 1;
	conf->scrollbars = 1;
	conf->resizable = 1;
	conf->has_past = 0;
	conf->has_future = 0;
	conf->window_size[0] = 320;
	conf->window_size[1] = 240;
}

void spry_usage () {
	g_print ("Usage...\n");
	/* exit (OPTS_ERROR); */
}
