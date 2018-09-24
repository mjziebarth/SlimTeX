/*
 * any_cpp14.cpp
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

#include <any_cpp14.hpp>
#include <stdexcept>

namespace Slimtex {

/* Constructors: */
any::any() :
	has_val_(false), type_(typeid(nullptr))
{
}

any::any(const std::string& str) :
	val_str(str), has_val_(true),
	type_(typeid(bool))
{
}

any::any(int i) :
	val_int(i), has_val_(true),
	type_(typeid(int))
{
}

any::any(bool b) :
	val_bool(b), has_val_(true),
	type_(typeid(bool))
{
}

/* Methods for any: */
const std::type_info& any::type() const
{
	if (type_ == std::type_index(typeid(int)))
	{
		return typeid(int);
	}
	else if (type_ == std::type_index(typeid(bool)))
	{
		return typeid(bool);
	}
	return typeid(std::string);
}

bool any::has_value() const
{
	return has_val_;
}


/* Casting: */
template<>
int any_cast<int>(const any& a)
{
	if (!a.has_value()){
		throw std::runtime_error("Typecast (to int) of empty any requested!");
	}
	if (a.type_ != std::type_index(typeid(int))){
		throw std::runtime_error("Invalid typecast (to int) requested!");
	}
	return a.val_int;
}

template<>
bool any_cast<bool>(const any& a)
{
	if (!a.has_value()){
		throw std::runtime_error("Typecast (to bool) of empty any requested!");
	}
	if (a.type_ != std::type_index(typeid(bool))){
		throw std::runtime_error("Invalid typecast (to bool) requested!");
	}
	return a.val_bool;
}

template<>
std::string any_cast<std::string>(const any& a)
{
	if (!a.has_value()){
		throw std::runtime_error("Typecast (to string) of empty any requested!");
	}
	if (a.type_ != std::type_index(typeid(std::string))){
		throw std::runtime_error("Invalid typecast (to string) requested!");
	}
	return a.val_str;
}


// END NAMESPACE
}
