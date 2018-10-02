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
 * along with SlimTeX. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef SLIMTEX_WINDOW_H
#define SLIMTEX_WINDOW_H

// TODO make sure all these headers are actually used!
#include <gtkmm/applicationwindow.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/paned.h>
#include <gtkmm/box.h>
#include <gtkmm/builder.h>
#include <gtkmm/application.h>
#include <gtkmm/headerbar.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/menubutton.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/popover.h>
#include <gtkmm/listbox.h>
#include <gtkmm/searchbar.h>

// GtkSourceView wrapper is extra:
#include <gtksourceviewmm.h>

// Custom wrapper for evince-view:
#include <evinceview.hpp>

#include <memory>
#include <styling.hpp>

// BEGIN NAMESPACE
namespace Slimtex {

class Window : public Gtk::ApplicationWindow
{
	public:
		Window(std::shared_ptr<const Slimtex::Styling> styling);
		~Window();
		
		static void init_application(Glib::RefPtr<Gtk::Application> app);
	
	private:
		// Signal handlers:
		// TODO
		
		// Child widgets:
		Gtk::VBox box;
		Gtk::HPaned pane;
		Gsv::View codeview;
		Glib::RefPtr<Gsv::Buffer> codebuffer;
		Gtk::ScrolledWindow codewindow;
		Gtk::ScrolledWindow pdfwindow;
		EvinceView pdfview;
		
		// Styling information:
		std::shared_ptr<const Slimtex::Styling> styling;
		Glib::RefPtr<Gtk::Builder>      menubuilder;

		// The menubar:
		std::shared_ptr<Gtk::HeaderBar> menubar;
		Gtk::ToggleButton tb_open;
		std::shared_ptr<Gtk::MenuButton> mb_main_menu;
		Glib::RefPtr<Gio::Menu>   main_menu;
		
		// The popover menu for opening (gedit-style):
		Gtk::Popover po_open;
		Gtk::VBox    vb_open;
		Gtk::Button  btn_open_further;
		Gtk::FileChooserDialog fcd_open;
		Gtk::ListBox lb_open_recent;
		Gtk::SearchBar sb_open;
		
		void parse_styling();

		void setup_menu_bar();
		
		void button_open_toggled();
		
		/* Signal that is executed when the popover for 
		 * the open button is closed: */
		void popover_open_closed();
		
		/* Close the popover for the open button: */
		void popover_open_close();
		void button_open_further_clicked();

};

// END NAMESPACE
}
#endif
