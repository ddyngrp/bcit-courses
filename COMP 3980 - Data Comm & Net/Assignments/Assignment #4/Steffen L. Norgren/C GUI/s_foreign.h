/*
	MODULE: s_foreign.h

	PURPOSE: Contains references to all foreign functions that are
			 ouside the scope of the GUI.

	AUTHORS: Doug Penner
			 Kyle Macdonald
			 Steffen L. Norgren
			 Max Wardell
			 Eddie Zhang
*/

#ifndef _FOREIGN_H
#define _FOREIGN_H

BOOL foreign_Connect(char *);
void foreign_Disconnect();
void foreign_SendText(char *);

#endif

BOOL foreign_Connect(char * something) {
	return TRUE;
}

void foreign_Disconnect() {
}

void foreign_SendText(char * sendText) {
}