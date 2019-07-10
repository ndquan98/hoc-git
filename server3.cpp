#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <string.h>
#include <netdb.h>
#include <poll.h>

#define PORTNO 3251
#define MAX_CLIENTS 10
using namespace std;

int main(int argc, char **argv)
{
    //Create Server socket
    sockaddr_in serv;
    int serv_len, cli_len;
    int serv_sfd, cli_sfd;
    int valread;
    char buffer[256];
    serv_sfd = socket(AF_INET,SOCK_STREAM,0);
    if(serv_sfd <0)
    {
        cerr << "<Error> Create Server Socket";
        close(serv_sfd);
        exit(EXIT_FAILURE);
    }
    //Init Server socket
    serv.sin_family=AF_INET;
    serv.sin_addr.s_addr=INADDR_ANY;
    serv.sin_port=htons(PORTNO);
    serv_len=sizeof(serv);
    //Set Server accept all connection
    int opt=1;
    if(setsockopt(serv_sfd,SOL_SOCKET,SO_REUSEADDR,(char*)&opt,sizeof(&opt))<0)
    {
        cerr << "<Error> Set Sock Opt";
        close(serv_sfd);
        exit(EXIT_FAILURE);
    }
    //Set Bind Server
    if(bind(serv_sfd,(sockaddr*)&serv,serv_len)<0)
    {
        cerr << "<Error> Bind Sock Server";
        close(serv_sfd);
        exit(EXIT_FAILURE);
    }
    //Set Listen
    if(listen(serv_sfd,3)<0)
    {
        cerr << "<Error> Listen Server";
        close(serv_sfd);
        exit(EXIT_FAILURE);
    }
    /*-----------I/O Multi---------- */
    pollfd *clients;
    if (clients == NULL)
    {
        cerr << "<Error> I/O Multi with pollfd";
        close(serv_sfd);
        exit(EXIT_FAILURE);
    }
    clients=new pollfd[MAX_CLIENTS];
    clients[0].fd=serv_sfd;         
    clients[0].events=POLLRDNORM;
    int clis_max=0;
    int clis_ready;

    //Init slot
    for(int i=1;i<MAX_CLIENTS;i++)
        clients[i].fd = -1; //-1 means available entry that can add new connection from client
    //Use poll for accept connect
    while(1)
    {
        int i;
        clis_ready=poll(clients,clis_max+1,-1); 
        if(clients[0].revents & POLLRDNORM) //mean new client connection
        {
            cli_sfd=accept(serv_sfd,(sockaddr*)&serv,(socklen_t*)&serv);
        }
        for(i=1;i<MAX_CLIENTS;i++) //Save desciptor of new client
        {
            if(clients[i].fd == -1)
                clients[i].fd=cli_sfd;
            break;
        }
        if(i==MAX_CLIENTS) //Too many clients
        {
            cerr << "<Error> Too many clients";
            exit(EXIT_FAILURE);
        }
        clients[i].events=POLLRDNORM;
        if(i>clis_max)
            i=clis_max;
        if(--clis_ready<=0)
            continue;
    }
    for(int i=1;i<=clis_max;i++)//check all clients for data
    {
        cli_sfd=clients[i].fd;
        if(cli_sfd == -1)
            continue;
        if(clients[i].revents & (POLLRDNORM | POLLERR))
        {
            if(valread = read(cli_sfd,buffer,sizeof(buffer))<0)
            {
                if(errno=ECONNRESET)
                {
                    cerr << "<Error> Client aborted connection";
                    close(cli_sfd);
                    clients[i].fd=-1;
                }
                else
                {
                    cerr << "<Error> Read from clients!";
                    close(cli_sfd);
                    exit(EXIT_FAILURE);
                }
                
            }
            else if(valread==0)
            {
                cerr << "<Error> Client close connection";
                close(cli_sfd);
                clients[i].fd=-1;
            }
            else
            {
                cout << "Messg from client: "<< buffer;
                send(cli_sfd,"Response",9,0);
            }
        }
        if(--clis_ready<=0)
            break;
    }
    close(serv_sfd);
    delete[] clients;
    clients=NULL;
    return 0;
}