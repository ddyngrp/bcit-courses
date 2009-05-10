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
 * 
 * Returns: struct of main gtk objects.
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
    if (conf->mode & FULLSCREEN)
    {
        gtk_widget_hide (gtk_objects->toolbar);
    } else {
        gtk_widget_hide (gtk_objects->toolbar_fullscreen);
    }
    
    /* detect context_menu mode */
    if (conf->mode & CONTEXT)
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
    GtkWidget*  toolbar_button;
    
    /* Create buttons */
    toolbar_fullscreen  = gtk_hbox_new(TRUE, 0);
    toolbar_button      = gtk_button_new_with_label("[]");
    
    /* Add buttons to toolbar */
    gtk_box_pack_start ((GtkBox*) toolbar_fullscreen, toolbar_button, TRUE, TRUE, 0);
    
    /* Configure objects */
    gtk_widget_set_size_request (toolbar_button, 10, 10);
    
    /* Connect buttons to actions */
	g_signal_connect (G_OBJECT (toolbar_button) , "clicked", G_CALLBACK (callback_toolbar)   , conf);
    
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
    back_button         = gtk_button_new();
    forward_button      = gtk_button_new();
    home_button         = gtk_button_new();
    context_button      = gtk_button_new();
    toolbar_button      = gtk_button_new();
    fullscreen_button   = gtk_button_new();
    minimize_button     = gtk_button_new();
    close_button        = gtk_button_new();
    
    /* add images */
    gtk_button_set_image((GtkButton*) back_button       , (GtkWidget*) gtk_image_new_from_file("images/back.svg")       );
    gtk_button_set_image((GtkButton*) forward_button    , (GtkWidget*) gtk_image_new_from_file("images/forward.svg")    );
    gtk_button_set_image((GtkButton*) home_button       , (GtkWidget*) gtk_image_new_from_file("images/home.svg")       );
    gtk_button_set_image((GtkButton*) context_button    , (GtkWidget*) gtk_image_new_from_file("images/context.svg")    );
    gtk_button_set_image((GtkButton*) fullscreen_button , (GtkWidget*) gtk_image_new_from_file("images/fullscreen.svg") );
    gtk_button_set_image((GtkButton*) toolbar_button    , (GtkWidget*) gtk_image_new_from_file("images/toolbar.svg")    );
    gtk_button_set_image((GtkButton*) minimize_button   , (GtkWidget*) gtk_image_new_from_file("images/minimize.svg")   );
    gtk_button_set_image((GtkButton*) close_button      , (GtkWidget*) gtk_image_new_from_file("images/close.svg")      );
    
    /* Add buttons to toolbar */
    gtk_box_pack_start ((GtkBox*) toolbar, back_button          , TRUE, TRUE, 0);
    gtk_box_pack_start ((GtkBox*) toolbar, forward_button       , TRUE, TRUE, 0);
    gtk_box_pack_start ((GtkBox*) toolbar, home_button          , TRUE, TRUE, 0);
    gtk_box_pack_start ((GtkBox*) toolbar, context_button       , TRUE, TRUE, 0);
    gtk_box_pack_start ((GtkBox*) toolbar, toolbar_button       , TRUE, TRUE, 0);
    gtk_box_pack_start ((GtkBox*) toolbar, fullscreen_button    , TRUE, TRUE, 0);
    gtk_box_pack_start ((GtkBox*) toolbar, minimize_button      , TRUE, TRUE, 0);
    gtk_box_pack_start ((GtkBox*) toolbar, close_button         , TRUE, TRUE, 0);
    
    /* Connect buttons to actions */
	g_signal_connect (G_OBJECT (fullscreen_button)  , "clicked", G_CALLBACK (callback_fullscreen)   , conf);
	g_signal_connect (G_OBJECT (back_button)        , "clicked", G_CALLBACK (callback_back)         , conf);
	g_signal_connect (G_OBJECT (forward_button)     , "clicked", G_CALLBACK (callback_forward)      , conf);
	g_signal_connect (G_OBJECT (context_button)     , "clicked", G_CALLBACK (callback_context)      , conf);
	g_signal_connect (G_OBJECT (toolbar_button)     , "clicked", G_CALLBACK (callback_toolbar)      , conf);
	g_signal_connect (G_OBJECT (home_button)        , "clicked", G_CALLBACK (callback_home)         , conf);
	g_signal_connect (G_OBJECT (minimize_button)    , "clicked", G_CALLBACK (callback_minimize)     , conf);
	g_signal_connect (G_OBJECT (close_button)       , "clicked", G_CALLBACK (callback_destroy)      , NULL);
    
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
    minimize    = gtk_button_new();
    fullscreen  = gtk_button_new();
    close       = gtk_button_new();
    back        = gtk_button_new();
    home        = gtk_button_new();
    forward     = gtk_button_new();
    toolbar     = gtk_button_new();
    context     = gtk_button_new();
    
    /* add images */
    gtk_button_set_image((GtkButton*) minimize  , (GtkWidget*) gtk_image_new_from_file("images/minimize.svg")   );
    gtk_button_set_image((GtkButton*) fullscreen, (GtkWidget*) gtk_image_new_from_file("images/fullscreen.svg") );
    gtk_button_set_image((GtkButton*) close     , (GtkWidget*) gtk_image_new_from_file("images/close.svg")      );
    gtk_button_set_image((GtkButton*) back      , (GtkWidget*) gtk_image_new_from_file("images/back.svg")       );
    gtk_button_set_image((GtkButton*) home      , (GtkWidget*) gtk_image_new_from_file("images/home.svg")       );
    gtk_button_set_image((GtkButton*) forward   , (GtkWidget*) gtk_image_new_from_file("images/forward.svg")    );
    gtk_button_set_image((GtkButton*) toolbar   , (GtkWidget*) gtk_image_new_from_file("images/toolbar.svg")    );
    gtk_button_set_image((GtkButton*) context   , (GtkWidget*) gtk_image_new_from_file("images/context.svg")    );
    /* gtk_button_set_image((GtkButton*) app       , (GtkWidget*) gtk_image_new_from_file("images/app.svg")        ); */
    
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
	g_signal_connect (G_OBJECT (minimize)   , "clicked", G_CALLBACK (callback_minimize)     , conf);
	g_signal_connect (G_OBJECT (fullscreen) , "clicked", G_CALLBACK (callback_fullscreen)   , conf);
	g_signal_connect (G_OBJECT (close)      , "clicked", G_CALLBACK (callback_destroy)      , NULL);
	g_signal_connect (G_OBJECT (back)       , "clicked", G_CALLBACK (callback_back)         , conf);
	g_signal_connect (G_OBJECT (home)       , "clicked", G_CALLBACK (callback_home)         , conf);
	g_signal_connect (G_OBJECT (forward)    , "clicked", G_CALLBACK (callback_forward)      , conf);
	g_signal_connect (G_OBJECT (toolbar)    , "clicked", G_CALLBACK (callback_toolbar)      , conf);
	g_signal_connect (G_OBJECT (context)    , "clicked", G_CALLBACK (callback_context)      , conf);
    
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



