#include <windows.h>

class Message {
public:
	static void ChoosePort();
	static void FailedPort();
	static void ErrorFailedPort();
	static void FailedSavePort();
	static void FailedConnection();
	static void Connect();
	static void DConnect();
	static void WriteError();
	static void CntChngSettings();
	static void ReadThreadError();
	static void HelpAbout();
};

