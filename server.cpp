#include <server.h>
#include <iostream>

using namespace std;

/*
    Class Server
*/
Server::Server(){
    server_st.protocol = AF_INET;
    // const char * hash = crypt(key, hash_md5);
}
const char * Server::generate_key(char * pass){
    this->server_st.private_key = (const char *)pass;
    return this->server_st.private_key;
}


int Server::create_server(const char * _inet_addr , uint32_t  inet_port) {
    //ip address
    server_st._inet_addr = inet_addr(_inet_addr);
    //port to run on
    server_st.inet_port =  htons(inet_port);
    //set socket protocol

    //create socket
    int socket_fd = socket(server_st.protocol,SOCK_STREAM , 0);
    server_st.socket_fd = socket_fd;
    error_handler("- SOCK ERR ");

    memset(&server_st.server_address , 0 , sizeof(struct sockaddr_in));
    server_st.server_address.sin_port = server_st.inet_port;
    server_st.server_address.sin_family = server_st.protocol;
    server_st.server_address.sin_addr.s_addr = server_st._inet_addr;


    //bind socket to address
    int bind_fd =  bind(server_st.socket_fd, (struct sockaddr *) &server_st.server_address,
                sizeof( struct sockaddr_in));
    error_handler("- BIND ERR ");

    //listen to connect
    int listen_fd =  listen(server_st.socket_fd, 1);
    error_handler("- LISTEN ERR  ");
    server_st.conn_status = true;



    // close(socket_fd);
    return socket_fd;

}
char * Server::recv_packet(int accept_fd) {
    //read from buff
    char  *buff[64];
    ssize_t rfd = recv(accept_fd , &buff , sizeof(buff) , MSG_CMSG_CLOEXEC );
    error_handler("-    RECV ERR  ");
    if (rfd != -1)
        printf("+ RECV : %d bytes recv \n", rfd);
        printf("+ >> %s \n" , buff);
        this->send_packet(accept_fd , "WATCHER ACK");
    return *buff;
}


int Server::accept_conn(int socket_fd) {
    //accept incoming connection
    socklen_t socket_length = sizeof(server_st.client_address);
    cout << "+ SS : ACCPT " << endl;
    int accept_fd =  accept(server_st.socket_fd, (struct sockaddr* ) &server_st.client_address,
                   &socket_length);
    error_handler("- ACCEPT ERR  ");
    cout << "+ SS: CONN " << endl;
    struct in_addr client_addr_st = (in_addr) server_st.client_address.sin_addr.s_addr;
    cout << "+ CLIENT ADDR: "  << inet_ntoa(client_addr_st) << ":" << ntohs(server_st.client_address.sin_port) << endl;
   return accept_fd;
}

ssize_t Server::send_packet(int conn , const void * msg){
    ssize_t s_fd = send(conn , msg , 64,  MSG_CONFIRM);
    error_handler("- SOCKET SEND");
    return s_fd;
}
