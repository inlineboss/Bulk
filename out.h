#ifndef OUT_H_
#define OUT_H_

/**
 * @brief Интерфейс вывода
 */
class Out {
public:
	/**
	 * @brief Вывод элментов
	 */
	virtual void out () = 0;

	virtual ~Out() {};

};//class Out

#endif /* OUT_H_ */
