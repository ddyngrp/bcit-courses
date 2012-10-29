
#include <commctrl.h>
#include <windows.h>
#include <mmsystem.h>

struct _Node{

	char* str;
	struct Node *hptr;

}Node;

//#define SCREENSIZE	
#define TYPESTART							200
#define IDSTART								100
#define	DATASTART							500
#define IDM_FILE							100
#define IDM_EXIT							101
#define IDM_ACTION							102
#define IDM_SCAN							103
#define IDM_STOP							104
#define IDM_CLMES							105
#define IDM_RESETCACHE						106
#define IDM_RESTART							107
#define IDM_CONFIG							108
#define IDM_HELP							109
#define IDM_ABOUT							110
#define IDC_MAIN_TOOL						111
#define IDB_STANDARD						112

#define ID_LISTBOX							130




struct Node *root;
struct Node *tracker;

void initializeToolBar(HWND hwnd);
void printTag(HWND hwnd, TCHAR* tag);
void printTitle(HWND hwnd);