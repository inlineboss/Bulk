#ifndef STORAGE_H_
#define STORAGE_H_

#include <string>
#include <fstream>

template<typename T>
class Storage {
public:

	struct Node {
		Node* prev = nullptr;
		T data;
	};

	void add (const T& data) {

		if (Head == nullptr) {

			Tail = Head = new Node;

			Head->data = data;

		} else {
			Node* new_node = new Node;

			new_node->data = data;

			Tail->prev = new_node;

			Tail = Tail->prev;
		}

		++count_object;
	}

	T& operator[](std::size_t numb) {

		Node* Index = Head;

		if(numb == 0) {
			return Index->data;
		}

		for (std::size_t i = 0; i < numb; ++i) {
			Index = Index->prev;
		}

		return Index->data;
	}

	void clear () {

		while (Head != nullptr) {

			Node* ptr = Head;

			Head = Head->prev;

			delete ptr;
		}

		Head = Tail = nullptr;
		count_object = 0;
	}

	std::size_t size() {
		return count_object;
	}

	T& last () { return Tail->data;	}

	~Storage() {
		clear();
	}

	void save_log(std::string path, std::string name) {

		if( Head == nullptr ) {
			return;
		}
		std::ofstream file;

		file.open( path + name + std::to_string(Head->data.get_time()) + ".log");

		for (std::size_t i = 0; i < count_object; i++) {
			file << (*this)[i].get_data() << " ";
		}

		file.close();
	}

private:
	Node* Tail = nullptr;
	Node* Head = nullptr;

	std::size_t count_object {0};
};



#endif /* STORAGE_H_ */