/**
 * cb_expose:
 * @draw: unused
 * @event: event containing the window
 * @data: filenumber
 *
 * Creates a resizable button.
 * TODO: customize and make it our own
 *
 * Returns: FALSE.
 **/
static gboolean
cb_expose( GtkWidget      *draw,
		   GdkEventExpose *event,
		   gpointer        data )
{
	gchar     *filename;
	GdkPixbuf *pixbuf;
	gint       pw, ph, dw, dh, x, y;
	GError    *error = NULL;

	/* Create filename from data */
	filename = g_strdup_printf("images/icon%d.png", GPOINTER_TO_INT( data ));

	/* Get drawing area dimensions */
	gdk_drawable_get_size( GDK_DRAWABLE( event->window ), &dw, &dh );

	/* Load pixbuf from file */
	pixbuf = gdk_pixbuf_new_from_file_at_size( filename, dw, dh, &error );
	g_free( filename );
	if( error )
	{
		g_print( "Error: %s\n", error->message );
		return( FALSE );
	}

	/* Calculate x and y position to center the image */
	pw = gdk_pixbuf_get_width( pixbuf );
	ph = gdk_pixbuf_get_height( pixbuf );
	x = ( dw - pw ) / 2;
	y = ( dh - ph ) / 2;

	/* Draw pixbuf */
	gdk_draw_pixbuf( GDK_DRAWABLE( event->window ), NULL, pixbuf, 0, 0,
					 x, y, -1, -1, GDK_RGB_DITHER_NONE, 0, 0 );
	g_object_unref( G_OBJECT( pixbuf ) );

	return( FALSE );
}


/**
 * button_test:
 *
 * Tests cb_expose.
 * TODO: Integrate into toolbar and context generators.
 **/
void
button_test()
{
	GtkWidget *window;
	GtkWidget *table;
	gint       i;

	window = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	gtk_window_set_default_size( GTK_WINDOW( window ), 300, 300 );
	g_signal_connect( G_OBJECT( window ), "destroy",
					  G_CALLBACK( gtk_main_quit ), NULL );

	table = gtk_table_new( 3, 3, TRUE );
	gtk_container_add( GTK_CONTAINER( window ), table );

	/* Create buttons */
	for( i = 0; i < 3; i++ )
	{
		gint j;

		for( j = 0; j < 3; j++ )
		{
			GtkWidget *button;
			GtkWidget *draw;

			button = gtk_button_new();
			gtk_table_attach( GTK_TABLE( table ), button, j, j + 1, i, i + 1,
				   			  GTK_FILL | GTK_EXPAND, GTK_FILL | GTK_EXPAND,
							  0, 0 );

			draw = gtk_drawing_area_new();
			g_signal_connect( G_OBJECT( draw ), "expose-event",
							  G_CALLBACK( cb_expose ),
							  GINT_TO_POINTER( i * 3 + j ) );
			gtk_container_add( GTK_CONTAINER( button ), draw );
		}
	}

	/* Show everything */
	gtk_widget_show_all( window );
	gtk_main();
}
