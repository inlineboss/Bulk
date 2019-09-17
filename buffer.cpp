#include "buffer.h"

#include <iostream>

Buffer::Buffer(): time_label{0}, data("") {}

Buffer::Buffer(const Buffer& buffer):
		time_label(buffer.time_label), data(buffer.data) {}

Buffer::Buffer(const std::string str):
		time_label (std::time(nullptr)), data (str) {}

void Buffer::reset (const std::string& cmd) {
	data = cmd;
	time_label = std::time(nullptr);
}

void Buffer::cls () {
	data.clear();
	time_label = 0;
}

void Buffer::out () {
	std::cout << data ;
}

std::size_t Buffer::size () {

	return data.size();
}

std::string Buffer::get_data() {
	return data.c_str();
}

std::time_t Buffer::get_time () {
	return time_label;
}
