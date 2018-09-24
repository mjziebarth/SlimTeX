/*
 * window_styling.cpp
 * Contains the styling routines to avoid clutter in window.cpp
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
#include <types.hpp>
#include <iostream>


// Handle missing of std::any in c++14 and below:
#if __cplusplus >= 201703L
	using std::any_cast;
#else
	// We use any_cpp14.hpp as a workaround. Nothing
	// to be done here since everything was declared
	// in window.hpp.
#endif


namespace Slimtex {


void Window::parse_styling()
{
	/* Make sure vector is initialized: */
	if (!styling){
		throw std::runtime_error("Styling not defined!");
	}
	const Styling& style = *styling;
	any val;
	
	/* Window dimensions: */
	Gdk::Geometry geometry;
	Gdk::WindowHints hints = static_cast<Gdk::WindowHints>(0);
	
	/* Min dimensions: */
	if ((val = style[STYLE_KEY_WINDOW_MIN_WIDTH]).has_value()){
		if (val.type() == typeid(int)){
			hints |= Gdk::HINT_MIN_SIZE;
			geometry.min_width = any_cast<int>(val);
		} else {
			throw std::runtime_error("Value \"window.min_width\" has wrong type.");
		}
	} else {
		geometry.min_width=0;
	}
	if ((val = style[STYLE_KEY_WINDOW_MIN_HEIGHT]).has_value()){
		if (val.type() == typeid(int)){
			hints |= Gdk::HINT_MIN_SIZE;
			geometry.min_height = any_cast<int>(val);
		} else {
			throw std::runtime_error("Value \"window.min_height\" has wrong type.");
		}
	} else {
		geometry.min_height=0;
	}
	/* Default dimensions: */
	std::cout << "1\n";
	if ((val = style[STYLE_KEY_WINDOW_DEFAULT_SIZE]).has_value()){
		if (val.type() == typeid(Size<int>)){
			Size<int> s(any_cast<Size<int>>(val));
			hints |= Gdk::HINT_BASE_SIZE;
			geometry.base_width = s.width;
			geometry.base_height = s.height;
		} else if (val.type() == typeid(std::string)){
			if (any_cast<std::string>(val) == "full"){
				// Maximize:
				maximize();
			} else {
				throw std::runtime_error("Value \"window.default_size\""
				                         " has wrong type.");
			}
		} else {
			throw std::runtime_error("Value \"window.default_size\" has wrong type.");
		}
	}
	
	set_geometry_hints(*this,geometry,hints);
	
	/* Code view font: */
	Pango::FontDescription font;
	bool font_set = false;
	if ((val = style[STYLE_KEY_CODEVIEW_FONT_FAMILY]).has_value()){
		if (val.type() == typeid(std::string)){
			font_set=true;
			font.set_family(any_cast<std::string>(val));
		}
	}
	if ((val = style[STYLE_KEY_CODEVIEW_FONT_SIZE]).has_value()){
		if (val.type() == typeid(int)){
			font_set=true;
			font.set_size(any_cast<int>(val) * PANGO_SCALE);
		}
	}
	if (font_set){
		this->codeview.override_font(font);
	}
	
	/* Code view dimensions: */
	int min_width=0, min_height=0;
	if ((val = style[STYLE_KEY_CODEVIEW_MIN_WIDTH]).has_value()){
		if (val.type() == typeid(int)){
			min_width = any_cast<int>(val);
		}
	}
	if ((val = style[STYLE_KEY_CODEVIEW_MIN_HEIGHT]).has_value()){
		if (val.type() == typeid(int)){
			min_height = any_cast<int>(val);
		}
	}
	this->codeview.set_size_request(min_width, min_height);
	
	/* Code view options: */
	
	// Highlight current line:
	if ((val = style[STYLE_KEY_CODEVIEW_HIGHLIGHT_CURRENT_LINE]).has_value()){
		if (val.type() == typeid(bool)){
			this->codeview.set_highlight_current_line(any_cast<bool>(val));
		}
	}
	// Show line numbers:
	if ((val = style[STYLE_KEY_CODEVIEW_SHOW_LINE_NUMBERS]).has_value()){
		if (val.type() == typeid(bool)){
			this->codeview.set_show_line_marks(any_cast<bool>(val));
		}
	}
}

// END NAMESPACE
}
