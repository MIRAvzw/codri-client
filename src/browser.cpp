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
#include "browser.hpp"


////////////////////////////////////////////////////////////////////////////////
// Class routines
//

//
// Construction and destruction
//

Browser::Browser ()
{
	add (m_layout);
	m_layout.pack_start (m_scroller);
	m_scroller.add (m_web_view);
	m_scroller.set_policy (Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	set_title ("webkitmm");

	m_web_view.signal_title_changed ().connect
		(sigc::mem_fun (this, &Browser::on_title_changed));
}

Browser::~Browser ()
{
}


//
// Public routines
//

void
Browser::open (Glib::ustring uri)
{
	switch (uri[0])
	{
		// assume it's a local file if it's of the form ./foo or /foo
		case '.':
			uri.erase (uri.begin ());
			uri = Glib::get_current_dir () + uri;
			// fall through
		case '/':
			uri = "file://" + uri;
			break;

		// else assume it's a web address and try loading via http
		default:
			// prepend 'http://' if user didn't enter a uri scheme
			Glib::ustring scheme = Glib::uri_parse_scheme (uri);
			if (scheme.empty ())
				uri = "http://" + uri;
	}

	m_web_view.open (uri);
}

//
// Signal handlers
//

void
Browser::on_title_changed (const Glib::RefPtr<WebKit::WebFrame>& frame, const Glib::ustring& title)
{
	set_title (title);
}

