#ifndef USERINTF_H
#define USERINTF_H

#include <thread>
#include <mutex>

#include "NamedPipe.h"
#include "UserPackHL.h"


/*! ----------------------------------------------------------------------------------------
 * @brief: Provides UI through named pipes. Creates 2 pipes for reading and writing.
 * -----------------------------------------------------------------------------------------
 * */
class UserInterface {
public:
	/*! ------------------------------------------------------------------------------------
	 * @brief:
	 * -------------------------------------------------------------------------------------
	 * */
	enum class STATE : uint8_t {
		CLOSED = 0,
		OPENED
	};

	/*! ------------------------------------------------------------------------------------
	 * @brief:
	 * -------------------------------------------------------------------------------------
	 * */
	enum MODE : uint8_t {
		OPEN_EXISTING = 1,
		CREATE_NEW
	};

	/*! ------------------------------------------------------------------------------------
	 * @brief:
	 * -------------------------------------------------------------------------------------
	 * */
	enum class RESULT {
		ERROR = -1,
		SUCCESS
	};

	/*! ------------------------------------------------------------------------------------
	 * @brief: Sets mode and calls initialization
	 * -------------------------------------------------------------------------------------
	 * */
	UserInterface(UserInterface::MODE mode);

	/*! ------------------------------------------------------------------------------------
	 * @brief: Calls close
	 * -------------------------------------------------------------------------------------
	 * */
	~UserInterface();

	/*! ------------------------------------------------------------------------------------
	 * @brief: Reads user data from pipe
	 * -------------------------------------------------------------------------------------
	 * */
	UserInterface::RESULT Read(UserPackHL *pack);

	/*! ------------------------------------------------------------------------------------
	 * @brief: Writes user data to pipe
	 * -------------------------------------------------------------------------------------
	 * */
	UserInterface::RESULT Write(const UserPackHL *pack);

	/*! ------------------------------------------------------------------------------------
	 * @brief: Returns false if pipe was broken, but is ready now - catches thread
	 * checks only rd_pipe (wr_pipe is depended, and isn't checkable)
	 * -------------------------------------------------------------------------------------
	 * */
	bool CheckWorkingCapacity();

private:
	/*! ------------------------------------------------------------------------------------
	 * @brief: Interfaces between driver and higher layer
	 * -------------------------------------------------------------------------------------
	 * */
	NamedPipe rd_pipe, wr_pipe;

	/*! ------------------------------------------------------------------------------------
	 * @brief: Mode of UI: open existing pipes or create new
	 * -------------------------------------------------------------------------------------
	 * */
	UserInterface::MODE mode;

	/*! ------------------------------------------------------------------------------------
	 * @brief: Inits threads, mutexes and detaches *_thr
	 * -------------------------------------------------------------------------------------
	 * */
	void Initialization();

	/*! ------------------------------------------------------------------------------------
	 * @brief: Destroy pipes, theads and mutexes
	 * -------------------------------------------------------------------------------------
	 * */
	void Close();

	/*! ------------------------------------------------------------------------------------
	 * @brief: Calls Close and Initialization
	 * -------------------------------------------------------------------------------------
	 * */
	void ReOpen();

	/*! ------------------------------------------------------------------------------------
	 * @brief: Waiting for pipes creating
	 * -------------------------------------------------------------------------------------
	 * */
	void Wait();

	/*! ------------------------------------------------------------------------------------
	 * @brief: Used by *_thr to open pipes in any order
	 * -------------------------------------------------------------------------------------
	 * */
	std::mutex rd_mutex, wr_mutex;

	/*! ------------------------------------------------------------------------------------
	 * @brief: Threads for initialization of pipes
	 * -------------------------------------------------------------------------------------
	 * */
	std::thread rd_thr, wr_thr;

	/*! ------------------------------------------------------------------------------------
	 * @brief: Creates read pipe (opens existing or creates new)
	 * -------------------------------------------------------------------------------------
	 * */
	void rdCreate();

	/*! ------------------------------------------------------------------------------------
	 * @brief: Creates write pipe (opens existing or creates new)
	 * -------------------------------------------------------------------------------------
	 * */
	void wrCreate();

};


#endif