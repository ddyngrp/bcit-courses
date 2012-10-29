#include "k_.h"


int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, 
					PSTR szCMLine, int iCmdShow){
	static TCHAR szAppName[] = TEXT ("HelloApplication");
	HWND	hwnd; 
	MSG		msg;
	WNDCLASS wndclass;

	wndclass.style		= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = HelloWndProc;	// Sets the window procedure for this window class to WndProc
	wndclass.cbClsExtra	= 0;	// Used to reverse space in the class structure
	wndclass.cbWndExtra = 0;	// Used to reverse space in the window structure
	wndclass.hInstance	= hInstance;	// the instance handle of the program
	wndclass.hIcon		= LoadIcon (NULL, IDI_APPLICATION); // Loads an icon used for all the windows created based on this window class
	wndclass.hCursor	= LoadCursor (NULL, IDC_ARROW);     // Loads a cursor used for all the windows created based on this window class
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH); // Obtains a graphic object (i.e. brush) for painting 
	wndclass.lpszMenuName = NULL; // specifies window class menu (HELLOWIN has no application menu)
	wndclass.lpszClassName = szAppName; // Assigns the class name.. (assigned in szAppName)

	if (!RegisterClass (&wndclass)){  // Registers a window class for the programs window.
		MessageBox (NULL, TEXT ("This program requires Windows 95/98/NT"), //Display's a Message Box
					szAppName, MB_ICONERROR); //
		return 0;
	}

	hwnd = CreateWindow(szAppName,		// Creates a window based on a window class
						TEXT("Hello World for Windows"),    // window caption
						WS_OVERLAPPEDWINDOW,				// window style
						CW_USEDEFAULT,						// initial x position
						CW_USEDEFAULT,						// initial y position
						CW_USEDEFAULT,						// initial x size
						CW_USEDEFAULT,						// initial y size
						NULL,								// parent window handle
						NULL,								// window menu handle
						hInstance,							// program instance hand
						NULL);								// creating parameters
	ShowWindow(hwnd, iCmdShow);		// Shows the window on the screen
	UpdateWindow(hwnd);				// Directs the window to paint itselfw

	while (GetMessage(&msg, NULL, 0, 0)){	// Obtains the message from the message queue
		TranslateMessage(&msg);				// Translates some keyboard message
		DispatchMessage(&msg);				// Sends a message to a window procedure
	}

	return (int) msg.wParam;
}

// hwnd - used to determine which window hwnd pointed to before deciding on an action
// message - The actual message identifier that WndProc will be handling
// wParam and lParam - Extensions of the message parameter. Used to give more information
//						and point to specifics that message cannot on its own
LRESULT CALLBACK HelloWndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	HDC		hdc;
	PAINTSTRUCT ps;
	RECT	rect;

	switch (message){
		case WM_CREATE:
			head = NULL;
			return 0;

		case WM_PAINT: 
			hdc = BeginPaint(hwnd, &ps); // First thing it does, it validates the window	// Initiates the beinning of window painting
										 // Then returns device context.

			GetClientRect(hwnd, &rect); // Obtains the dimensions of the window's client area (drawing area)

			DrawText(hdc, TEXT("Hello, Windows"), -1, &rect, // Displays a text string
					DT_SINGLELINE | DT_CENTER | DT_VCENTER);

			EndPaint(hwnd, &ps);	// Ends window painting
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);		// Inserts a "quit" message into the message queue
			return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);	// Performs default processing of messages
}


int getLengthOfInt(int d) {
	
	if(d > 1000000000000000 || d < -1000000000000000) {
		return 16;
	} else if (d > 100000000000000 || d < -100000000000000) {
		return 15;
	} else if( d > 10000000000000 || d < -10000000000000) {
		return 14;
	} else if( d > 1000000000000 || d < -1000000000000) {
		return 13;
	} else if( d > 100000000000 || d < -100000000000) {
		return 12;
	} else if( d > 10000000000 || d < -10000000000) {
		return 11;
	} else if( d > 1000000000 || d < -1000000000) {
		return 10;
	} else if( d >100000000 || d < -100000000) {
		return 9;
	} else if(d > 10000000 || d < -10000000) {
		return 8;
	} else if(d > 1000000 || d < -1000000) {
		return 7;
	} else if(d > 100000 || d < -100000) {
		return 6;
	} else if( d > 10000 || d < -10000) {
		return 5;
	} else if( d > 1000 || d < -1000) {
		return 4;
	} else if( d > 100 || d < -100) {
		return 3;
	} else if( d > 10 || d < -10) {
		return 2;
	} else 
		return 1;
	
}


