#define PLAYBACK_BUFFER_SIZE   	327680L
#define DATABLOCK_SIZE          	32768L
#define MAX_BUFFERS                	 2  // double buffer
#define MSG_LEN                   		128

static WAVEHDR* wh[MAX_BUFFERS];

// temp buffer for this example
//.............................

static VOID*    pPlaybackBuffer;  
static DWORD    nPlaybackBufferPos = 0L;  // position in playback buffer  
static DWORD    nPlaybackBufferLen = 0L;  // total data in playback buffer

VOID AllocBuffers ()
{
   int i;

   // allocate two WAVEHDR buffer blocks
	//...................................

	for (i = 0; i < MAX_BUFFERS; i++)                                        
	{                                                               
	   wh[i] = HeapAlloc( GetProcessHeap(),                         
	                      HEAP_ZERO_MEMORY,                         
	                      sizeof(WAVEHDR) );                        
	   if (wh[i])                                                  
	   {                                                            
	       wh[i]->lpData = HeapAlloc( GetProcessHeap(),             
	                                  HEAP_ZERO_MEMORY,             
	                                  DATABLOCK_SIZE);                       
	       wh[i]->dwBufferLength = DATABLOCK_SIZE;
	   }
	}

   // allocate playback buffer - enough space to hold
   // ten data buffer blocks of waveform sound data
   //................................................

   pPlaybackBuffer = HeapAlloc( GetProcessHeap(),
                                HEAP_ZERO_MEMORY,
                                PLAYBACK_BUFFER_SIZE);
} 

/*****************************************************************************
*  CleanUpBuffers
*
*
*
******************************************************************************/

VOID CleanUpBuffers()
{
   int i;

   // free the WAVEHDR buffer blocks
	//...............................

 	for (i = 0; i < MAX_BUFFERS; i++)                                        
	{
     if (wh[i] != NULL)
     {
	      HeapFree(GetProcessHeap(), 0, wh[i]->lpData);                 
	      HeapFree(GetProcessHeap(), 0, wh[i]);
         wh[i] = NULL;
     }
	}
	
	// free playback buffer
	//.....................
	
	HeapFree(GetProcessHeap(), 0, pPlaybackBuffer);
}
