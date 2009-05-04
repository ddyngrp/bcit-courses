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

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _spry_conf {
	char	*init_url;		/* initial URL passed via command line */
	int		fullscreen,		/* enable / disalbe fullscreen */
			context_menu,	/* enable / disable context menu */
			scrollbars,		/* enable / disable scrollbars */
			has_past,		/* whether there pages in the history */
			has_future;		/* whether there are pages in the future */
	int		window_size[2];	/* the initial size of the window in x,y */
} SPRY_CONF, *PSPRY_CONF;
