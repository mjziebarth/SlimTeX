/*
 * any_cpp14.hpp
 * Replacement for std::any if std=c++17 is not available.
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

#include <string>
#include <typeindex>

namespace Slimtex {

class any;

template<typename T>
T any_cast(const any&);

class any {
	/* Quick and dirty replacement for std::any if std=c++17 is not
	 * available on compiling system (which is not too unlikely at
	 * time of writing) */
	friend int any_cast<int>(const any&);
	friend bool any_cast<bool>(const any&);
	friend std::string any_cast<std::string>(const any&);
	
	public:
		any(const std::string&);
		any(int);
		any(bool);
		any();
		
		any& operator=(const any&) = default;
		
		const std::type_info& type() const;
		
		bool has_value() const;
	
	private:
		/* Information about content: */
		bool has_val_;
		std::type_index type_;
		
		/* Data space for content: */
		std::string val_str;
		int val_int;
		bool val_bool;
};

}
