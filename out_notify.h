#ifndef OUT_NOTIFY_H_
#define OUT_NOTIFY_H_

#include "out.h"
#include "storage.h"

class OutNotify {
public:

	OutNotify(const char * title, const char* separator);

	void add (Out* object);

	void operator() ();

	void clear ();

	 std::string get_title();

	 std::string get_separator();

private:
	std::string title;

	std::string separator;

	Storage<Out*> views;
};

#endif /* OUT_NOTIFY_H_ */
