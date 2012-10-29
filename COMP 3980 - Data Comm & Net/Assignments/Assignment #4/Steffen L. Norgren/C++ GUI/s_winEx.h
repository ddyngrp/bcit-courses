/*
	MODULE: winEx.h

	PURPOSE: Custom windows exception class

	AUTHORS: Doug Penner
			 Kyle Macdonald
			 Steffen L. Norgren
			 Max Wardell
			 Eddie Zhang
 */

#ifndef _WINEX_H_
#define _WINEX_H_

#include <windows.h>

// out of memory handler that throws WinException
int NewHandler(size_t size);

class WinException {
public:
    WinException(char* msg) : _err(GetLastError()), _msg(msg) {}
    DWORD GetError() const { return _err; }
    char const * GetMessage() const { return _msg; }
private:
    DWORD  _err;
    char * _msg;
};

#endif