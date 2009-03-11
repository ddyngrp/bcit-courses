// TestQue.cpp : Defines the entry point for the console application.
//


#include "stdafx.h" 
#include <assert.h>
#include <iostream>

#include <sstream>
#include <string>
using namespace std;

#include "CircularBuffer.h"

///////////////////////////////////////////////////////////////////////////
// QueInfo
//
// Purpose:		stores info for threads

struct QueInfo
{
	CircularBuffer *	que;			// circular que
	long				index;			// string index
	HANDLE				hWriteEvent;	// handle to write thread done
	bool				retWrite;		// return from write thread
	HANDLE				hReadEvent;		// handle to read thread done
	bool				retRead;		// return from read thread
	string				txtText[3];		// text strings for test
	string				strGet;			// recieves text read

};

///////////////////////////////////////////////////////////////////////////
// testWriteQue
//
// Purpose:		thread to write to circular que

DWORD WINAPI testWriteQue ( LPVOID lpParameter )
{
	// get params
	QueInfo &	    info  = *( (QueInfo *) lpParameter );
	CircularBuffer &	que	  = *info.que;
	long			index = info.index;

	// set current text put and txt end
	const char * txt = info.txtText[index].c_str();
	long length      = info.txtText[index].size();

	char * txtPut = (char *) txt;
	char * txtEnd = (char *) txt + length;

	// show not finished writing string
	bool putDone = false;

	// perform random write
	while ( !putDone )
	{
		long count;
		if ( que.writeCount(count) )
		{
			// write min of text remaing to 
			// write or max can put into buffer
			count = min(strlen(txtPut),count);

			if ( count > 0 )
			{
				que.write( (BYTE *) txtPut, count );

				cout << "Wrote Chars: " << count << endl;

				txtPut += count;

				if ( txtPut == txtEnd )
					putDone = true;
			}

			cout << "Read Pos: " << que.readPos() << " Write Pos: " << que.writePos() << endl;
		}
		else
			cout << "Cant write" << endl;

	}

	// get if success
	info.retWrite = putDone;

	// show done
	::SetEvent( info.hWriteEvent );

	return putDone;
}

///////////////////////////////////////////////////////////////////////////
// testReadQue
//
// Purpose:		thread to read from circular que

DWORD WINAPI testReadQue ( LPVOID lpParameter )
{
	// buffer for gets
	char txtGet[256];

	// get params
	QueInfo &	    info   = *( (QueInfo *) lpParameter );
	CircularBuffer &	que	   = *info.que;
	long			index  = info.index;
	string &		strGet = info.strGet;

	// string for collecting text
	strGet = "";

	// show not finished reading string
	bool getDone = false;

	// perform random read
	while ( !getDone )
	{
		long count;
		if ( que.readCount(count) )
		{
			// read min of text remaing to 
			// read or max can get from buffer
			count = min( info.txtText[index].size() - info.strGet.size(),count);

			// get text
			memset(txtGet,0,256);
			que.read( (BYTE *) txtGet, count );

			cout << "Read Chars: " << count << endl;

			strGet += txtGet;
			if ( strGet.size() >= info.txtText[index].size() )
				getDone = true;

			cout << "Read Pos: " << que.readPos() << " Write Pos: " << que.writePos() << endl;
		}
		else
			cout << "Cant read" << endl;

	}

	// get if success
	info.retRead = getDone;

	// show done
	::SetEvent( info.hReadEvent );

	return getDone;

}


///////////////////////////////////////////////////////////////////////////
// testQue
//
// Purpose:		text read/write to que

bool testQue ( QueInfo & info )
{
	// show test not done
	bool done = false;

	// show write not done
	bool put  = false;

	// show read not done
	bool get  = false;

	// init thread handles
	HANDLE hWriteThread = 0;
	HANDLE hReadThread  = 0;

	// init thread ids
	ULONG idWriteThread = 0;
	ULONG idReadThread  = 0;

	// init return values from values
	info.retWrite = false;	
	info.retRead  = false;	

	// create read thread
	hReadThread = 
	CreateThread( NULL, 0, testReadQue, (LPVOID) &info, 0, &idReadThread );

	// create write thread
	hWriteThread = 
	CreateThread( NULL, 0, testWriteQue, (LPVOID) &info, 0, &idWriteThread );

	// get events
	HANDLE hEvents[2];
	hEvents[0] = info.hReadEvent;
	hEvents[1] = info.hWriteEvent;

	// test que multi-thread read/write
	bool success = false;
	while ( !done )
	{
		// wait for results
		DWORD wait =
		WaitForMultipleObjects( 2, hEvents, false, INFINITE );

		// get wait for results
		switch ( wait )
		{
			case WAIT_OBJECT_0:
			{
				if ( !get )
					get = info.retRead;

				::ResetEvent( info.hReadEvent );
			}

			case WAIT_OBJECT_0 + 1:
			{
				if ( !put )
					put = info.retWrite;

				::ResetEvent( info.hWriteEvent );
			}
		}

		// test if done
		if ( get & put )
		{
			if ( info.strGet == info.txtText[info.index] )
				success = true;

			done = true;
		}
	}

	return success;
}

int main(int argc, char* argv[])
{
	// randomize que size for testing
	long queSz = rand();
	if ( queSz > 100 )
		queSz = 100;

	cout << "Que size: " << queSz << endl;

	// create que
	CircularBuffer que;
	que.create(queSz);

	// init thread info
	QueInfo info;
	info.que   = &que;
	info.index = 0;

	// initialize text strings
	info.txtText[0] = "This is a long line of text. using it i can test the circular que. Obviously it is a pointless piece of text. So what. Take a cigar and shove it.";
	info.txtText[1] = "Could there be anything worse than typing in pointless text for testing?";
	info.txtText[2] = "Yes there could be. Typing in the answer. Way to many nights with the computer!";

	// create thread kill events
	info.hWriteEvent = ::CreateEvent( NULL, TRUE, FALSE, NULL );	
	info.hReadEvent  = ::CreateEvent( NULL, TRUE, FALSE, NULL );	

	// test que
	for ( long noTests = 0; noTests < 10; noTests++ )
	{
		// set string index
		long index = noTests %3;
		info.index = index;

		// start read/write test
		if ( !testQue(info) )
		{
			MessageBox(NULL,"Failed test","TestQue",MB_OK);
		}
	}

	MessageBox(NULL,"Passed test","TestQue",MB_OK);

	return 0;
}

