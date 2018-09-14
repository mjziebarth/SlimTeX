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
 * along with Foobar.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <gtkmm/application.h>
#include <gtkmm/grid.h>
#include <window.hpp>

int main(int argc, char *argv[])
{
  auto app =
    Gtk::Application::create(argc, argv,
      "org.slimtex.base");

	// Create window
	Slimtex::Window window;
	window.set_default_size(200, 200);


	return app->run(window);
}
