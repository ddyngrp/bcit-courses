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
#include "browser.h"
#include "callbacks.h"
#include "spry.h"

/**
 * generate_gui:
 * @conf: pointer to a struct of config settings
 *
 * Creates a the entire gui (main window).
 **/
SPRY_GTK_OBJECTS*
generate_gui (SPRY_CONF* conf)
{
    
    SPRY_GTK_OBJECTS* gtk_objects = malloc (sizeof (SPRY_GTK_OBJECTS));
    
    /* Create GTK Objects */
	gtk_objects->main_window        = generate_main_window(conf);       /* Main Window */
    gtk_objects->v_box              = gtk_vbox_new(FALSE, 0);           /* holds all the toolbars */
    gtk_objects->toolbar            = generate_toolbar(conf);
    gtk_objects->toolbar_fullscreen = generate_toolbar_fullscreen(conf);
    gtk_objects->context_menu       = generate_context_menu (conf);
    gtk_objects->scrolled_window    = gtk_scrolled_window_new (NULL, NULL);
	gtk_objects->web_view           = WEBKIT_WEB_VIEW (webkit_web_view_new ());
    
    /* Configure scrolled window */
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (gtk_objects->scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	
	/* Put GTK Objects inside each-other and make them visible */
	gtk_container_add   (GTK_CONTAINER (gtk_objects->main_window)       , gtk_objects->v_box                );
    gtk_container_add   (GTK_CONTAINER (gtk_objects->scrolled_window)   , GTK_WIDGET (gtk_objects->web_view));
    gtk_box_pack_start    ((GtkBox*)      gtk_objects->v_box              , gtk_objects->toolbar              , FALSE, FALSE, 0);
    gtk_box_pack_start    ((GtkBox*)      gtk_objects->v_box              , gtk_objects->toolbar_fullscreen   , FALSE, FALSE, 0);
    gtk_box_pack_start    ((GtkBox*)      gtk_objects->v_box              , gtk_objects->context_menu         , TRUE , TRUE , 0);
	gtk_box_pack_start    ((GtkBox*)      gtk_objects->v_box              , gtk_objects->scrolled_window      , TRUE , TRUE , 0);
    
    /* show objects */
	gtk_widget_grab_focus (GTK_WIDGET (gtk_objects->web_view));
	gtk_widget_show_all (gtk_objects->main_window);
    
    /* detect fullscreen mode */
    if (conf->fullscreen)
    {
        gtk_widget_hide (gtk_objects->toolbar);
    } else {
        gtk_widget_hide (gtk_objects->toolbar_fullscreen);
    }
    
    /* detect context_menu mode */
    if (conf->context_menu)
    {
        gtk_widget_hide (gtk_objects->scrolled_window);
    } else {
        gtk_widget_hide (gtk_objects->context_menu);
    }
    
    /* return gtk_objects */
    return gtk_objects;
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
    toolbar_fullscreen  = gtk_hbox_new(TRUE, 0);
    fullscreen          = gtk_button_new_with_label("[]");
    close               = gtk_button_new_with_label("X");
    
    /* Add buttons to toolbar */
    gtk_box_pack_start ((GtkBox*) toolbar_fullscreen, fullscreen, TRUE, TRUE, 0);
    
    /* Configure objects */
    gtk_widget_set_size_request (fullscreen, 10, 10);
    
    /* Connect buttons to actions */
	g_signal_connect (G_OBJECT (fullscreen) , "clicked", G_CALLBACK (callback_fullscreen)   , conf);
    
    /* show buttons */
    gtk_widget_show(fullscreen);
    gtk_widget_show(close);
    
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
    toolbar     = gtk_hbox_new(TRUE, 0);
    back        = gtk_button_new_with_label("<-");
    forward     = gtk_button_new_with_label("->");
    fullscreen  = gtk_button_new_with_label("[]");
    minimize    = gtk_button_new_with_label("-");
    close       = gtk_button_new_with_label("X");
    
    /* Add buttons to toolbar */
    gtk_box_pack_end ((GtkBox*) toolbar, back, TRUE, TRUE, 0);
    gtk_box_pack_end ((GtkBox*) toolbar, forward, TRUE, TRUE, 0);
    gtk_box_pack_end ((GtkBox*) toolbar, fullscreen, TRUE, TRUE, 0);
    gtk_box_pack_end ((GtkBox*) toolbar, minimize, TRUE, TRUE, 0);
    gtk_box_pack_end ((GtkBox*) toolbar, close, TRUE, TRUE, 0);
    
    /* Connect buttons to actions */
	g_signal_connect (G_OBJECT (fullscreen) , "clicked", G_CALLBACK (callback_fullscreen)   , conf);
	g_signal_connect (G_OBJECT (back)       , "clicked", G_CALLBACK (callback_back)         , conf);
	g_signal_connect (G_OBJECT (forward)    , "clicked", G_CALLBACK (callback_forward)     , conf);
	g_signal_connect (G_OBJECT (minimize)   , "clicked", G_CALLBACK (callback_minimize)     , conf);
	g_signal_connect (G_OBJECT (close)      , "clicked", G_CALLBACK (callback_destroy)      , NULL);
    
    /* Show buttons */
    gtk_widget_show(fullscreen);
    gtk_widget_show(back);
    gtk_widget_show(forward);
    gtk_widget_show(minimize);
    gtk_widget_show(close);
        
    /* Return toolbar */
    return toolbar;
}

/**
 * generate_context_menu:
 * @conf: pointer to a struct of config settings
 *
 * Creates the context menu.
 *
 * Returns: A pointer to the context menu.
 **/
GtkWidget*
generate_context_menu (SPRY_CONF* conf)
{
    /* Declarations */
    GtkWidget*  menu;
    GtkWidget*  back;
    GtkWidget*  forward;
    GtkWidget*  home;
    GtkWidget*  fullscreen;
    GtkWidget*  minimize;
    GtkWidget*  close;
    
    /* Create buttons */
    menu        = gtk_table_new(2, 3, TRUE);
    back        = gtk_button_new_with_label("<-");
    forward     = gtk_button_new_with_label("->");
    home        = gtk_button_new_with_label("H");
    fullscreen  = gtk_button_new_with_label("[]");
    minimize    = gtk_button_new_with_label("-");
    close       = gtk_button_new_with_label("X");
    
    /* Add buttons to toolbar */
    gtk_table_attach(GTK_TABLE (menu), back         , 0, 1, 0, 1, GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE (menu), home         , 1, 2, 0, 1, GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE (menu), forward      , 2, 3, 0, 1, GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE (menu), minimize     , 0, 1, 1, 2, GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE (menu), fullscreen   , 1, 2, 1, 2, GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE (menu), close        , 2, 3, 1, 2, GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    
    /* Connect buttons to actions */
	g_signal_connect (G_OBJECT (fullscreen) , "clicked", G_CALLBACK (callback_fullscreen)   , conf);
	g_signal_connect (G_OBJECT (back)       , "clicked", G_CALLBACK (callback_back)         , conf);
	g_signal_connect (G_OBJECT (home)       , "clicked", G_CALLBACK (callback_home)         , conf);
	g_signal_connect (G_OBJECT (forward)    , "clicked", G_CALLBACK (callback_forward)     , conf);
	g_signal_connect (G_OBJECT (minimize)   , "clicked", G_CALLBACK (callback_minimize)     , conf);
	g_signal_connect (G_OBJECT (close)      , "clicked", G_CALLBACK (callback_destroy)      , NULL);
    
    /* Show buttons */
    gtk_widget_show(fullscreen);
    gtk_widget_show(back);
    gtk_widget_show(home);
    gtk_widget_show(forward);
    gtk_widget_show(minimize);
    gtk_widget_show(close);
        
    /* Return toolbar */
    return menu;
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
    /* Create Window */
	GtkWidget* main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    
    /* Resize the window */
	gtk_window_set_default_size (GTK_WINDOW (main_window), conf->window_size[0], conf->window_size[1]);
    
    /* Set window name (taskbar / titlebar) */
	gtk_widget_set_name (main_window, "Spry");
    
    /* Connect close signal to quit */
	g_signal_connect (G_OBJECT (main_window), "destroy", G_CALLBACK (callback_destroy), NULL);
    
    /* Return window */
    return main_window;
}
