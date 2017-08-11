#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/epoll.h>
#include<string.h>
#include<arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <arpa/inet.h>
using namespace std;

const unsigned short SER_PORT = 8000;
const unsigned int   MAX_EVENTS = 1024;

void setNonBlocking(int sockfd)
{
    int opts;
    opts = fcntl(sockfd, F_GETFL);
    opts |= O_NONBLOCK;
    if(fcntl(sockfd, F_SETFL, opts) == -1)
    {
        cerr<<"fcntl error"<<endl;
    }
}

int ser_socket;
void signalfun(int sig)
{
    if(sig == SIGINT)
    {
        close(ser_socket);
        cout<<"close socketfd"<<endl;
    }
}
int main()
{
    struct sockaddr_in ser_addr, cli_addr;
    int epollfd, cli_socket, nfds;
    struct epoll_event ev, events[MAX_EVENTS];
    socklen_t cliaddr_len;
    char buf[1024];
    char ip_addr[16];
    memset(buf, 0, sizeof(buf));
    memset(ip_addr, 0, sizeof(ip_addr));
    signal(SIGINT, signalfun);
    ser_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(ser_socket == -1)
    {
        cerr<<"socket error"<<endl;
        return -1;
    }
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port   = htons(SER_PORT);
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(ser_socket,(struct sockaddr*)&ser_addr, sizeof(ser_addr)) == -1)
    {
        cerr<<"bind error"<<endl;
        return -1;
    }
    if(listen(ser_socket, 10) == -1)
    {
        cerr<<"listen error"<<endl;
        return -1;
    }
    epollfd = epoll_create(MAX_EVENTS);
    if(epollfd == -1)
    {
        cerr<<"epoll_create error"<<endl;
        return -1;
    }
    ev.events = EPOLLIN;
    ev.data.fd = ser_socket;
    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, ser_socket, &ev) == -1)
    {
        cerr<<"epoll_ctl error"<<endl;
        return -1;
    }
    while(1)
    {
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if(nfds == -1)
        {
            cerr<<"epoll_wait error"<<endl;
            return -1;
        }
        for(int n = 0; n < nfds; ++n)
        {
            if(events[n].data.fd == ser_socket)
            {
                cli_socket = accept(ser_socket, (struct sockaddr*)&cli_addr, &cliaddr_len);
                if(cli_socket == -1)
                {
                    cerr<<"accept error"<<endl;
                    return -1;
                }
                if(inet_ntop(AF_INET, &cli_addr.sin_addr.s_addr, ip_addr, sizeof(ip_addr)) != NULL)
                {
                    cout<<"client ip:"<< ip_addr <<endl;
                }
                else {
                   cerr<<"inet_ntop error"<<endl; 
                }
                setNonBlocking(cli_socket);
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = cli_socket;
                if(epoll_ctl(epollfd, EPOLL_CTL_ADD, cli_socket, &ev) == -1)
                {
                    cerr<<"epoll_ctl error"<<endl;
                    return -1;
                }
            }
            else if(events[n].events & EPOLLIN)
            {
                int socketfd = events[n].data.fd;
                recv(socketfd, buf, sizeof(buf), 0);
                send(socketfd, buf,sizeof(buf), 0);
                memset(buf, 0, sizeof(buf));
                close(socketfd);
            }
        }
    }
    close(ser_socket);
    return 0;
}
