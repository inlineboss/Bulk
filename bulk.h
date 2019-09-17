#ifndef BULK_H_
#define BULK_H_

#include <memory>

#include "buffer.h"
#include "storage.h"
#include "out_notify.h"

/**
 * \brief Класс пакетной обработки комманд
 */
class Bulk {
public:

	/**
	 * @param max_count_cmd - Максимальное количество комманд в пакете
	 */
	Bulk (int max_count_cmd);

	/**
	 * @brief Получение пакета комманд
	 *
	 * @param outstream - поток ввода
	 */
	void in (std::istream& outstream);

private:

	/**
	 * @brief Интерфейс поведения
	 */
	class Command {
	public:
		/**
		 * @brief Исполнение комманды
		 * @param Входной буффер
		 */
		virtual void execute (Buffer) = 0;

		virtual ~Command() {};

	}; //class Command

	/**
	 * Оповещение
	 */
	class Notify : public Command {
	public:

		Notify(Bulk& obj): obj(obj) {};

		void execute(Buffer ) override;

	private:

		Bulk& obj;

	}; //class Notify

	/**
	 * Закончить обработку пакета
	 */
	class Cancle : public Command {
	public:

		Cancle(Bulk& obj): obj(obj) {};

		void execute(Buffer) override;

	private:

		Bulk& obj;

	}; //class Cancle

	/**
	 * Добавить элемент
	 */
	class Add: public Command {
	public:

		Add(Bulk& obj): obj(obj) {};

		void execute(Buffer msg) override;

	private:

		Bulk& obj;

	};//class Add

	/**
	 * Пустое поведение
	 */
	class Void: public Command {
	public:

		Void(Bulk& obj): obj(obj) {};

		void execute(Buffer) override;

	private:
		Bulk& obj;

	};//class Void

	/**
	 * Управляющий поведением
	 */
	class CommandHandler {

		/**
		 * Слежка за открытием/закрытием фигурных скобок
		 */
		class Brackets {
			public:
				Brackets() = default;

				/**
				 * Получение элемента - фигурной скобки
				 *
				 * @param bracket - Символ '{' || '}'
				 */
				void to_accept (char bracket);

				/**
				 * @brief Проверка на закрытость
				 */
				bool close();

				/**
				 * @brief Сброс счетчиков
				 */
				void clear ();

			private:
				std::size_t counter_open {0};
				std::size_t counter_close {0};

			};//class Brackets

	public:
		/**
		 * Инициализация объекта
		 *
		 * @param ref_bulk - Ссылка на объект реализующий поведение
		 *
		 * @param size - Количество комманд в пакете
		 */
		CommandHandler(Bulk& ref_bulk, int size);

		/**
		 * @brief Анализ команды
		 *
		 * @param input - Команда
		 *
		 * @return Поведение соответствующее полученной команде
		 */
		std::unique_ptr<Command> operator() (std::string input);

		/**
		 * @brief Сброс счетчиков
		 */
		void clear();

		/**
		 * @brief Флаг заполненности пакета
		 *
		 * @return true - Получено максимально допустимое количество комманд,
		 * 			false - Пакет еще не заполнен
		 */
		bool last ();

	private:
		Bulk& ref_bulk;

		const std::size_t  max;

		char target;

		std::size_t index {0};

		Brackets brackets;

	};//class CommandHandler

	/**
	 * @brief Сохранить комманду в хранилище
	 *
	 * @param buff - Комманда
	 */
	void add(Buffer buff);

	/**
	 * @brief Очистка хранилищ
	 */
	void clear ();

	CommandHandler maker;

	OutNotify notify;

	Storage <Buffer> data;

}; //Bulk

#endif /* BULK_H_ */
