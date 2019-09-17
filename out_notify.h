#ifndef OUT_NOTIFY_H_
#define OUT_NOTIFY_H_

#include "out.h"
#include "storage.h"

/**
 * @brief Хранилище интерфейсов вывода
 */
class OutNotify {
public:

	/**
	 * @brief Инициализация хранилища
	 *
	 * @param title - Заголовок
	 * @param separator - Разделитель
	 */
	OutNotify(const char * title, const char* separator);

	/**
	 * @brief Добавление элемента
	 *
	 * @param object - Добавляемый элемент
	 */
	void add (Out* object);

	/**
	 * @brief Вызвать все хранимые элементы
	 */
	void operator() ();

	/**
	 * @brief Очистить хранилище
	 */
	void clear ();

	/**
	 * @brief Получить заголовок
	 * @return Заголовок
	 */
	 std::string get_title();
	 /**
	  * @brief Получить разделитель
	  *
	  * @return Разделитель
	  */
	 std::string get_separator();

private:
	std::string title;

	std::string separator;

	Storage<Out*> views;
};

#endif /* OUT_NOTIFY_H_ */
