#ifndef BULK_H_
#define BULK_H_

#include <memory>

#include "buffer.h"
#include "storage.h"
#include "out_notify.h"

class Bulk {
public:

	Bulk (int max_count_cmd);

	void in (std::istream& outstream);

private:

	class Command {
	public:

		virtual void execute (Buffer) = 0;

		virtual ~Command() {};
	};

	class Notify : public Command {
	public:

		Notify(Bulk& obj): obj(obj) {};

		void execute(Buffer ) override;

	private:
		Bulk& obj;
	};

	class Cancle : public Command {
	public:

		Cancle(Bulk& obj): obj(obj) {};

		void execute(Buffer) override;

	private:
		Bulk& obj;
	};

	class Add: public Command {
	public:

		Add(Bulk& obj): obj(obj) {};

		void execute(Buffer msg) override;

	private:
		Bulk& obj;
	};

	class Void: public Command {
	public:

		Void(Bulk& obj): obj(obj) {};

		void execute(Buffer) override;

	private:
		Bulk& obj;
	};

	class CommandHandler {

		class Brackets {
			public:
				Brackets() = default;

				void to_accept (char bracket);

				bool close();

				void clear ();

			private:
				std::size_t counter_open {0};
				std::size_t counter_close {0};
			};

	public:
		CommandHandler(Bulk& ref_bulk, int size);

		std::unique_ptr<Command> operator() (std::string input);

		void clear();

		bool last ();

	private:
		Bulk& ref_bulk;

		const std::size_t  max;

		char target;

		std::size_t index {0};

		Brackets brackets;
	};

	void add(Buffer buff);

	void clear ();

	CommandHandler maker;

	OutNotify notify;

	Storage <Buffer> data;
};

#endif /* BULK_H_ */
