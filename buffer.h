#ifndef BUFFER_H_
#define BUFFER_H_

#include <string>
#include <ctime>

#include "out.h"

/**
 * @brief
 */
class Buffer: public Out {
public:
	Buffer();

	Buffer(const Buffer& buffer);

	Buffer(const std::string str);

	/**
	 * @brief Замена команды
	 *
	 * @param cmd - новая команда
	 */
	void reset (const std::string& cmd);

	/**
	 * @brief Удалить комманду
	 */
	void cls ();

	/**
	 * @brief Вывод хранимой комманды
	 */
	void out () override;

	/**
	 * @brief Получение размера команды
	 *
	 * @return Размер
	 */
	std::size_t size ();

	/**
	 * @brief Получение комманды
	 *
	 * @return Комманды
	 */
	std::string get_data();

	/**
	 * @brief Получить время ввода комманды
	 *
	 * @return Время
	 */
	std::time_t get_time ();
private:

	std::time_t time_label;

	std::string data;
};



#endif /* BUFFER_H_ */
