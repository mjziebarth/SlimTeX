/*
 * evinceview.cpp
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
 * along with SlimTeX. If not, see <https://www.gnu.org/licenses/>.
 */

#include <evinceview.hpp>
#include <stdexcept>
#include <utility>

// Handle the communication with the evince view C code
// only internally:
#include <evince-view.h>
#include <evince-document.h>
#include <giomm/file.h>

#include <iostream>

namespace Slimtex {


static GtkWidget* create_ev_view(){
	GtkWidget* widget = ev_view_new();
	if (!widget){
		throw std::runtime_error("Could not allocate evince view!");
	}
	return ev_view_new();
}

EvinceView::EvinceView() :
	// Allocate C object ev_view and move it to base class
	// initializer.
	Gtk::Widget(std::move(*Glib::wrap(create_ev_view()))),
	model(ev_document_model_new())
{
	/* Set model of view: */
	ev_view_set_model(reinterpret_cast<EvView*>(gobj()),
	                  static_cast<EvDocumentModel*>(model));
	
	/* Initialize evince view library: */
	ev_init();
}

EvinceView::~EvinceView()
{
	/* Shutdown evince view library: */
	ev_shutdown();
}

void EvinceView::load(const Glib::RefPtr<Gio::File>& file)

{
	if (!file){
		/* Better throw exception. TODO */
		throw std::runtime_error("Nullpointer passed.");
	}
	
	/* Local variables: */
	EvDocumentModel* document_model = static_cast<EvDocumentModel*>(model);
	EvDocument* old_document = ev_document_model_get_document(document_model);
	GFile* gfile = reinterpret_cast<GFile*>(file->gobj());
	GError* error = nullptr;
	GCancellable* cancellable = g_cancellable_new();
	if (!cancellable){
		throw std::runtime_error("Could not allocate cancellable!");
	}
	
	/* Get new document: */
	EvDocument* document = ev_document_factory_get_document_for_gfile(
	                           gfile, EV_DOCUMENT_LOAD_FLAG_NONE, cancellable,
	                           &error);
	if (!document){
		if (error){
			std::cout << "Error message:\n" << error->message << "\n";
		}
		throw std::runtime_error("Document is NULL!");
	}
	
	/* Set new document and load: */
	ev_document_model_set_document(document_model, document);
	gboolean load_success = 
		ev_document_load_gfile(document, gfile, EV_DOCUMENT_LOAD_FLAG_NONE,
		                       cancellable, &error);
	if (!load_success || error){
		throw std::runtime_error("Failed to load document!");
	}
	
	/* Clean up: */
	if (old_document){
		free(old_document);
	}
}

}