void found_tag_14443a(int cid, int pupi, size_t length) {
	char buffer1[16];
	char buffer2[16];
	char string[255];
	
	_itoa_s(cid, buffer1, 16, 10);
	_itoa_s(pupi, buffer2, 16, 10);
	
	
	strcpy_s(string, 255, "Entity: 14443a");
	strcat_s(string, 255, " | CID: ");
	strcat_s(string, 16, buffer1);
	strcat_s(string, 255, " | PUPI: ");
	strcat_s(string, 16, buffer2);

	insertData(string);
	_14443aCounter++;
}

void found_tag_14443b(int cid, int pupi, size_t length) {
	char buffer1[16];
	char buffer2[16];
	char string[255];
	
	_itoa_s(cid, buffer1, 16, 10);
	_itoa_s(pupi, buffer2, 16, 10);
	
	curr = (item *)malloc(sizeof(item));

	strcpy_s(string, 255, "Entity: 14443b");
	strcat_s(string, 255, " | CID: ");
	strcat_s(string, 16, buffer1);
	strcat_s(string, 255, " | PUPI: ");
	strcat_s(string, 16, buffer2);

	curr->str = string;
	curr->next = head;
	head = curr;
	_14443bCounter++;
}

void found_tag_14434(int id, char* data, size_t length) {
	char buffer1[16];
	char string[255];
	
	_itoa_s(id, buffer1, 16, 10);
	
	strcpy_s(string, 255, "Entity: 14434");
	strcat_s(string, 255, " | ID: ");
	strcat_s(string, 16, buffer1);
	strcat_s(string, 255, " | Data: ");
	strcat_s(string, 255, data);

	insertData(string);
	_14434Counter++;
}

void found_tag_15693(int uniqueID, int dataFormatID, int invFlag, size_t length) {
	char buffer1[16];
	char buffer2[16];
	char buffer3[16];
	char string[255];
	
	_itoa_s(uniqueID, buffer1, 16, 10);
	_itoa_s(dataFormatID, buffer2, 16, 10);
	_itoa_s(invFlag, buffer3, 16, 10);

	strcpy_s(string, 255, "Entity: 15693");
	strcat_s(string, 255, " | Unique ID: ");
	strcat_s(string, 16, buffer1);
	strcat_s(string, 255, " | Inventory Flag: ");
	strcat_s(string, 16, buffer2);
	strcat_s(string, 255, " | Data Format ID: ");
	strcat_s(string, 16, buffer3);

	insertData(string);
	_15693Counter++;
}

void found_tag_tagit(int id, int data, size_t length) {
	char buffer1[16];
	char buffer2[16];
	char string[255];
	
	_itoa_s(id, buffer1, 16, 10);
	_itoa_s(data, buffer2, 16, 10);

	strcpy_s(string, 255, "Entity: Tag It");
	strcat_s(string, 255, " | ID: ");
	strcat_s(string, 16, buffer1);
	strcat_s(string, 255, " | Data: ");
	strcat_s(string, 16, buffer2);

	insertData(string);
	_tagitCounter++;
}

void found_tag_lfdst(int merchID, int tagNum, size_t length) {
	char buffer1[16];
	char buffer2[16];
	char string[255];
	
	_itoa_s(merchID, buffer1, 16, 10);
	_itoa_s(tagNum, buffer2, 16, 10);
	
	strcpy_s(string, 255, "Entity: LF DST");
	strcat_s(string, 255, " | MID: ");
	strcat_s(string, 16, buffer1);
	strcat_s(string, 255, "| Tag Number");
	strcat_s(string, 16, buffer2);

	insertData(string);
	_lfdstCounter++;
}

void found_tag_apollo(int id, char* data, size_t length) {
	char buffer1[16];
	char string[255];
	
	_itoa_s(id, buffer1, 16, 10);

	strcpy_s(string, 255, "Entity: Apollo");
	strcat_s(string, 255, " | ID: ");
	strcat_s(string, 16, buffer1);
	strcat_s(string, 255, "| Data: ");
	strcat_s(string, 16, data);

	insertData(string);
	_apolloCounter++;
}

void found_version(int type, int major, int minor) {

}

void found_tag_none() {
	_noTagCounter++;
}

void insertData(char string[255]) {
	curr = (item *)malloc(sizeof(item));
	curr->str = string;

	if(head==NULL) {  /* list is empty */
		head = curr;
		curr->prev = NULL;
	} else {
		tail->next = curr;
		curr->prev = tail;
	}

	tail = curr;
	curr->next = NULL;

	tagCounter++;
}

int listSize() {
	int count=0;
	for(curr = head; curr!=NULL; curr = curr->next) {
		count++;
	}
	return count;
}

struct node getList() {
	return *head;
}

/*
// accessing through the list

for(curr = head; curr!=NULL; curr = curr->next) {
	ouput(curr->str);
}

*/