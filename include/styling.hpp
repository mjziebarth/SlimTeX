/*
 * styling.hpp
 * Contains declarations of string constants used in the style config
 * file. These keys, whose values can be found in src/styling.cpp,
 * enumerate the possible entries in the style config file.
 * The styling information is read on startup.
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


#ifndef STYLING_HPP
#define STYLING_HPP

#include <unordered_map>
#include <any>

namespace Slimtex {

// Window properties:
extern const char* STYLE_KEY_WINDOW_MIN_WIDTH;
extern const char* STYLE_KEY_WINDOW_MIN_HEIGHT;

// Text editor properties:
extern const char* STYLE_KEY_CODEVIEW_FONT_FAMILY;
extern const char* STYLE_KEY_CODEVIEW_FONT_SIZE;
extern const char* STYLE_KEY_CODEVIEW_MIN_WIDTH;
extern const char* STYLE_KEY_CODEVIEW_MIN_HEIGHT;
extern const char* STYLE_KEY_CODEVIEW_HIGHLIGHT_CURRENT_LINE;
extern const char* STYLE_KEY_CODEVIEW_SHOW_LINE_NUMBERS;


class Styling {
	public:
		Styling(const char* filename);
		
		std::any operator[](const std::string& key) const;
		
	private:
		std::unordered_map<std::string,std::any> style_dict;

};

}
#endif
