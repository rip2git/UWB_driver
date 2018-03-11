#ifndef COMPort_H
#define COMPort_H

#ifdef __linux__
	typedef unsigned long DWORD;
	typedef int HANDLE;
#else
	typedef unsigned long DWORD;
	typedef void* HANDLE;
#endif

typedef unsigned char uint8;


/* -----------------------------------------------------------------------------------------
 * Interface between driver and hard devices
 * -----------------------------------------------------------------------------------------
 * */
class COMPort {
public:
	/* -------------------------------------------------------------------------------------
	 * -------------------------------------------------------------------------------------
	 * */
	enum class STATE {
		CLOSED = 0,
		OPENED
	};

	/* -------------------------------------------------------------------------------------
	 * -------------------------------------------------------------------------------------
	 * */
	struct TimeOutStruct {
		DWORD Ms;
		DWORD nChars;
	};

	/* -------------------------------------------------------------------------------------
	 * -------------------------------------------------------------------------------------
	 * */
	struct InitializationStruct {
		char *portName;
		DWORD baudRate;
		TimeOutStruct timeOut;
	};

	/* -------------------------------------------------------------------------------------
	 *
	 * -------------------------------------------------------------------------------------
	 * */
	COMPort();
	COMPort(InitializationStruct *initStr);

	/* -------------------------------------------------------------------------------------
	 * Calls Close
	 * -------------------------------------------------------------------------------------
	 * */
	~COMPort();

	/* -------------------------------------------------------------------------------------
	 * -------------------------------------------------------------------------------------
	 * */
	COMPort::STATE GetState() const;

	/* -------------------------------------------------------------------------------------
	 * Closes file descriptor
	 * -------------------------------------------------------------------------------------
	 * */
	void Close();

	/* -------------------------------------------------------------------------------------
	 * Flush by OS abilities
	 * -------------------------------------------------------------------------------------
	 * */
	bool FastFlush() const;

	/* -------------------------------------------------------------------------------------
	 * Slow flush: doing fast flush, gets delay = charsSpacing and tries to read byte.
	 * *** If last is failed when return true, else repeats from the beginning.
	 * *** Changes timeOut for its own purposes. Returns timeOut before return from call
	 * -------------------------------------------------------------------------------------
	 * */
	void Flush() const;

	/* -------------------------------------------------------------------------------------
	 * Returns current time out
	 * -------------------------------------------------------------------------------------
	 * */
	const TimeOutStruct* GetCurrentTimeOut() const;

	/* -------------------------------------------------------------------------------------
	 * -------------------------------------------------------------------------------------
	 * */
	int GetAvailableBytesOfRecvBuf() const;

	/* -------------------------------------------------------------------------------------
	 * Sets timeOut and calls ChangeTimeOut
	 * -------------------------------------------------------------------------------------
	 * */
	bool SetTimeOut(const TimeOutStruct *timeOut);

	/* -------------------------------------------------------------------------------------
	 * -------------------------------------------------------------------------------------
	 * */
	void Initialization(InitializationStruct *initStr);

	/* -------------------------------------------------------------------------------------
	 * Reads data from buffer (behavior is dependent on parameters of ChangeTimeOut);
	 * *** Returns received bytes (0:n) or failure (-1)
	 * -------------------------------------------------------------------------------------
	 * */
	int Read(uint8 *buffer, uint8 buffer_size) const;

	/* -------------------------------------------------------------------------------------
	 * Reads one byte from buffer (behavior is dependent on parameters of ChangeTimeOut);
	 * *** Returns received bytes (0:1) or failure (-1)
	 * -------------------------------------------------------------------------------------
	 * */
	int ReadByte(uint8 *buffer) const;

	/* -------------------------------------------------------------------------------------
	 * Writes data to buffer (up to 256 bytes per write) / transfers data as is
	 * *** Returns transfered (n) bytes or failure (-1)
	 * -------------------------------------------------------------------------------------
	 * */
	int Write(const uint8 *buffer, uint8 buffer_size) const;
	int Write(const char *buffer) const;

private:
	/* -------------------------------------------------------------------------------------
	 * File descriptor / used by OS
	 * -------------------------------------------------------------------------------------
	 * */
	HANDLE fd;

	/* -------------------------------------------------------------------------------------
	 * -------------------------------------------------------------------------------------
	 * */
	COMPort::STATE state;

	/* -------------------------------------------------------------------------------------
	 * -------------------------------------------------------------------------------------
	 * */
	DWORD baudRate;

	/* -------------------------------------------------------------------------------------
	 * Current time out
	 * -------------------------------------------------------------------------------------
	 * */
	TimeOutStruct timeOut;

	/* -------------------------------------------------------------------------------------
	 * length of 10 bytes in ms
	 * -------------------------------------------------------------------------------------
	 * */
	uint8 charsSpacing;

	/* -------------------------------------------------------------------------------------
	 * Checks port for system errors / close if it was detected
	 * -------------------------------------------------------------------------------------
	 * */
	bool GetStatus() const;

	/* -------------------------------------------------------------------------------------
	 * Resets errno
	 * -------------------------------------------------------------------------------------
	 * */
	int GetLastSystemError() const;

	/* -------------------------------------------------------------------------------------
	 * Changes the algorithm for receiving data:
	 * *** User sets time out to read data and number of chars which should be received;
	 * *** Reset errno
	 * -------------------------------------------------------------------------------------
	 * */
	bool ChangeTimeOut(const TimeOutStruct *timeOut) const;
};


#endif
