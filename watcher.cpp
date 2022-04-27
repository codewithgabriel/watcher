//============================================================================
// Name        : watcher.cpp
// Author      : Gabriel
// Version     : 0.0.1
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//  Email      : olatoyeolaide@gmail.com
//============================================================================
#include <watcher.h>
#include <string>
#include <iostream>
#include <exception>



using namespace std;
//segment .data

//segment .bss
int _inotify_fd , _watcher_fd , _socket_fd;

static void catch_signal(int sig) {
  (void)inotify_rm_watch(_inotify_fd, _watcher_fd);
  (void) close(_inotify_fd);
  (void) close(_socket_fd);

  cout << "+ inotify closed" << endl;
  error_handler("- ERROR: catch_signal");
}



int   Watcher::create_server(const char * ip_addr , uint32_t port) {
      watcher_server.server_st.socket_fd = watcher_server.create_server(ip_addr , port);
      _socket_fd =   watcher_server.server_st.socket_fd;
      return watcher_server.server_st.socket_fd;
}
int Watcher::set_watch (int inotify_fd , const char * pathname , unsigned int flags) {
  //watcher_fd
  watcher_server.server_st.inotify_fd = inotify_fd;
  watcher_server.server_st.pathname = pathname;
  watcher_server.server_st.flags = flags;
  watcher_server.server_st.watcher_fd = inotify_add_watch(inotify_fd, pathname ,  flags);
  _inotify_fd = inotify_fd; _watcher_fd = watcher_server.server_st.watcher_fd;
  return watcher_server.server_st.watcher_fd;
}

int   Watcher::keep_alive(int socket_fd){
  //accept incoming new connection and read incoming packet
  watcher_server.server_st.accept_fd = watcher_server.accept_conn(socket_fd);

  while(watcher_server.server_st.conn_status){
    sleep(1);
    //recv incoming packets
      watcher_server.recv_packet(watcher_server.server_st.accept_fd);
      //reply to incoming packets
      watcher_server.send_packet(watcher_server.server_st.accept_fd , "WATCHER SERVER UP");
      //keep watching the for file events
      for (;;)
        int watcher_fd = event_handler( watcher_server.server_st.inotify_fd , watcher_server.server_st.pathname,watcher_server.server_st.flags);
  		   // cout << "+	WATCHER FD: " << watcher_fd << endl;
         // close(watcher_server.server_st.accept_fd);
  }
  close(socket_fd);
  return 0;
}
int   Watcher::get_conn_info() {
  cout << "+ ip address :" << watcher_server.server_st._inet_addr << endl;
  cout << "+ watcher fd : " << watcher_server.server_st.watcher_fd << endl;
  return 0;
}

//help_msg
void Watcher::help() {
    cout << "Usage: ./watcher --watcher[-server , -client] 127.0.0.1 dirname" << endl;
    cout << "--help     display help" << endl;
    cout << "--watcher-server     watcher as server" << endl;
    cout << "--watcher-client     watcher as client" << endl;
    exit(0);
}
//getargv
const char * Watcher::get_argv(int argc , char * argv[]) {
    if (argc == 0)
        help();
    const char * arg;
    for (int i = 0; i < argc ; i++) {
        arg = argv[i];
    }
    return (arg);
}
//parse argv
bool Watcher::parse_argv(int argc , char * argv[], const char* item) {
    if (argc == 0)
        help();
    bool status  = false;
    string arg;
    for (int i = 0; i < argc ; i++) {
        arg = (string)argv[i];
        if (item == arg)
            status = true;
    }

    return (status);
}
//process all argv base on conditions
int Watcher::process_argv (int argc , char * argv[] , const char * item){
  if (item == "--help" && parse_argv(argc , argv , item) == 1) {
      help();
      return 0;
  }else if (item == "--watcher-server" && parse_argv(argc , argv , item) == 1 ) {
    //./watcher --watcher-server 127.0.0.1 dirname
    const char *positional_arg = argv[1];
    const char * ip_addr = argv[2];
    const char  * pathname = argv[3];
    //generate server key
    // char *pass = getpass("+ Enter new passphrase: ");
    // const char * key = watcher_server.generate_key(pass);
    // cout << "+ PUBKEY :" << key << endl;
    // //inotify_fd
    int inotify_fd = inotify_init();
  	//print error message and exit program
  	error_handler("intify_init");
  	cout << "+ watcher init" << endl;
  	cout << "+ process id : " << PID << endl;
  	cout << "+ watching : " << pathname << endl;
  	cout << "+ inotify id : " << inotify_fd << endl;
    //create server and keep it alive
    this->set_watch(inotify_fd , pathname , IN_MODIFY | IN_ACCESS | IN_CREATE | IN_DELETE | IN_OPEN);
    cout << "+ watcher state : SET" << endl;
    int socket_fd = this->create_server(ip_addr , INET_DEFAULT_PORT);
    _socket_fd = socket_fd;
    this->keep_alive(socket_fd);
  }else if(item == "--watcher-client" && parse_argv(argc , argv , item) == 1){
      /* ./watcher --watcher-client 127.0.0.1 dirname */
      Client _client;
      int server_fd = _client._connect(argv[2] , INET_DEFAULT_PORT);
      cout << "+ CONNECTED : " << argv[2] << endl;
      cout << "+ SERVER FD : "  << server_fd << endl;
      cout << "(enter key)>> ";
      char * server_key[64];
      scanf("%s", &server_key);
      _client.send_cmd(&server_fd , &server_key);
      while(true) {
        sleep(1);
        _client.recv_packet(server_fd);
      }


  }
    return 0;
}

