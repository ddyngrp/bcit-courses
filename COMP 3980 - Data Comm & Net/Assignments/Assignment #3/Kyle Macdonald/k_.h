#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>


LRESULT CALLBACK HelloWndProc (HWND, UINT, WPARAM, LPARAM);
void found_version(int type, int major, int minor);
void insertData(char string[255]);
void found_tag_14443a(int cid, int pupi, size_t length);
void found_tag_14443b(int cid, int pupi, size_t length);
void found_tag_14434(int id, char* data, size_t length);
void found_tag_15693(int dataFormatID, int invFlag, int uniqueID, size_t length);
void found_tag_tagit(int id, int data, size_t length);
void found_tag_lfdst(int merchID, int tagNum, size_t length);
void found_tag_apollo(int id, char* data, size_t length);
void found_tag_none();
int getLengthOfInt(int d);
int listSize();
struct node getList();


static int tagCounter = 0;
static int _14443aCounter = 0;
static int _14443bCounter = 0;
static int _14434Counter = 0;
static int _15693Counter = 0;
static int _tagitCounter = 0;
static int _lfdstCounter = 0;
static int _apolloCounter = 0;
static int _noTagCounter = 0;

struct node {
	char *str;
	struct node *next;
	struct node *prev;
};

typedef struct node item;
struct node *curr;
struct node *head;
struct node *tail;
struct node *Traverse;
