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
void HelpAbout() {
	MessageBox(NULL,
		TEXT("Welcome to the RFID Scanner, Assignment #3 for COMP 3980\n\nAuthors:  Doug Penner\n\tKyle Macdonald\n\tSteffen L. Norgren\n\tMax Wardell\n\tEddie Zhang"), 
		TEXT("About RFID Scanner"), MB_OK);
}
