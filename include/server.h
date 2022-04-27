#include <watcherlib.h>

/* ‘GNU's Not Unix’ hashed using SHA-256, MD5, and DES. */
static const char hash_sha[] ="$5$DQ2z5NHf1jNJnChB$kV3ZTR0aUaosujPhLzR84Llo3BsspNSe4/tsp7VoEn6";
static const char hash_md5[] = "$1$A3TxDv41$rtXVTUXl2LkeSV0UU5xxs1";
static const char hash_des[] = "FgkTuF98w5DaI";

#define INET_DEFAULT_PORT 8989u

struct conn_info_server {
    in_addr_t  _inet_addr;
    uint32_t inet_port;
    const char  * private_key;
    char * public_key;
    bool conn_status;
    int protocol;
    int socket_fd;
    int accept_fd;
    int watcher_fd;
    int inotify_fd;
    const char *  pathname;
    unsigned int flags;
    struct sockaddr_in  server_address;
    struct sockaddr_in  client_address;
};

class Server {
  public:
    conn_info_server server_st;
    Server();
    int create_server(const char * inet_addr ,  uint32_t inet_port);
    ssize_t send_packet(int conn , const void * msg);
    int accept_conn(int socket_fd);
    char * recv_packet(int accept_fd);
    int command_handler(const char * cmd);
    int validate_key(const char * key , const char * c_key);
    const char * generate_key( char *pass);
};




//
// template<class Server , class Client>
//   Server init(Server _server , Client _client);
//   Server connect(Server _server , Client _client);
//   Server disconnect(Server _server , Client _client);
//   Server generate_key(Server _server , Client _client);
