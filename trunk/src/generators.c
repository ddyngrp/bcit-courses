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

#include "config.h"
#include "generators.h"

#include "callbacks.h"
#include "spry.h"

/**
 * generate_gui:
 * @conf: pointer to a struct of config settings
 *
 * Creates a the entire gui (main window).
 * 
 * Returns: struct of main gtk objects.
 **/
SPRY_GTK_OBJECTS*
generate_gui (SPRY_CONF* conf)
{
    
    SPRY_GTK_OBJECTS* gtk_objects = malloc (sizeof (SPRY_GTK_OBJECTS));
    
	/* main window */
    gtk_objects->main_window = generate_main_window(conf);
    gtk_objects->v_box = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER (gtk_objects->main_window), gtk_objects->v_box);
	
	/* toolbar */
    gtk_objects->toolbar = generate_toolbar(conf);
    gtk_widget_set_size_request (gtk_objects->toolbar, 10, conf->toolbar_height);
    gtk_box_pack_start((GtkBox*) gtk_objects->v_box, gtk_objects->toolbar, FALSE, FALSE, 0);
	
	/* toolbar_fullscreen */
    gtk_objects->toolbar_fullscreen = generate_toolbar_fullscreen(conf);
    gtk_widget_set_size_request (gtk_objects->toolbar_fullscreen, 10, conf->toolbar_fullscreen_height);
    gtk_box_pack_start((GtkBox*) gtk_objects->v_box, gtk_objects->toolbar_fullscreen, FALSE, FALSE, 0);
	
	/* context menu */
    gtk_objects->context_menu = generate_context_menu(conf);
    gtk_box_pack_start((GtkBox*) gtk_objects->v_box, gtk_objects->context_menu         , TRUE , TRUE , 0);
	
	/* web view */
    gtk_objects->web_view = WEBKIT_WEB_VIEW (webkit_web_view_new());
		gtk_objects->web_view_container = gtk_scrolled_window_new (NULL, NULL);
	if (ENABLED(conf->features, SCROLLBARS_ENABLED))
	{
		gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (gtk_objects->web_view_container), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	} else {
		gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (gtk_objects->web_view_container), GTK_POLICY_NEVER, GTK_POLICY_NEVER);
	}
	gtk_container_add (GTK_CONTAINER (gtk_objects->web_view_container) , GTK_WIDGET (gtk_objects->web_view));
	gtk_box_pack_start((GtkBox*) gtk_objects->v_box, gtk_objects->web_view_container, TRUE , TRUE , 0);
    /* show objects */
    gtk_widget_grab_focus (GTK_WIDGET (gtk_objects->web_view));
    gtk_widget_show_all (gtk_objects->main_window);
    
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
    GtkWidget*  toolbar_button;
    
    /* Create buttons */
    toolbar_fullscreen  = gtk_hbox_new(TRUE, 0);
    toolbar_button      = generate_button("toolbar");
    
    /* Add buttons to toolbar */
    gtk_box_pack_start((GtkBox*) toolbar_fullscreen, toolbar_button, TRUE, TRUE, 0);
    
    /* Connect buttons to actions */
    g_signal_connect(G_OBJECT (toolbar_button)     , "clicked"     , G_CALLBACK (callback_toolbar)   , conf);
    
    /* show buttons */
    gtk_widget_show(toolbar_button);
    
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
    GtkWidget*  back_button;
    GtkWidget*  forward_button;
    GtkWidget*  home_button;
    GtkWidget*  context_button;
    GtkWidget*  toolbar_button;
    GtkWidget*  fullscreen_button;
    GtkWidget*  minimize_button;
    GtkWidget*  close_button;
    
    /* Create buttons */
    toolbar             = gtk_hbox_new(TRUE, 0);
    back_button         = generate_button("back");
    forward_button      = generate_button("forward");
    home_button         = generate_button("home");
    context_button      = generate_button("context");
    toolbar_button      = generate_button("toolbar");
    fullscreen_button   = generate_button("fullscreen");
    minimize_button     = generate_button("minimize");
    close_button        = generate_button("close");
    
    /* Add buttons to toolbar */
    gtk_box_pack_start((GtkBox*) toolbar, back_button           , TRUE, TRUE, 0);
    gtk_box_pack_start((GtkBox*) toolbar, forward_button        , TRUE, TRUE, 0);
    gtk_box_pack_start((GtkBox*) toolbar, home_button           , TRUE, TRUE, 0);
    gtk_box_pack_start((GtkBox*) toolbar, context_button        , TRUE, TRUE, 0);
    gtk_box_pack_start((GtkBox*) toolbar, toolbar_button        , TRUE, TRUE, 0);
    gtk_box_pack_start((GtkBox*) toolbar, fullscreen_button     , TRUE, TRUE, 0);
    gtk_box_pack_start((GtkBox*) toolbar, minimize_button       , TRUE, TRUE, 0);
    gtk_box_pack_start((GtkBox*) toolbar, close_button          , TRUE, TRUE, 0);
    
    /* Connect buttons to actions */
    g_signal_connect(G_OBJECT (fullscreen_button)   , "clicked", G_CALLBACK (callback_fullscreen)   , conf);
    g_signal_connect(G_OBJECT (back_button)         , "clicked", G_CALLBACK (callback_back)         , conf);
    g_signal_connect(G_OBJECT (forward_button)      , "clicked", G_CALLBACK (callback_forward)      , conf);
    g_signal_connect(G_OBJECT (context_button)      , "clicked", G_CALLBACK (callback_context)      , conf);
    g_signal_connect(G_OBJECT (toolbar_button)      , "clicked", G_CALLBACK (callback_toolbar)      , conf);
    g_signal_connect(G_OBJECT (home_button)         , "clicked", G_CALLBACK (callback_home)         , conf);
    g_signal_connect(G_OBJECT (minimize_button)     , "clicked", G_CALLBACK (callback_minimize)     , conf);
    g_signal_connect(G_OBJECT (close_button)        , "clicked", G_CALLBACK (callback_destroy)      , NULL);
    
    /* Show buttons */
    gtk_widget_show(fullscreen_button);
    gtk_widget_show(back_button);
    gtk_widget_show(forward_button);
    gtk_widget_show(toolbar_button);
    gtk_widget_show(context_button);
    gtk_widget_show(home_button);
    gtk_widget_show(minimize_button);
    gtk_widget_show(close_button);
        
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
    GtkWidget*  minimize;
    GtkWidget*  fullscreen;
    GtkWidget*  close;
    GtkWidget*  back;
    GtkWidget*  home;
    GtkWidget*  forward;
    GtkWidget*  toolbar;
    GtkWidget*  context;
    
    /* Create buttons */
    menu        = gtk_table_new(3, 3, TRUE);
    minimize    = generate_button("minimize");
    fullscreen  = generate_button("fullscreen");
    close       = generate_button("close");
    back        = generate_button("back");
    home        = generate_button("home");
    forward     = generate_button("forward");
    toolbar     = generate_button("toolbar");
    context     = generate_button("context");
    
    /* Add buttons to toolbar */
    gtk_table_attach(GTK_TABLE (menu), minimize     , 0, 1, 0, 1, GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE (menu), fullscreen   , 1, 2, 0, 1, GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE (menu), close        , 2, 3, 0, 1, GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE (menu), back         , 0, 1, 1, 2, GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE (menu), home         , 1, 2, 1, 2, GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE (menu), forward      , 2, 3, 1, 2, GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE (menu), toolbar      , 1, 2, 2, 3, GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    gtk_table_attach(GTK_TABLE (menu), context      , 2, 3, 2, 3, GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND, 0, 0);
    
    /* Connect buttons to actions */
    g_signal_connect(G_OBJECT (minimize)    , "clicked", G_CALLBACK (callback_minimize)     , conf);
    g_signal_connect(G_OBJECT (fullscreen)  , "clicked", G_CALLBACK (callback_fullscreen)   , conf);
    g_signal_connect(G_OBJECT (close)       , "clicked", G_CALLBACK (callback_destroy)      , NULL);
    g_signal_connect(G_OBJECT (back)        , "clicked", G_CALLBACK (callback_back)         , conf);
    g_signal_connect(G_OBJECT (home)        , "clicked", G_CALLBACK (callback_home)         , conf);
    g_signal_connect(G_OBJECT (forward)     , "clicked", G_CALLBACK (callback_forward)      , conf);
    g_signal_connect(G_OBJECT (toolbar)     , "clicked", G_CALLBACK (callback_toolbar)      , conf);
    g_signal_connect(G_OBJECT (context)     , "clicked", G_CALLBACK (callback_context)      , conf);
    
    /* Show buttons */
    gtk_widget_show(minimize);
    gtk_widget_show(fullscreen);
    gtk_widget_show(close);
    gtk_widget_show(back);
    gtk_widget_show(home);
    gtk_widget_show(forward);
    gtk_widget_show(fullscreen);
    gtk_widget_show(context);
        
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
    GtkWidget* main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    /* Resize the window */
    gtk_window_set_default_size(GTK_WINDOW (main_window), conf->window_size[0], conf->window_size[1]);
	if (DISABLED(conf->features, RESIZE_ENABLED))
		gtk_window_set_resizable((GtkWindow*) main_window, FALSE);
    
    /* Set window name (taskbar / titlebar) and icon */
    gtk_widget_set_name(main_window, "Spry");
    gtk_window_set_icon_from_file((GtkWindow*) main_window, "/usr/local/share/spry/app.svg", NULL);
    
    /* Connect close signal to quit */
    g_signal_connect(G_OBJECT (main_window), "destroy", G_CALLBACK (callback_destroy), NULL);
    
    /* Return window */
    return main_window;
}

/**
 * generate_button:
 * @icon_name: icon filename
 *
 * Creates a resizable button.
 *
 * Returns: The button.
 */
GtkWidget*
generate_button(char* icon_name)
{
    /* declarations */
    GtkWidget *button;
    GtkWidget *draw;

    /* create the button */
    button = gtk_button_new();

    /* create the drawin area (inside the button) */
    draw = gtk_drawing_area_new();
    
    /* tell gtk to re-draw the icon when the button changes */
    g_signal_connect(G_OBJECT(draw), "expose-event", G_CALLBACK(event_button_expose), icon_name);
    
    /* add the drawing area to the button */
    gtk_container_add(GTK_CONTAINER(button), draw);
    
    /* return the button */
    return button;
}
