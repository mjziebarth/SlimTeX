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

// BEGIN NAMESPACE
namespace Slimtex {

Window::Window(std::shared_ptr<const Slimtex::Styling> styling)
	: styling(styling)
{
	// TODO : Quick defaults:
	set_title("SlimTeX");
	
	// Add the pane:
	add(this->pane);
	
	// Add code view:
	this->codewindow.add(this->codeview);
	pane.add(this->codewindow);
	
	// Add pdf view:
	this->pdfwindow.add(this->pdfview);
	pane.add(this->pdfwindow);
	std::cout << "Added pdfview!\n";
	
	// Parse settings:
	try {
		parse_styling();
	} catch (...){
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

void Window::parse_styling()
{
	/* Make sure vector is initialized: */
	if (!styling){
		throw std::runtime_error("Styling not defined!");
	}
	const Styling& style = *styling;
	std::any val;
	Gdk::Geometry geometry;
	Gdk::WindowHints hints;
	/* Min width: */
	if ((val = style[STYLE_KEY_WINDOW_MIN_WIDTH]).has_value()){
		if (val.type() == typeid(int)){
			hints |= Gdk::HINT_MIN_SIZE;
			geometry.min_width = std::any_cast<int>(val);
		}
	} else {
		geometry.min_width=0;
	}
	/* Min height: */
	if ((val = style[STYLE_KEY_WINDOW_MIN_HEIGHT]).has_value()){
		if (val.type() == typeid(int)){
			hints |= Gdk::HINT_MIN_SIZE;
			geometry.min_height = std::any_cast<int>(val);
		}
	} else {
		geometry.min_height=0;
	}
	set_geometry_hints(*this,geometry,hints);
	
	/* Code view font: */
	Pango::FontDescription font;
	bool font_set = false;
	if ((val = style[STYLE_KEY_CODEVIEW_FONT_FAMILY]).has_value()){
		if (val.type() == typeid(std::string)){
			font_set=true;
			font.set_family(std::any_cast<std::string>(val));
		}
	}
	if ((val = style[STYLE_KEY_CODEVIEW_FONT_SIZE]).has_value()){
		if (val.type() == typeid(int)){
			font_set=true;
			font.set_size(std::any_cast<int>(val) * PANGO_SCALE);
		}
	}
	if (font_set){
		this->codeview.override_font(font);
	}
	
	/* Code view dimensions: */
	int min_width=0, min_height=0;
	if ((val = style[STYLE_KEY_CODEVIEW_MIN_WIDTH]).has_value()){
		if (val.type() == typeid(int)){
			min_width = std::any_cast<int>(val);
		}
	}
	if ((val = style[STYLE_KEY_CODEVIEW_MIN_HEIGHT]).has_value()){
		if (val.type() == typeid(int)){
			min_height = std::any_cast<int>(val);
		}
	}
	this->codeview.set_size_request(min_width, min_height);
	
}




// END NAMESPACE
}
