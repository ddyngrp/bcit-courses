#include "signal_handler.h"
#include "client.h"
#include "server.h"

void on_btn_client_activate(GtkWidget *window_client) {
	gtk_widget_hide(window_main);
	gtk_widget_show(window_client);
}

void on_btn_server_activate(GtkWidget *window_server) {
	gtk_widget_hide(window_main);
	gtk_widget_show(window_server);
}

void on_help_about_activate(GtkWidget *dialogue_about) {
	gtk_dialog_run(GTK_DIALOG(dialogue_about));
	gtk_widget_hide(dialogue_about);
}

void on_server_file_listen_activate() {
	pthread_t server_thread;

	/* Create the server thread */
	pthread_create(&server_thread, NULL, &start_server, (void *)NULL);
}

void on_server_view_clear_activate() {
	GtkTextBuffer   *buffer;
	GtkTextIter		start, end;

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_client_list));
	gtk_text_buffer_get_bounds(buffer, &start, &end);
	
	gtk_text_buffer_delete(buffer, &start, &end);
}

void on_file_connect_activate(GtkWidget *dialogue_client_connect) {
	gtk_dialog_run(GTK_DIALOG(dialogue_client_connect));
	gtk_widget_hide(dialogue_client_connect);
}

void on_btn_connect_activate() {
	const gchar	*server;
	pthread_t	client_thread;
	int			r;

	server = gtk_entry_get_text(GTK_ENTRY(entry_server));

	if ((r = start_client(server)) == -1) {
		append_text("Error: connection failed\n");
	}
	else { /* start read thread */
		pthread_create(&client_thread, NULL, &client_recv, (void *)NULL);
	}
}

void on_client_view_clear_activate() {
	GtkTextBuffer   *buffer;
	GtkTextIter		start, end;

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_chat_out));
	gtk_text_buffer_get_bounds(buffer, &start, &end);
	
	gtk_text_buffer_delete(buffer, &start, &end);
}

void on_btn_clear_activate() {
	GtkTextBuffer   *buffer;
	GtkTextIter		start, end;

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_chat_input));
	gtk_text_buffer_get_bounds(buffer, &start, &end);
	
	gtk_text_buffer_delete(buffer, &start, &end);
}

void on_btn_send_activate() {
	GtkTextBuffer	*buffer;
	GtkTextIter		start, end;
	gchar			*text;

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_chat_input));
	gtk_text_buffer_get_bounds(buffer, &start, &end);

	text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);

	client_send(text);	

	on_btn_clear_activate();
}

void on_file_save_log_activate() {
	GtkTextBuffer	*buffer;
	GtkTextIter		start, end;
	gchar			*text;
	FILE *ofp;

	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_chat_out));
	gtk_text_buffer_get_bounds(buffer, &start, &end);

	text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);

	ofp = fopen("./chat_log.txt", "w");
	fprintf(ofp, "%s", text);
	fclose(ofp);
}

void on_file_quit_activate() {
	gtk_main_quit();
}

void on_window_destroy() {
	gtk_main_quit();
}
