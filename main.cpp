#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <memory>
#include <ctime>

#include <fstream>
#include <sstream>

#include "bulk.h"

int main (int, const char **) {

	try {

	Bulk bulk(4);

	while(true){
			bulk.in(std::cin);
	}

	} catch(...) {

		std::cout << "BLA" << std::endl;
	}

    return 0;
}
