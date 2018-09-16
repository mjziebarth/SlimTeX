/*
 * styling.hpp
 * Contains definition of string constants used in the style config
 * file. These keys enumerate the possible entries in the style config file.
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

#include <styling.hpp>
#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <iostream>
#include <string>

namespace Slimtex {

// Window properties:
const char* STYLE_KEY_WINDOW_MIN_WIDTH = "window.min_width";
const char* STYLE_KEY_WINDOW_MIN_HEIGHT = "window.min_height";

// Text editor properties:
const char* STYLE_KEY_CODEVIEW_FONT_FAMILY = "codeview.font_face";
const char* STYLE_KEY_CODEVIEW_FONT_SIZE = "codeview.font_size";
const char* STYLE_KEY_CODEVIEW_MIN_WIDTH = "codeview.min_width";
const char* STYLE_KEY_CODEVIEW_MIN_HEIGHT = "codeview.min_height";



/* Array of all properties: */


/******************************************************************************/

static std::any read_attribute(xmlNode* node)
{
	xmlAttr* attribute = node->properties;
	std::string type;
	std::string val;
	while(attribute){
		/* Read attribute name and value: */
		const xmlChar* attr_name = attribute->name;
		xmlChar* val_ = xmlNodeListGetString(node->doc, attribute->children, 1);
		
		/* Convert value to std::string: */
		char* c =  (char*)val_;
		int len = xmlStrlen(val_);
		std::string val_str(c,len);
		xmlFree(val_); 
		
		/* Assign to result: */
		if (xmlStrEqual(attr_name, BAD_CAST("type"))){
			type = val_str;
		} else if (xmlStrEqual(attr_name, BAD_CAST("value"))){
			val = val_str;
		}
		attribute = attribute->next;
	}
	
	/* Construct std::any: */
	if (type == "int"){
		return std::any(std::stoi(val));
	}
	if (type != "str"){
		std::cout << "TYPE: " << type << "\n";
		throw std::runtime_error("Unknown type in XML!");
	}
	return std::any(val);
}


static void build_style_dict_recursive(xmlNode* node, std::string prefix,
                           std::unordered_map<std::string,std::any>& style_dict)
{
	for (; node; node = node->next){
		if (node->type != XML_ELEMENT_NODE){
			continue;
		}
		/* Create string from xmlChar*: */
		char* c =  (char*)node->name;
		int len = xmlStrlen(node->name);
		std::string name(c,len);
		/* Create full key: */
		std::string full_key((prefix.empty()) ? name : prefix + "." + name); 
		if (node->children){
			// Nodes with children are not elements we want to add to the
			// style dict.
			build_style_dict_recursive(node->children, full_key, style_dict);
		} else {
			// Attributes are the leaves. Add!
			if (style_dict.count(full_key) > 0){
				throw std::runtime_error("Style attribute defined twice.");
			}
			// Read value:
			style_dict[full_key] = read_attribute(node);
		}
	}
}


// The xml parsing:
Styling::Styling(const char* filename)
{
	/* Parse XML: */
	xmlDocPtr doc; //

	doc = xmlReadFile(filename, NULL, 0);
	if (doc == NULL) {
		throw std::runtime_error("Could not read styling xml!");
	}
	
	/* Load keys: */
	xmlNode* root = xmlDocGetRootElement(doc);
	if (root){
		build_style_dict_recursive(root->children, "", style_dict);
	} else {
		throw std::runtime_error("Empty style xml!");
	}
	
	/* Clean: */
	xmlFreeDoc(doc);
}

std::any Styling::operator[](const std::string& key) const
{
	return style_dict.at(key);
}


// END NAMESPACE
}
