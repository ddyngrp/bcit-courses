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

void on_btn_client_activate(GtkWidget *window_client);
void on_btn_server_activate(GtkWidget *window_server);
void on_help_about_activate(GtkWidget *dialogue_about);
void on_server_file_listen_activate();
void on_server_view_clear_activate();
void on_file_connect_activate(GtkWidget *dialogue_client_connect);
void on_btn_connect_activate();
void on_client_view_clear_activate();
void on_btn_clear_activate();
void on_btn_send_activate();
void on_file_save_log_activate();
void on_file_quit_activate();
void on_window_destroy();

#endif
