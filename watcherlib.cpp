#include <watcherlib.h>

//check for  errno status and exist the program
void error_handler(const char * err_msg) {
	if (errno) {
		perror(err_msg);
		exit(EXIT_FAILURE);
	}
}
