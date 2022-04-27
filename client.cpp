#include <client.h>
#include <iostream>
using namespace std;

void get_time(){
  chrono::time_point<chrono::system_clock> d;
  d = chrono::system_clock::now();
  time_t date = chrono::system_clock::to_time_t(d);
  cout << ctime(&date) << endl;
}



/*
    Class Client
*/

Client::Client()  {
    client_st.protocol = AF_INET;
}


 int Client::_connect(const char * _inet_addr ,  uint32_t inet_port){
    int socket_fd = socket(client_st.protocol,SOCK_STREAM , 0);
    error_handler("- SOCKET ERR");
    client_st.client_address.sin_family = client_st.protocol;
    client_st.client_address.sin_addr.s_addr = inet_addr(_inet_addr);
    client_st.client_address.sin_port = htons(inet_port);
    int server_fd = connect(socket_fd , (struct sockaddr *) &client_st.client_address , (socklen_t)sizeof(client_st.client_address));
    error_handler("- CONNECT ERR  ");
    cout << "SERVER FD: " << server_fd << endl;
    return socket_fd;
 }

 char * Client::recv_packet(int server_fd) {
     //read from buff
    char  *buff[64];
    ssize_t rfd = read(server_fd , &buff , sizeof(buff));
    error_handler("-    READ ERR  ");
    if (rfd > 0)
        printf("+ RECV: %d bytes recv \n", rfd);
        printf("+ >> : %s \n" , buff) ;
        printf("%s", "+ TIME : ");
        get_time();
    return *buff;
 }
 ssize_t Client::send_cmd(int *server_fd , void * msg){
    ssize_t s_fd = send(*server_fd ,msg , 64,  MSG_CONFIRM);
    error_handler("- SOCKET SEND");
    return s_fd;
}
