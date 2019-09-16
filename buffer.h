#ifndef BUFFER_H_
#define BUFFER_H_

#include <string>
#include <ctime>

#include "out.h"

class Buffer: public Out {
public:
	Buffer();

	Buffer(const Buffer& buffer);

	Buffer(const std::string str);

	void reset (const std::string& cmd);

	void cls ();

	void out () override;

	void size ();

	std::string get_data();

	std::time_t get_time ();
private:

	std::time_t time_label;

	std::string data;
};



#endif /* BUFFER_H_ */
