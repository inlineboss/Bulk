#include "bulk.h"

#include <iostream>
#include <string>

int main (int argc, const char* argv[]) {

	try {

		if(argc > 1) {

			Bulk bulk( std::stoi(argv[1]) );

			while(true){
				bulk.in(std::cin);
			}

		}

	} catch(...) {

		std::cout << "BLA" << std::endl;
	}

    return 0;
}
