/*
 * window.cpp
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

#include <window.hpp>
#include <iostream>
#include <string>
#include <pangomm/fontdescription.h>
#include <gtkmm/menuitem.h>
#include <config.hpp>
#include <glib/gi18n.h>

// Handle missing of std::any in c++14 and below:
#if __cplusplus >= 201703L
	using std::any_cast;
#else
	// We use any_cpp14.hpp as a workaround. Nothing
	// to be done here since everything was declared
	// in window.hpp.
#endif

// BEGIN NAMESPACE
namespace Slimtex {

void Window::init_application(Glib::RefPtr<Gtk::Application> app)
{
	/* TODO : Does this even do anything? Check!
	 *        If it does something, make sure it is complete. */
	app->set_accel_for_action("slimtex.new", "<Primary>n");
	app->set_accel_for_action("slimtex.quit", "<Primary>q");
	app->set_accel_for_action("slimtex.copy", "<Primary>c");
	app->set_accel_for_action("slimtex.paste", "<Primary>v");
}

void Window::setup_menu_bar(){
	// Create builder from file:
	// TODO Is this still used?
	try {
		std::string path = std::string(BASE_PATH).append("/ui/menubar.ui");
		menubuilder = Gtk::Builder::create_from_file(path);
	} catch (Gio::ResourceError e) {
		std::cerr << "Error loading ui definition: " << e.what() << "\n"
		             "Cannot start!\n";
		exit(-1);
	} catch (...) {
		std::cerr << "Error loading ui definition. Cannot start!\n";
		exit(-1);
	}
	
	// Apply menu builder (?):
//	Glib::RefPtr<Gio::Menu> menu = 
//	    Glib::RefPtr<Gio::Menu>::cast_dynamic(menubuilder->get_object("menubar"));
	menubar = std::make_shared<Gtk::HeaderBar>();
	menubar->set_title("SlimTeX");
	menubar->set_show_close_button(true);
	menubar->show();
	
	// Create open button:
	// TODO mb_main_menu should be MenuButton!
	//      and we should set mb_main_menu->set_menu(main_menu);
	mb_open = std::make_shared<Gtk::MenuButton>();
	mb_open->set_label(_("Open"));
	mb_open->show();
	
	// TODO populate lb_open_recent with elements!
	lb_open_recent.show();
	btn_open_further.show();
	sb_open.show();
	
	
	po_open.add(lb_open_recent);
	po_open.add(btn_open_further);
	po_open.add(sb_open);
	po_open.show();
	po_open.set_relative_to(*mb_open);
	po_open.popup();
	
	menubar->pack_start(*mb_open);
	//mb_open

	// Use the nice Gnome titlebar:
	set_titlebar(*menubar);
}

Window::Window(std::shared_ptr<const Slimtex::Styling> styling)
	: styling(styling), btn_open_further(_("Further documents ..."))
{
	/* Initialize language buffer: */
	auto language = Gsv::LanguageManager::get_default()->get_language("latex");
	codebuffer = Gsv::Buffer::create(language);
	codeview.set_buffer(codebuffer);
	
	// Add the pane:
	add(pane);
	
	// Add code view:
	codewindow.add(codeview);
	pane.pack1(codewindow, true, false);
	
	// Add pdf view:
	pdfwindow.add(pdfview);
	pane.pack2(pdfwindow, true, false);
	
	// Add menu
	setup_menu_bar();
	
	// Parse settings:
	try {
		parse_styling();
	} catch (std::runtime_error e){
		std::cerr << "Could not load all neccessary items to style window!\n"
		             "Error message: \""
		          << e.what() << "\"\n";
	} catch (...) {
		std::cerr << "Could not load all neccessary items to style window!\n";
	}
	
	// Fixed settings:
	codeview.set_wrap_mode(Gtk::WRAP_WORD);
	
	
	// Show:
	codewindow.show();
	codeview.show();
	pdfwindow.show();
	pdfview.show();
	
	std::string path("test_documents/sincos.pdf");
	pdfview.load(Gio::File::create_for_path(path));
	
	// Show container:
	pane.show();
}

Window::~Window(){

}


// END NAMESPACE
}
