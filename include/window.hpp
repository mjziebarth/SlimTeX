/*
 * window.hpp
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

#ifndef SLIMTEX_WINDOW_H
#define SLIMTEX_WINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/paned.h>

// GtkSourceView wrapper is extra:
#include <gtksourceviewmm.h>

// Custom wrapper for evince-view:
#include <evinceview.hpp>

#include <memory>
#include <styling.hpp>

// BEGIN NAMESPACE
namespace Slimtex {

class Window : public Gtk::Window
{
	public:
		Window(std::shared_ptr<const Slimtex::Styling> styling);
		~Window();
	
	private:
		// Signal handlers:
		// TODO
		
		// Child widgets:
		Gtk::HPaned pane;
		Gsv::View codeview;
		Gtk::ScrolledWindow codewindow;
		Gtk::ScrolledWindow pdfwindow;
		EvinceView pdfview;
		
		// Styling information:
		std::shared_ptr<const Slimtex::Styling> styling;
		
		
		void parse_styling();


};

// END NAMESPACE
}
#endif