void Watcher::get_time(){
  chrono::time_point<chrono::system_clock> d;
  d = chrono::system_clock::now();
  time_t date = chrono::system_clock::to_time_t(d);
  cout << ctime(&date) << endl;
}

int Watcher::event_handler(int inotify_fd ,const char *pathname , unsigned int flags) {
  int i =0;
	//length
	int length;
  //buffer
  char buff[BUFFER_LEN];

  //handle signal
  struct sigaction  sig_action;
  sigemptyset(&sig_action.sa_mask);
  sig_action.sa_flags = 0;
  sig_action.sa_handler = catch_signal;
  int sig =  sigaction(SIGINT , &sig_action ,NULL);
  error_handler("- ERROR: signal");
  //read events into buffer
  cout << "+ SS : WFF EVT" << endl;
	length = read(inotify_fd , buff , BUFFER_LEN);
  //loop through all events
	while( i < length) {
		struct inotify_event * i_event =  (struct inotify_event*) &buff[i];
		//i_event
		if (i_event->mask & IN_ACCESS) {
      char event_[64] = "EVENT FILE  ACCESSED => ";
      char *msg = strcat( event_ ,  i_event->name  ) ;
      cout << msg << endl;
      watcher_server.send_packet(watcher_server.server_st.accept_fd , msg);

		}
		if (i_event->mask & IN_MODIFY) {
      char event_[64] = "EVENT FILE  MODIFIED => ";
      char *msg = strcat( event_ ,  i_event->name  ) ;
      cout << msg << endl;


      watcher_server.send_packet(watcher_server.server_st.accept_fd , msg);
		}
		if (i_event->mask & IN_CREATE) {
      char event_[64] = "EVENT FILE  CREATED => ";
      char *msg = strcat( event_ ,  i_event->name  ) ;
      cout << msg << endl;


      watcher_server.send_packet(watcher_server.server_st.accept_fd , msg);
		}
    if (i_event->mask & IN_OPEN) {
      char event_[26] = "EVENT FILE  OPENED => ";
      char *msg = strcat( event_ ,  i_event->name  ) ;
      cout << msg << endl;

      watcher_server.send_packet(watcher_server.server_st.accept_fd , msg);

    }
    if (i_event->mask & IN_DELETE) {
        char event_[26] = "EVENT FILE DELETED => ";
        char *msg = strcat( event_ ,  i_event->name  ) ;
        cout << msg << endl;

        // cout << del_msg << endl;
        watcher_server.send_packet(watcher_server.server_st.accept_fd , msg);

        // watcher_server.send_packet(watcher_server.server_st.accept_fd , "DELETED" );

    }
		i+=EVENT_SIZE + i_event->len;

	}
	  error_handler("- ERROR: event_handler");
    return 0;
}
