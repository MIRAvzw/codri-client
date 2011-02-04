/*
 * Copyright (c) 2010 Tim Besard <tim.besard@gmail.com>
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

////////////////////////////////////////////////////////////////////////////////
// Configuration
//

//
// Essential stuff
//

// Headers
#include "browser.h"

// Globals
static GtkWidget* main_window;
static GtkWidget* uri_entry;
static GtkStatusbar* main_statusbar;
static WebKitWebView* web_view;
static gchar* main_title;
static gdouble load_progress;
static guint status_context_id;



////////////////////////////////////////////////////////////////////////////////
// Callbacks
//

static void
update_title (GtkWindow* window)
{
	GString* string = g_string_new (main_title);
	g_string_append (string, " - Kiosk Browser");
	if (load_progress < 100)
		g_string_append_printf (string, " (%f%%)", load_progress);
	gchar* title = g_string_free (string, FALSE);
	gtk_window_set_title (window, title);
	g_free (title);
}

static void
link_hover_cb (WebKitWebView* page, const gchar* title, const gchar* link, gpointer data)
{
	/* underflow is allowed */
	gtk_statusbar_pop (main_statusbar, status_context_id);
	if (link)
		gtk_statusbar_push (main_statusbar, status_context_id, link);
}

static void
notify_title_cb (WebKitWebView* web_view, GParamSpec* pspec, gpointer data)
{
	if (main_title)
		g_free (main_title);
	main_title = g_strdup (webkit_web_view_get_title(web_view));
	update_title (GTK_WINDOW (main_window));
}

static void
notify_load_status_cb (WebKitWebView* web_view, GParamSpec* pspec, gpointer data)
{
	if (webkit_web_view_get_load_status (web_view) == WEBKIT_LOAD_COMMITTED) {
		WebKitWebFrame* frame = webkit_web_view_get_main_frame (web_view);
		const gchar* uri = webkit_web_frame_get_uri (frame);
		if (uri)
			gtk_entry_set_text (GTK_ENTRY (uri_entry), uri);
	}
}

static void
notify_progress_cb (WebKitWebView* web_view, GParamSpec* pspec, gpointer data)
{
	load_progress = webkit_web_view_get_progress (web_view) * 100;
	update_title (GTK_WINDOW (main_window));
}

static void
destroy_cb (GtkWidget* widget, gpointer data)
{
	gtk_main_quit ();
}

////////////////////////////////////////////////////////////////////////////////
// Hooks
//

gboolean
go_back_hk (gpointer data)
{
	webkit_web_view_go_back (web_view);
	return FALSE;
}

gboolean
quit_hk (gpointer data)
{
	gtk_main_quit ();
	return FALSE;
}


////////////////////////////////////////////////////////////////////////////////
// GUI
//

static GtkWidget*
create_browser ()
{
	GtkWidget* scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

	web_view = WEBKIT_WEB_VIEW (webkit_web_view_new ());
	gtk_container_add (GTK_CONTAINER (scrolled_window), GTK_WIDGET (web_view));

	g_signal_connect (web_view, "notify::title", G_CALLBACK (notify_title_cb), web_view);
	g_signal_connect (web_view, "notify::load-status", G_CALLBACK (notify_load_status_cb), web_view);
	g_signal_connect (web_view, "notify::progress", G_CALLBACK (notify_progress_cb), web_view);
	g_signal_connect (web_view, "hovering-over-link", G_CALLBACK (link_hover_cb), web_view);

	return scrolled_window;
}

static GtkWidget*
create_statusbar ()
{
	main_statusbar = GTK_STATUSBAR (gtk_statusbar_new ());
	status_context_id = gtk_statusbar_get_context_id (main_statusbar, "Link Hover");

	return (GtkWidget*)main_statusbar;
}

static GtkWidget*
create_window ()
{
	GtkWidget* window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size (GTK_WINDOW (window), 800, 600);
	gtk_widget_set_name (window, "GtkLauncher");
	g_signal_connect (window, "destroy", G_CALLBACK (destroy_cb), NULL);

	return window;
}


////////////////////////////////////////////////////////////////////////////////
// Auxiliary
//

static gchar*
filenameToURL (const char* filename)
{
	if (!g_file_test(filename, G_FILE_TEST_EXISTS))
		return 0;

	GFile *gfile = g_file_new_for_path(filename);
	gchar *fileURL = g_file_get_uri(gfile);
	g_object_unref(gfile);

	return fileURL;
}

////////////////////////////////////////////////////////////////////////////////
// Public routines
//

void
browser_init()
{
	// Initialise GTK
	gtk_init (NULL, NULL); // (&argc, &argv);
	if (!g_thread_supported ()) {
		printf ("! I really need threads\n");
		exit (1);
	}
	
	// Initialise GDK threads
	g_thread_init (NULL);
	gdk_threads_init ();
	gdk_threads_enter ();

	// Setup the GUI
	GtkWidget* vbox = gtk_vbox_new (FALSE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), create_browser (), TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (vbox), create_statusbar (), FALSE, FALSE, 0);
	main_window = create_window ();
	gtk_container_add (GTK_CONTAINER (main_window), vbox);
}

void
browser_run()
{
	// Load and display the starting URL
	gchar *uri = (gchar*) "file://./html/accordion.html";
	gchar *fileURL = filenameToURL(uri);
	webkit_web_view_load_uri(web_view, fileURL ? fileURL : uri);
	g_free(fileURL);
	
	// Start the main loop
	gtk_widget_grab_focus (GTK_WIDGET (web_view));
	gtk_widget_show_all (main_window);
	gtk_main ();
}

void
browser_exit()
{
	gdk_threads_leave ();
}

void
browser_go_back()
{
	g_idle_add(go_back_hk, NULL);
}
void
browser_quit()
{
	g_idle_add(quit_hk, NULL);
}
