/*
 * generators.c
 * Copyright (C) 2009 Doug Penner <darwinsurvivor@gmail.com>
 *                    Brendan Neva <bneva1@my.bcit.ca>
 *                    Steffen L. Norgren <ironix@trollop.org>
 *                    Eddie Zhang <edisonhammer@gmail.com>
 * 
 * generators.c is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * generators.c is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "generators.h"
#include "callbacks.h"
#include "spry.h"

/**
 * generate_gui:
 * @conf: pointer to a struct of config settings
 *
 * Creates a the entire gui (main window).
 **/
void
generate_gui (SPRY_CONF* conf)
{
    
    SPRY_GTK_OBJECTS* gtk_objects = malloc (sizeof (SPRY_GTK_OBJECTS));
    
    conf->gtk_objects = gtk_objects;
    
    /* Create GTK Objects */
	gtk_objects->main_window        = generate_main_window(conf);       /* Main Window */
    gtk_objects->v_box              = gtk_vbox_new(FALSE, 0);           /* holds all the toolbars */
    gtk_objects->toolbar            = generate_toolbar(conf);
    gtk_objects->toolbar_fullscreen = generate_toolbar_fullscreen(conf);
    gtk_objects->scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_objects->web_view           = WEBKIT_WEB_VIEW (webkit_web_view_new ());
    
    /* Configure scrolled window */
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (gtk_objects->scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	
	/* Put GTK Objects inside each-other and make them visible */
	gtk_container_add   (GTK_CONTAINER (gtk_objects->main_window)       , gtk_objects->v_box                );
    gtk_container_add   (GTK_CONTAINER (gtk_objects->scrolled_window)   , GTK_WIDGET (gtk_objects->web_view));
    gtk_box_pack_end    ((GtkBox*)      gtk_objects->v_box              , gtk_objects->toolbar              , FALSE, FALSE, 0);
    gtk_box_pack_end    ((GtkBox*)      gtk_objects->v_box              , gtk_objects->toolbar_fullscreen   , FALSE, FALSE, 0);
	gtk_box_pack_end    ((GtkBox*)      gtk_objects->v_box              , gtk_objects->scrolled_window      , FALSE, FALSE, 0);
    
    /* Connect Signals */
	g_signal_connect (G_OBJECT (gtk_objects->main_window), "destroy", G_CALLBACK (destroy), NULL);
    
    /* Make all objects visible */
	gtk_widget_grab_focus (GTK_WIDGET (gtk_objects->web_view));
	gtk_widget_show_all (gtk_objects->main_window);
}

/**
 * generate_toolbar_fullscreen:
 * @conf: pointer to a struct of config settings
 *
 * Creates the fullscreen toolbar for the top (fullscreen mode)
 *
 * Returns: A pointer to the toolbar.
 **/
GtkWidget*
generate_toolbar_fullscreen (SPRY_CONF* conf)
{
    /* Declarations */
    GtkWidget*  toolbar_fullscreen;
    GtkWidget*  fullscreen;
    GtkWidget*  close;
    
    /* Create buttons */
    toolbar_fullscreen  = gtk_hbutton_box_new();
    fullscreen          = gtk_button_new_with_label("[]");
    close               = gtk_button_new_with_label("X");
    
    /* Add buttons to toolbar */
    gtk_container_add (GTK_CONTAINER (toolbar_fullscreen), fullscreen);
    gtk_container_add (GTK_CONTAINER (toolbar_fullscreen), close);
    
    /* Connect buttons to actions */
	g_signal_connect (G_OBJECT (fullscreen) , "clicked", G_CALLBACK (toggle_fullscreen) , conf);
	g_signal_connect (G_OBJECT (close)      , "clicked", G_CALLBACK (destroy)           , NULL);
    
    /* Return toolbar */
    return toolbar_fullscreen;
}

/**
 * generate_toolbar:
 * @conf: pointer to a struct of config settings
 *
 * Creates the toolbar for the top (restored mode)
 *
 * Returns: A pointer to the toolbar.
 **/
GtkWidget*
generate_toolbar (SPRY_CONF* conf)
{
    /* Declarations */
    GtkWidget*  toolbar;
    GtkWidget*  back;
    GtkWidget*  forward;
    GtkWidget*  fullscreen;
    GtkWidget*  minimize;
    GtkWidget*  close;
    
    /* Create buttons */
    toolbar     = gtk_hbutton_box_new();
    back        = gtk_button_new_with_label("<-");
    forward     = gtk_button_new_with_label("->");
    fullscreen  = gtk_button_new_with_label("[]");
    minimize    = gtk_button_new_with_label("-");
    close       = gtk_button_new_with_label("X");
    
    /* Add buttons to toolbar */
    gtk_container_add (GTK_CONTAINER (toolbar), back);
    gtk_container_add (GTK_CONTAINER (toolbar), forward);
    gtk_container_add (GTK_CONTAINER (toolbar), fullscreen);
    gtk_container_add (GTK_CONTAINER (toolbar), minimize);
    gtk_container_add (GTK_CONTAINER (toolbar), close);
    
    /* Configure objects */
    gtk_widget_set_size_request (back, 10, 10);
    
    /* Connect buttons to actions */
	g_signal_connect (G_OBJECT (fullscreen) , "clicked", G_CALLBACK (toggle_fullscreen) , conf);
	g_signal_connect (G_OBJECT (back)       , "clicked", G_CALLBACK (do_nothing)        , NULL);
	g_signal_connect (G_OBJECT (forward)    , "clicked", G_CALLBACK (do_nothing)        , NULL);
	g_signal_connect (G_OBJECT (minimize)   , "clicked", G_CALLBACK (do_nothing)        , NULL);
	g_signal_connect (G_OBJECT (close)      , "clicked", G_CALLBACK (destroy)           , NULL);
    
    /* Return toolbar */
    return toolbar;
}

/**
 * generate_main_window:
 * @conf: pointer to a struct of config settings
 *
 * Creates main window.
 *
 * Returns: A pointer to the main window.
 **/
GtkWidget*
generate_main_window (SPRY_CONF* conf)
{
	GtkWidget* main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size (GTK_WINDOW (main_window), conf->window_size[0], conf->window_size[1]);
	gtk_widget_set_name (main_window, "Spry");
	g_signal_connect (G_OBJECT (main_window), "destroy", G_CALLBACK (destroy), NULL);
    return main_window;
}
