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
 * along with Foobar.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <window.hpp>
#include <iostream>
#include <string>
#include <pangomm/fontdescription.h>
#include <gtkmm/menuitem.h>

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

void Window::setup_menu_bar(){
//	menubar.append(Gtk::MenuItem("New"))
//	menubar.append(Gtk::MenuItem("Open"))
//	menubar.append(Gtk::MenuItem("Save"))
}

Window::Window(std::shared_ptr<const Slimtex::Styling> styling)
	: styling(styling)
{
	/* Initialize language buffer: */
	auto language = Gsv::LanguageManager::get_default()->get_language("latex");
	codebuffer = Gsv::Buffer::create(language);
	this->codeview.set_buffer(codebuffer);

	// TODO : Quick defaults:
	set_title("SlimTeX");
	
	// Add the pane:
	add(this->pane);
	
	// Add code view:
	this->codewindow.add(this->codeview);
	pane.pack1(this->codewindow, true, false);
	
	// Add pdf view:
	this->pdfwindow.add(this->pdfview);
	pane.pack2(this->pdfwindow, true, false);
	std::cout << "Added pdfview!\n";
	
	// Add menu TODO
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
	this->codeview.set_wrap_mode(Gtk::WRAP_WORD);
	
	
	// Show:
	this->codewindow.show();
	this->codeview.show();
	this->pdfwindow.show();
	this->pdfview.show();
	std::cout << "Showed pdfview!\n";
	
	std::string path("test_documents/sincos.pdf");
	this->pdfview.load(Gio::File::create_for_path(path));
	
	// Show container:
	pane.show();
}

Window::~Window(){

}


// END NAMESPACE
}
