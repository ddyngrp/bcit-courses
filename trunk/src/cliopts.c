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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "spry.h"
#include "cliopts.h"

SPRY_CONF* parse_args(int argc, char *argv[]) {
	SPRY_CONF *conf;
	int	c;

	conf = malloc(sizeof(SPRY_CONF));

	while (1) {
		static struct option long_options[] =
		{
			/* These options set a flag */
			{"fullscreen", no_argument, 0, 1},
			{"f", no_argument, 0, 1},
			/* These options set a value */
			{"width", required_argument, 0, 'w'},
			{"height", required_argument, 0, 'h'},
			{0, 0, 0, 0}
		};
	}

	return conf;
}

void init_spry_conf(SPRY_CONF* conf) {
}
