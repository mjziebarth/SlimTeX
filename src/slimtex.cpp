/*
 * slimtex.cpp
 *
 * Copyright (C) 2018 Malte Ziebarth
 *
 * This file is part of SlimTeX.
 *
 * SlimTeX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SlimTeX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SlimTeX. If not, see <https://www.gnu.org/licenses/>.
 */

#include <gtkmm/application.h>
#include <gtkmm/grid.h>
#include <gtkmm/cssprovider.h>
#include <window.hpp>
#include <iostream>
#include <memory>
#include <libxml/parser.h>

#include <styling.hpp>

/* Internationalization:
 * TODO this does not work yet! */
#define GETTEXT_PACKAGE "gtk20"
#define PROGRAMNAME_LOCALEDIR "locale"
#include <glib/gi18n.h>
#include <locale.h>


int main(int argc, char *argv[])
{
	// Initialize locale:
	// TODO this does not work yet!
	setlocale(LC_ALL, "");
	bindtextdomain(GETTEXT_PACKAGE, PROGRAMNAME_LOCALEDIR);
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
	textdomain(GETTEXT_PACKAGE);

	auto app = Gtk::Application::create(argc, argv, "org.slimtex.base");
	
	// Do some app initialization that needs to be synchronized with
	// the Window class:
	Slimtex::Window::init_application(app);

	// Library initializing:
	LIBXML_TEST_VERSION
	Gsv::init();
	
	// Load style:
	std::shared_ptr<const Slimtex::Styling> styling
		= std::make_shared<const Slimtex::Styling>("config/style.xml");
	
	// Cleanup function for the XML library.
	xmlCleanupParser();
	
	// Create window
	Slimtex::Window window(styling);
	window.set_default_size(200, 200);


	// Run app:
	return app->run(window);
}
