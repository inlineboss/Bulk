#include "out_notify.h"

#include <iostream>

OutNotify::OutNotify(const char * title, const char* separator) :
	title (title), separator(separator) {}

void OutNotify::add (Out* object) {
	views.add(object);
}

void OutNotify::operator() () {

	std::size_t last_index {0};

	if(views.size() == 0) {
		 return;
	}

	std::cout << title <<": ";

	if(views.size() == 1) {
		views[0]->out(); std::cout << std::endl;
		return;
	}

	for (std::size_t i = 0; i < views.size() - 1; ++i) {

		views[i]->out(); std::cout << ", ";

		last_index = i;
	}

	views[++last_index]->out();

	std::cout << std::endl;
}

void OutNotify::clear () {
	views.clear();
}

std::string OutNotify::get_title() {
	return title.c_str();
}

std::string OutNotify::get_separator() {
	return separator.c_str();
}
