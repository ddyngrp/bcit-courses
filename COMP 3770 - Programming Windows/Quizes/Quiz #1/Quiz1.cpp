


/*********************************************************************
Comp3770 Quiz#1 (Max 12 marks)

Submit your solution to the sharein Quiz folder. Your solution should
be placed in a file with the project file,.h and .cpp files. The folder
name should be "LastName FirstName Set" e.g. "Richards Dennis B"

THERE ARE 5 QUESTIONS - MAKE SURE YOU ANSWER THEM ALL

Q3-5 can be written as comments in your WinMain()

Q1. <2 mark>

Using the code provided (WndProc.h, WndProc.cpp, and Quiz1.cpp) without
moving code or deleting any code (you will need to add code) get the
program to compile, link and execute.

Q2. <7 marks>
Add a counter to your code from Q1 to keep track of the number
of windows created. The counter CANNOT BE GLOBAL OR STATIC. Hint:
use the "extra" memory space. In WndProc.cpp the "counter" value
is extracted and stored in variable "numW". For every window created
the counter should automatically increment (i.e. don't increament the counter
in WinMain())

The result should be like the example .exe. Note that all the windows
show the same result (3 in this case) because they all SHARE the
window counter.

The functions you need can be found online on msdn. Alternatively
the function names are very similar in name to the functions necessary
to have complete assignment1 - i.e. you likely can guess their names.

The display has been taken care of - you'll need to just add your
code  in WM_PAINT to get your counter value.

Again each time a window is CREATED the counter should be updated
as appropriate.

Create 3 windows to demonstrate your code functions correctly.

DO NOT DELETE ANY CODE PROVIDED!! DO NOT PUT ALL CODE INTO ONE FILE!!

Q3. Give the 2 tasks BeginPaint() method performs in WM_PAINT according to what was discussed in lecture (other
than returning a paint structure). <1 mark>
Q4. Why does the windows loop send the msg back to the O/S instead of sending the msg to the wndproc you created? <1 mark>
Q5. What is the difference between cbClsExtra and cbWndExra? <1 mark>
*********************************************************************/


int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, 
					PSTR szCMLine, int iCmdShow){
	static TCHAR szAppName[] = TEXT ("HelloApplication");
	HWND	hwnd;
	MSG		msg;
	WNDCLASS wndclass;

	wndclass.style		= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = HelloWndProc;
	wndclass.cbClsExtra	= 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance	= hInstance;
	wndclass.hIcon		= LoadIcon (NULL, IDI_APPLICATION);
	wndclass.hCursor	= LoadCursor (NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass (&wndclass)){
		MessageBox (NULL, TEXT ("This program requires Windows 95/98/NT"),
					szAppName, MB_ICONERROR);
		return 0;
	}
	hwnd = CreateWindow(szAppName,		
						TEXT("Hello World for Windows"), 
						WS_OVERLAPPEDWINDOW,	
						CW_USEDEFAULT,		
						CW_USEDEFAULT,		
						CW_USEDEFAULT,		
						CW_USEDEFAULT,		
						NULL,				
						NULL,				
						hInstance,			
						NULL);				
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	
	while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
