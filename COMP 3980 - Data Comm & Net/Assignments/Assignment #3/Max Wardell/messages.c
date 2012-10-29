#include "cases.h"
#include "functions.h"

/*Various messages to assist the user.*/
void ChoosePortMsg() {
	MessageBox(NULL, TEXT("No port selected, please choose a port."), TEXT(""), MB_OK);
}
void FailedPortMsg() {
	MessageBox(NULL, TEXT("Could not open port. Try another port."), TEXT(""), MB_OK);
}
void ErrorFailedPortMsg() {
	MessageBox(NULL, TEXT("Error opening COM port."), TEXT(""), MB_OK);
}
void FailedSavePortMsg() {
	MessageBox(NULL, TEXT("Error, could not save port."), TEXT(""), MB_OK);
}
void FailedConnectionMsg() {
	MessageBox(NULL, TEXT("Could not connect."), TEXT(""), MB_OK);
}
void ConnectMsg() {
	MessageBox(NULL, TEXT("Successfully connected!."), TEXT(""), MB_OK);
}
void DConnectMsg() {
	MessageBox(NULL, TEXT("Successfully disconnected!."), TEXT(""), MB_OK);
}
void WriteErrorMsg() {
	MessageBox(NULL, TEXT("Error, could not write character."), TEXT(""), MB_OK);
}
void CntChngSettingsMsg() {
	MessageBox(NULL, TEXT("Cannot change settings while in Connect Mode.\nPlease disconnect first."), TEXT(""), MB_OK);
}
void ReadThreadErrorMsg() {
MessageBox(NULL, TEXT("Error creating READ thread"), TEXT("") ,MB_OK);
}
void HelpMsg() {
	MessageBox(NULL,
		TEXT("Welcome to the Intelligent Terminal Emulator!\n\nThis program emulates the vt100 video terminal. It communicates via serial port connection. Its capabilities include being able to interact with the Linux command-line interface. It interprets all escape codes necessary to interact with the Alpine email client.\n\nTo Connect:\nClick on the Port drop-down menu and select the port your serial cable is connected to.\nOnce said port has been selected, choose your desired port settings and click OK.\nClick on the Connect drop-down menu and click Connect. Click Disconnect to end your session.\n\nInteracting with the command-line:\nPress the Enter key to get initial input.\nLogin using your Linux username and password.\nType in \"alpine\" to start up the program.  You can also do other terminal commands here such as installing the program or moving files.\nIn alpine, simply click 'h' or scroll to the help menu item to view Alpine's interface commands."), 
		TEXT("Troubleshooting"), MB_OK);
}
