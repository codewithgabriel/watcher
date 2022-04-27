#include <watcherlib.h>
#include <server.h>
#include <client.h>


#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUFFER_LEN (1024 * (EVENT_SIZE + 16))
#define PID (getpid())


// static void  catch_signal(int sig);


class Watcher {
public:
    Server watcher_server;
    int   create_server(const char * ip_addr , uint32_t port);
    int   set_watch(int inotify_fd  , const char *pathname , unsigned int flags);
    int   keep_alive(int socket_fd);
    int   get_conn_info();
    void  help ();
    int   event_handler(int inotify_fd ,const char *f_path , unsigned int flags);
    bool  parse_argv(int argc , char *argv[] , const char * item);
    int   process_argv(int argc, char * argv[] , const char * item);
    const char * get_argv(int argc , char * argv[]);
    void  get_time();
};
