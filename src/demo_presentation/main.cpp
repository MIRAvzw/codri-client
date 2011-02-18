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

#include "browser.hpp"



////////////////////////////////////////////////////////////////////////////////
// Main
//

int
main (int argc, char** argv)
{
	Gtk::Main kit (argc, argv);
	if (!Glib::thread_supported())
		Glib::thread_init ();
	WebKit::init ();
	Browser w;
	w.open ("./html/accordion.html");
	//w.set_default_size(1024, 768);
	w.fullscreen();
	w.show_all();
	Gtk::Main::run(w);
	return 0;
}


