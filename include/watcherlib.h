#include <unistd.h>
#include <ctype.h>
#include <cstdlib>
#include <sys/inotify.h>
#include <errno.h>
#include <cstring>
#include <cstdbool>
#include <csignal>
#include <ctime>
#include <cstdio>
#include <sys/socket.h>
#include <crypt.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <chrono>


void error_handler(const char * err_msg);
