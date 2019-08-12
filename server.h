#ifndef SERVER_H
#define SERVER_H
#include "sys/types.h"
#include "sys/socket.h"
#include "arpa/inet.h"
#include "pthread.h"
#include "unistd.h"
#include "vector"
#include "chrono"
#include "thread"
#include "fcntl.h"

class Server
{
private:
    bool pause = false;
    int _socket;
    sockaddr_in server_addr;
    bool state = true;
    std::vector<pthread_t> threads;
    std::vector<sockaddr_in> clients;
public:

    Server();
    ~Server();
    void server_init();
    static void* work_with_client(void* arg);
};

#endif // SERVER_H
