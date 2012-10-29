#include "message.h"

void Message::ChoosePort() {
	MessageBox(NULL, TEXT("No port selected, please choose a port."), TEXT(""), MB_OK);
}

void Message::FailedPort() {
	MessageBox(NULL, TEXT("Could not open port. Try another port."), TEXT(""), MB_OK);
}

void Message::ErrorFailedPort() {
	MessageBox(NULL, TEXT("Error opening COM port."), TEXT(""), MB_OK);
}

void Message::FailedSavePort() {
	MessageBox(NULL, TEXT("Error, could not save port."), TEXT(""), MB_OK);
}

void Message::FailedConnection() {
	MessageBox(NULL, TEXT("Could not connect."), TEXT(""), MB_OK);
}

void Message::Connect() {
	MessageBox(NULL, TEXT("Successfully connected!."), TEXT(""), MB_OK);
}

void Message::DConnect() {
	MessageBox(NULL, TEXT("Successfully disconnected!."), TEXT(""), MB_OK);
}

void Message::WriteError() {
	MessageBox(NULL, TEXT("Error, could not write character."), TEXT(""), MB_OK);
}

void Message::CntChngSettings() {
	MessageBox(NULL, TEXT("Cannot change settings while in Connect Mode.\nPlease disconnect first."), TEXT(""), MB_OK);
}

void Message::ReadThreadError() {
MessageBox(NULL, TEXT("Error creating READ thread"), TEXT("") ,MB_OK);
}

void Message::HelpAbout() {
	MessageBox(NULL,
		TEXT("Welcome to the RFID Scanner, Assignment #3 for COMP 3980\n\nAuthors:  Doug Penner\n\tKyle Macdonald\n\tSteffen L. Norgren\n\tMax Wardell\n\tEddie Zhang"), 
		TEXT("About RFID Scanner"), MB_OK);
}

