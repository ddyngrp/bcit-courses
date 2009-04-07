#include "win_main.h"
extern HWAVEOUT hwo;
static WAVEHDR songData;
static HANDLE hFile;
static DWORD bytesRead;

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	clnt_recv_tcp
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Jaymz Boilard
--	PROGRAMMER:	Jaymz Boilard
-- 
--	INTERFACE:	void clnt_recv_tcp(char buf[])
-- 
--	RETURNS:	void
-- 
--	NOTES:	Called when the client receives a tcp message asynchronously.
---------------------------------------------------------------------------------------*/
void clnt_recv_tcp(char buf[])
{
    WAVEFORMATEX wavFmt;  //format of the music

    if(strncmp("fmt", buf, 3) == 0)
    {
        memcpy(&wavFmt, buf+3, sizeof(wavFmt)); //get the format from server
        waveOutOpen(&hwo, WAVE_MAPPER, &wavFmt, 0, NULL, CALLBACK_NULL); //open the playing device
        waveOutPrepareHeader(hwo, &songData, sizeof(songData));
        //initialize UDP socket
        //send(tcpFd, "ready", 6, 0);
    }
}


/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	clnt_recv_udp
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Jaymz Boilard
--	PROGRAMMER:	Jaymz Boilard
-- 
--	INTERFACE:	void clnt_recv_udp(char buf[])
-- 
--	RETURNS:	void
-- 
--	NOTES:	Called when the client receives a udp message asynchronously.
--          Will be spawned as a new thread from the actual async receive part
---------------------------------------------------------------------------------------*/
void clnt_recv_udp(char buf[])
{
    memcpy(songData.lpData, buf, sizeof(buf));
    songData.dwBufferLength = MAXBUFSIZE;
    songData.dwBytesRecorded = sizeof(buf);
    waveOutWrite(hwo, &songData, sizeof(songData));
}

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	serv_broadcast
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Jaymz Boilard
--	PROGRAMMER:	Jaymz Boilard
-- 
--	INTERFACE:	serv_broadcast(char fileName[80])
-- 
--	RETURNS:	void
-- 
--	NOTES:	Called when the user on the server's side presses the broadcast
--          button.  All we do here is open the file and extract the WAVEFORMATEX
--          structure from the beginning of it.  Then we send it to the client and
--          wait until the client responds with a ready message.
---------------------------------------------------------------------------------------*/
void serv_broadcast(char fileName[80])
{
    char outBuf[MAXBUFSIZE];
    WAVEFORMATEX wavFmt;

    if(hFile = CreateFile(fileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL))
    {
        /* Skip unecessary stuff */
        SetFilePointer(hFile, 12, NULL, FILE_CURRENT);
        // ^ skip past the "fmt" as well?
        ReadFile(hFile, &wavFmt, sizeof(wavFmt), &bytesRead, NULL);
        
        memcpy(outBuf, &wavFmt, sizeof(wavFmt));
        //send(sockfd, outBuf, sizeof(outBuf), 0);
        /* Loop skips to the data section */
    }
    //else: error msg
}

/*--------------------------------------------------------------------------------------- 
--	FUNCTION:	serv_broadcast
-- 
--	REVISIONS:	
-- 
--	DESIGNER:	Jaymz Boilard
--	PROGRAMMER:	Jaymz Boilard
-- 
--	INTERFACE:	serv_broadcast(char fileName[80])
-- 
--	RETURNS:	void
-- 
--	NOTES:	Called when the server receives a TCP message from the client.
--          it checks the type of message and processes it accordingly
--          "ready" message - reads the data portion of the file and sends
--                            it via UDP
---------------------------------------------------------------------------------------*/
void serv_recv_tcp(char buf[])
{
    char outBuf[MAXBUFSIZE];
    if(strcmp(buf, "ready") == 0)
    {
        //initialize UDP function
        SetFilePointer(hFile, bytesRead + 12, NULL, FILE_CURRENT);
        //we only get this msg if we've already sent the header, therefore we know that the file is open
            //may need to set +12 to +15
        do
        {
            ReadFile(hFile, outBuf, sizeof(outBuf), &bytesRead, NULL);
            //send(udp_sockfd, outBuf, sizeof(bytesRead), 0);
        }
        while(bytesRead > 0);
    }
}
