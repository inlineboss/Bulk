#include "bulk.h"

#include <iostream>

Bulk::Bulk (int max_count_cmd):
	maker(*this, max_count_cmd), notify("bulk", ",") {}

void Bulk::in(std::istream& outstream) {

	std::string input;

	while(!maker.last()) {

		if (std::getline (outstream, input)) {

				maker(input)->execute(input);
		}
	}
	std::cout << std::endl;
	notify();

	clear();
}

void Bulk::Notify::execute(Buffer) {
	obj.notify();
	obj.clear();
}

void Bulk::Cancle::execute(Buffer) {
	obj.clear();
}

void Bulk::Add::execute(Buffer msg) {
	obj.add(msg);
}

void Bulk::Void::execute(Buffer) {

}

void Bulk::CommandHandler::Brackets::to_accept (char bracket) {

	switch(bracket) {
	case '{':
		counter_open++;
		break;

	case '}':
		counter_close++;
		break;
	}
}

bool Bulk::CommandHandler::Brackets::close () {

	if( counter_open == counter_close ) {

		counter_open = counter_close = 0;

		return true;

	} else {

		return false;
	}
}

void Bulk::CommandHandler::Brackets::clear () {
	counter_open = counter_close = 0;
}

Bulk::CommandHandler::CommandHandler(Bulk& ref_bulk, int size):
		ref_bulk (ref_bulk), max(size), target('}')
{}

std::unique_ptr<Bulk::Command>
Bulk::CommandHandler::operator ()(std::string input) {

	if (input == "{") {
		target = '{';
		brackets.to_accept('{');
		return std::make_unique<Bulk::Void>(ref_bulk);
	}

	if (input == "}") {
		target = '}';
		brackets.to_accept('}');
		return std::make_unique<Bulk::Void>(ref_bulk);
	}

	if (input == "") {
		target = 'q';
	}

	switch (target) {
	case '}':

		++index;
		return std::make_unique<Bulk::Add>(ref_bulk);
	break;
	case '{' :

		return std::make_unique<Bulk::Add>(ref_bulk);
	break;
	case 'q' :

		if( brackets.close() ) {

			brackets.clear();
			return std::make_unique<Bulk::Notify>(ref_bulk);

		} else {

			brackets.clear();
			return std::make_unique<Bulk::Cancle>(ref_bulk);

		}

	break;
	default:

		return std::make_unique<Bulk::Void>(ref_bulk);
	break;
	}
}

void Bulk::CommandHandler::clear() {
	index = 0;
	target = '}';
}

bool Bulk::CommandHandler::last() {
	return max == index;
}

void Bulk::add(Buffer buff) {

	data.add(buff);
	notify.add(&data.last());
}

void Bulk::clear () {
	data.save_log(std::string{},
					notify.get_title());
	notify.clear();

	data.clear();

	maker.clear();
}
