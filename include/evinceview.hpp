/*
 * evinceview.pp
 * 
 * gtkmm compatible wrapper for the GtKWidget EvView
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

#ifndef EVINCEVIEW_H
#define EVINCEVIEW_H

#include <gtkmm/widget.h>

// BEGIN NAMESPACE
namespace Slimtex{

class EvinceView : public Gtk::Widget {
	public:
		EvinceView();

};

// END NAMESPACE
}

#endif
