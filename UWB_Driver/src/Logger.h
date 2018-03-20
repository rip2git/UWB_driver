#ifndef LOGGER_H_
#define LOGGER_H_

#include <fstream>
#include <string>


/*! ----------------------------------------------------------------------------------------
 * @brief: Provides logging
 * -----------------------------------------------------------------------------------------
 * */
class Logger : public std::fstream {
public:
	/*! ------------------------------------------------------------------------------------
	 * @brief:
	 * -------------------------------------------------------------------------------------
	 * */
	enum class MODE : int {
		OFF = 0,
		CONSOLE = 1,
		FILE = 2
	};

	/*! ------------------------------------------------------------------------------------
	 * @brief:
	 * -------------------------------------------------------------------------------------
	 * */
	Logger() : std::fstream() {};

	/*! ------------------------------------------------------------------------------------
	 * @brief:
	 * -------------------------------------------------------------------------------------
	 * */
	~Logger();

	/*! ------------------------------------------------------------------------------------
	 * @brief:
	 * -------------------------------------------------------------------------------------
	 * */
	void toNull();

	/*! ------------------------------------------------------------------------------------
	 * @brief:
	 * -------------------------------------------------------------------------------------
	 * */
	void toConsole();

	/*! ------------------------------------------------------------------------------------
	 * @brief:
	 * -------------------------------------------------------------------------------------
	 * */
	void toFile();
};



#endif