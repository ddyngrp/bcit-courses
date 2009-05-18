/*
 * cliopts.c
 * Copyright (C) 2009 Doug Penner <darwinsurvivor@gmail.com>
 *                    Brendan Neva <bneva1@my.bcit.ca>
 *                    Steffen L. Norgren <ironix@trollop.org>
 *                    Eddie Zhang <edisonhammer@gmail.com>
 * 
 * cliopts.c is free software: you can redistribute it and/or modify it
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

#include "config.h"
#include "cliopts.h"

#include "spry.h"

/**
 * parse_args:
 * @argc: number of arguments passed in
 * @argv: the arguments passed via the command line
 *
 * Initializes the SPRY_CONF struct and then parses command-line options to set
 * the appropriate flag or setting inside the SPRY_CONF struct.
 *
 * Returns: %SPRY_CONF struct
 **/
SPRY_CONF*
parse_args(int argc, char *argv[])
{
    SPRY_CONF *conf;
    int c, option_index = 0;
    static struct option long_options[] =
    {
        {"url"                          , required_argument , 0, 'u'},
        {"fullscreen"                   , no_argument       , 0, 'f'},
        {"no-context-menu"              , no_argument       , 0, 'c'},
        {"no-scrollbars"                , no_argument       , 0, 's'},
        {"fixed-size"                   , no_argument       , 0, 'z'},
        {"toolbar-height"               , required_argument , 0, 't'},
        {"toolbar-hidden-height"        , required_argument , 0, 'T'},
        {"width"                        , required_argument , 0, 'x'},
        {"height"                       , required_argument , 0, 'y'},
        {"help"                         , no_argument       , 0, 'h'},
        {"version"                      , no_argument       , 0, 'v'},
        {0, 0, 0, 0}
    };

    conf = malloc(sizeof (SPRY_CONF));
    init_spry_conf(conf);

    while (1)
    {
        c = getopt_long(argc, argv, "u:fcszt:T:x:y:hv", long_options, &option_index);

        if (c == -1)
            break;

        switch (c)
        {
        case 0:
            /* If the option set a flag, do nothing */
            if (long_options[option_index].flag != 0)
                break;
            break;

        case 'u':
            if (strstr(optarg, "http://"))
            {
                conf->init_url = optarg;
            }
            else
            {
                conf->init_url = malloc((strlen("http://") + strlen(optarg)) * sizeof(char) + 1);
                memset(conf->init_url, '\0', sizeof (conf->init_url));
                                                  
                strcat(conf->init_url, "http://");
                strcat(conf->init_url, optarg);
            }
            break;

        case 'f':
            conf->mode = conf->mode | FULLSCREEN;
            break;

        case 'c':
            conf->features = conf->features & !CONTEXT_MENU_ENABLED;
            break;

        case 's':
            conf->features = conf->features & !SCROLLBARS_ENABLED;
            break;

        case 'z':
            conf->features = conf->features & !RESIZE_ENABLED;
            break;

        case 'x':
            conf->window_size[0] = atoi(optarg);
            break;

        case 'y':
            conf->window_size[1] = atoi(optarg);
            break;

        case 't':
            conf->toolbar_height = atoi(optarg);
            break;

        case 'T':
            conf->toolbar_fullscreen_height = atoi(optarg);
            break;

        case 'h':
            spry_usage(argv[0], OPTS_HELP);
            break;
            
        case 'v':
            g_print("Spry - Gtk+ WebKit Browser Version %s\n", VERSION);
            exit(0);
            break;
            
        default:
            spry_usage(argv[0], OPTS_ERROR);
            break;
        }
    }

    return conf;
}

/**
 * init_spry_conf:
 * @conf: pointer to the #SPRY_CONF struct
 *
 * Initializes the SPRY_CONF struct with default values.
 **/
void
init_spry_conf(SPRY_CONF* conf)
{
    conf->init_url                  = "http://www.google.ca";
    conf->features                  = SCROLLBARS_ENABLED | CONTEXT_MENU_ENABLED | RESIZE_ENABLED;
    conf->mode                      = TOOLBAR;
    conf->browser_status            = 0;
    conf->window_size[0]            = DEFAULT_WIDTH;
    conf->window_size[1]            = DEFAULT_HEIGHT;
    conf->toolbar_height            = DEFAULT_TOOLBAR_HEIGHT;
    conf->toolbar_fullscreen_height = DEFAULT_TOOLBAR_FULLSCREEN_HEIGHT;
}

/**
 * spry_usage:
 * @command: the command to load the program (e.g. "./spry")
 * @err: the type of error that initiated this function
 *
 * Prints out the command-line usage for the application as well as handling
 * command-line option errors.
 **/
void
spry_usage(char* command, int err)
{
    if (err == OPTS_HELP)
    {
        g_print("Spry - Gtk+ WebKit Browser Version %s\n\n", VERSION);
        g_print("usage: spry [arguments]\n\n");
        g_print("Arguments:\n");
        g_print("  -u         or  --url                               The URL of the website to load\n");
        g_print("  -f         or  --fullscreen                        Enable fullscreen mode\n");
        g_print("  -c         or  --no-context-menu                   Disable context menu\n");
        g_print("  -s         or  --no-scrollbars                     Disable scrollbars\n");
        g_print("  -t [size]  or  --toolbar-height [size]             Set the height of the toolbar\n");
        g_print("  -T [size]  or  --toolbar-fullscreen-height [size]  Set the height of the fullscreen toolbar\n");
        g_print("  -z         or  --fixed-size                        Disable resizing\n");
        g_print("  -x [size]  or  --width [size]                      Set the width of the window\n");
        g_print("  -y [size]  or  --height [size]                     Set the height of the window\n");
        g_print("  -h         or  --help                              Prints out this screen\n");
        g_print("  -v         or  --version                           Prints out version information\n");
    }
    else if (err == OPTS_ERROR)
    {
        g_print ("Try `spry --help` for more information.\n");
    } else {
        g_print ("%s: unknown error\n", command);
        g_print ("Try `spry --help` for more information.\n");
    }
    
    exit(err);
}
