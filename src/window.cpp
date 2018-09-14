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

// BEGIN NAMESPACE
namespace Slimtex {


Window::Window() //: pdfview(this)
{
	// TODO : Quick defaults:
	set_title("SlimTeX");
	
	// Add the pane:
	add(this->pane);
	
	// Add code view:
	pane.add(this->codeview);
//	pane.add(this->pdfview);
	
	// Initialize code view:
	this->codeview.show();
//	this->pdfview.show();
	
	// Show container:
	pane.show();
}

Window::~Window(){

}

// END NAMESPACE
}
