#include "server.h"

Server::Server()
{

}

Server::~Server()
{
    for(size_t i = 0; i < threads.size(); ++i)
    {
        pthread_join(threads[i],nullptr);
    }
    close(_socket);
}

void Server::server_init()
{
    std::chrono::milliseconds dude(100);

    _socket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(_socket == -1)
    {
        perror("Scok trable");
        exit(-1);
    }

    fcntl(_socket,F_SETFL,O_NONBLOCK);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1488);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    int bind_status = bind(_socket,(sockaddr*)&server_addr,sizeof(server_addr));

    if(bind_status < 0)
    {
        perror("Bind trable");
        exit(-1);
    }

    do
    {
     bool accept_connection;
     sockaddr_in soc_cli;
     soc_cli.sin_family = AF_INET;
     soc_cli.sin_port = htons(1488);
     socklen_t len_struct = sizeof(soc_cli);
     int recv_status = recvfrom(_socket,&accept_connection,sizeof(bool),0,(sockaddr*)&soc_cli,&len_struct);
     if(recv_status != -1)
     {
         clients.push_back(soc_cli);
         threads.resize(threads.size() + 1);
         pthread_create(&threads[threads.size() - 1], 0 , work_with_client , static_cast<void*>(&clients[clients.size() - 1]) );
     }
     std::this_thread::sleep_for(dude);
    }while(state);
}

void *Server::work_with_client(void *arg)
{

}
