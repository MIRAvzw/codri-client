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

// Include guard
#ifndef __BROWSER
#define __BROWSER

// Headers
#include <webkitmm/init.h>
#include <webkitmm/webview.h>
#include <gtkmm.h>



////////////////////////////////////////////////////////////////////////////////
// Class definition
//

class Browser : public Gtk::Window
{
	public:
		// Construction and destruction
		Browser ();
		~Browser ();
	
		// Public routines
		void open (Glib::ustring uri);

	private:
		// Member data
		WebKit::WebView m_web_view;
		Gtk::VBox m_layout;
		Gtk::ScrolledWindow m_scroller;
		
		// Signal handlers
		void on_title_changed (const Glib::RefPtr<WebKit::WebFrame>& frame, const Glib::ustring& title);
};


// Include guard
#endif

