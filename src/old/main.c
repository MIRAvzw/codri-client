/*
First run browser.glade through gtk-builder-convert with this command:
gtk-builder-convert browser.glade browser.xml
 
Then save this file as main.c and compile it using this command
(those are backticks, not single quotes):
  gcc -Wall -g -o main main.c `pkg-config --cflags --libs gtk+-2.0 webkit-1.0` -export-dynamic
Then execute it using:
  ./main
*/

#include <stdio.h>
#include <string.h>
#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include <stdlib.h>
#include <stdio.h>

static WebKitWebView* web_view;

void on_window_destroy (GtkObject *object, gpointer user_data)
   {
       gtk_main_quit();
       exit(0);
   }
   

int main (int argc, char *argv[])
{
    GtkBuilder *builder;
    GtkWidget  *window;
    GtkWidget  *scrolled_window;
    GtkWidget  *statusbar1;

    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "main.xml", NULL);
    window = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));
    scrolled_window = GTK_WIDGET (gtk_builder_get_object (builder, "scrolledwindow1"));
    statusbar1 = GTK_WIDGET (gtk_builder_get_object (builder, "statusbar1"));

    gtk_window_set_title(GTK_WINDOW(window), "Example Web Browser");

    web_view = WEBKIT_WEB_VIEW (webkit_web_view_new ());
    gtk_container_add (GTK_CONTAINER (scrolled_window), GTK_WIDGET (web_view));
   
    gtk_builder_connect_signals (builder, NULL);
    
    // Connect destroy signal (todo: in glade?)
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);
 
    g_object_unref (G_OBJECT (builder));
                     
    gchar* uri = (gchar*) (argc > 1 ? argv[1] : "file://./main.html");
    webkit_web_view_open (web_view, uri);
   
    gtk_statusbar_push (GTK_STATUSBAR(statusbar1), 0, "Done");
       
    gtk_widget_grab_focus (GTK_WIDGET (web_view));
    gtk_widget_show_all (window);
                   
    gtk_main();
 
    return 0;
} 
