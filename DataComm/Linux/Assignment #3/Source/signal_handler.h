#ifndef _SIGNAL_HANDLER_H_
#define _SIGNAL_HANDLER_H_

#include <gtk/gtk.h>
#include <pthread.h>
#include <stdio.h>

GtkWidget	*window_main;		/* This window gets hidden after the user choses client/server mode */
GtkWidget	*text_client_list;	/* output for connected clients */
GtkWidget	*text_chat_out;		/* chat output */
GtkWidget	*text_chat_input;	/* chat input */
GtkWidget	*entry_server;		/* server IP or name */

#endif
