#include <stdio.h>
#include <string.h>

// Function prototypes
void foo (const char* );
void bar (void);


int main (int argc, char* argv[])
{
	printf ("Address of foo = %p\n", foo);
	printf ("Address of bar = %p\n", bar);
	foo (argv[1]);
	return 0;
}

void foo (const char* input)
{
	char buf[10];

	printf ("Stack image is: \n%p\n%p\n%p\n%p\n%p\n%p\n\n");

	// Feed the user input into the buffer with no bounds checking
	strcpy (buf, input);
	printf ("%s\n", buf);

	printf ("New stack image is: \n%p\n%p\n%p\n%p\n%p\n%p\n\n");
}

void bar (void)
{
	printf ("In function bar\n");
}
