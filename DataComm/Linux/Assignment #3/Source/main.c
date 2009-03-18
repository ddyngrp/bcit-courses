/*------------------------------------------------------------------------------
-- SOURCE FILE:	main.c - The main entry point for the program.
-- 
-- PROGRAM:     chat
-- 
-- FUNCTIONS:   main(int argc, char *argv[]) 
-- 
-- DATE:        March 18, 2009
-- 
-- REVISIONS:   
-- 
-- DESIGNER:    Steffen L. Norgren
-- 
-- PROGRAMMER:  Steffen L. Norgren
-- 
-- NOTES: This is the main entry point for the porgram. It sets up the main
--        GUI display and assigns the values to several global variables
--        used for display output.
--
------------------------------------------------------------------------------*/

#include "signal_handler.h"
#include "client.h"

int main(int argc, char *argv[]) {
	GtkBuilder	*builder;

	gtk_init(&argc, &argv);

	builder = gtk_builder_new();
	gtk_builder_add_from_file(builder, "chat.xml", NULL);

	window_main = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
	text_client_list = GTK_WIDGET(gtk_builder_get_object(builder, "text_client_list"));
	text_chat_out = GTK_WIDGET(gtk_builder_get_object(builder, "text_chat_out"));
	text_chat_input = GTK_WIDGET(gtk_builder_get_object(builder, "text_chat_input"));
	entry_server = GTK_WIDGET(gtk_builder_get_object(builder, "entry_server"));

	gtk_builder_connect_signals(builder, NULL);
	g_object_unref(G_OBJECT(builder));

	gtk_widget_show(window_main);
	gtk_main();

	return 0;
}
