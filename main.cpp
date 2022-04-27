//============================================================================
// Name        : watcher.cpp
// Author      : Gabriel
// Version     : 0.0.1
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//  Email      : olatoyeolaide@gmail.com
//============================================================================

#include <iostream>
#include <watcher.h>
#include <string>

using namespace std;
//segment .data

//segment .bss
Watcher watcher;

//segment .text
//main:
int main(int argc , char * argv[] , char * env[]) {
  //handle --help argv
  watcher.process_argv(argc , argv , "--help");
  watcher.process_argv(argc , argv , "--watcher-server");
  watcher.process_argv(argc , argv , "--watcher-client");
  watcher.get_time();
	return 0;
}
