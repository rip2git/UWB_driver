
#include "COMHandler.h"
#include "main.h"
#include <windows.h>

/// linker, misc
/// -static-libgcc -static-libstdc++


//#define Main_DEBUG_MODE


#define POLL_PERIOD 	500


unsigned char buf[128];
unsigned char buf_size;
unsigned int distance;
COMHandler hPort;
COMHandler::RESULT opRes;



DWORD WINAPI receive(CONST LPVOID lpParam)
{
	UserPack upack;
	cout << "***rd on" << endl;
	HANDLE hMutex = (HANDLE)lpParam;

	while (1) {
		WaitForSingleObject(hMutex, INFINITE);
		opRes = hPort.Receive(&upack);
		ReleaseMutex(hMutex);
		if (opRes == COMHandler::RESULT::SUCCESS) {
			if (upack.Command == UserPack::COMMAND::Status) {
				cout << "ERROR: " << static_cast <int> (upack.DestinationID) << endl;
			} else {
				upack.Print();
				cout << " distance: " << static_cast <int> (upack.Data[6] + (upack.Data[7] << 8)) << " cm" << endl;
			}
		}
	}
}


int main()
{
	std::string n;
	unsigned char poll_msg[] = "__OK__00";
	UserPack upack;

	int mainstate = 0;
	TON t1;

	if (hPort.GetState() == COMHandler::STATE::OPENED)
		cout << "*** COM" << static_cast <int> (hPort.GetPortNumber()) << " opened" << endl;
	else
		cout << "***error" << endl;


	HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);

	t1.start(0);
	while (1) {
		switch (mainstate) {
			case 0:
			{
				upack.Command = UserPack::COMMAND::SetID;
				upack.DestinationID = hPort.GetPortNumber() & 0x0F;
				upack.TotalSize = 0;
				WaitForSingleObject(hMutex, INFINITE);
				hPort.Send(&upack);
				opRes = hPort.Receive(&upack);
				ReleaseMutex(hMutex);

				if (opRes == COMHandler::RESULT::SUCCESS) {
					for (uint8 i = 0; i < upack.TotalSize; ++i)
						cout << upack.Data[i];
					cout << endl;
					mainstate = 1;
				}
			} break;
			case 1:
			{
				upack.Command = UserPack::COMMAND::Distance;
				upack.DestinationID = UserPack::BROADCAST_ID;
				upack.TotalSize = sizeof(poll_msg);
				upack.SetData(poll_msg);

				HANDLE thr = CreateThread(NULL, 0, &receive, &hMutex, DETACHED_PROCESS, NULL);
				if (thr == INVALID_HANDLE_VALUE) {
					cout << "***thread error" << endl;
					cin >> buf;
					exit(0);
				}
				Sleep(11);
				cout << "***wr on" << endl;
				mainstate = 2;
			} break;
			case 2:
			{
				//std::getline(cin, n);
				Sleep(490);
				WaitForSingleObject(hMutex, INFINITE);
				hPort.Send(&upack);
#ifdef Main_DEBUG_MODE
				opRes = hPort.Receive(&upack);
				if (opRes == COMHandler::RESULT::SUCCESS)
					cout << "***sended: " << t1.since() << endl;
#else
				cout << "***sended: " << t1.since() << endl;
#endif
				ReleaseMutex(hMutex);
			} break;

			default: // nop
				break;
		}
	}

	return 0;
}

