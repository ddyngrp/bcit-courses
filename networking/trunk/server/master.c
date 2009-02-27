/* Master control - Currently this only contains the main() function,
   but in the future it likely deal with more, such as the interface
   functions between networking and game logic.
*/

#include "server.h"

int main(void) { /* Starting a server takes no arguments */
	start_server(); /* Create a way to stop the server */
	return 1;
}
