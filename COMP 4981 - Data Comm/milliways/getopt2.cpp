#include <iostream> 
#include <unistd.h>
using namespace std;

extern char *optarg;
extern int  optind, opterr;


int main (int argc, char *argv[])
{
        int ret;
        static char optstring[] = "a:b:c:";
        opterr = 0;

        while ((ret = getopt (argc, argv, optstring)) != -1)
        {
                switch (ret)
                {
                        case 'a':
                                cout << "Found option a; argument is: ";
				cout << optarg << endl;
                                break;
                        case 'b':
				cout << "Found option b; argument is: ";
				cout << optarg << endl;
                                break;
                        case 'c':
                                cout << "Found option c; argument is: ";
				cout << optarg << endl;
                                break;
                        case '?':
                                cout << "Found an option that was not in optstring";
				cout << endl;
                }
        }
        if (optind < argc) //make sure all the command line arguments have been processed
                cout << "Stopped at: " << argv[optind] << endl;
        return 0;
}
