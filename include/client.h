#include <watcherlib.h>

struct conn_info_client {
    in_addr_t  _inet_addr;
    uint32_t inet_port;
    const char  * private_key;
    char * public_key;
    bool conn_status;
    int protocol;
    int socket_fd;
    int watcher_fd;
    struct sockaddr_in  server_address;
    struct sockaddr_in  client_address;
};


class Client {
    private:
      conn_info_client client_st;
    public:
      Client();
      int _connect(const char * inet_addr ,  uint32_t inet_port);
      ssize_t send_cmd(int * server_fd , void* msg);
      char * recv_packet(int socket_fd);
      int validate_key(const char * key , const char * c_key);
      const char * generate_key( char *pass);
};
