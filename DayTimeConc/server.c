// Headers
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>


// Socket, address, bind, listen and forever accept
int main(int argc, char* argv[])
{
    int servid, clientid, msglen;
    unsigned int socksize;
    char buf[50];
    struct sockaddr_in servsock, clientsock;
    pid_t pid;
    time_t currenttime;


    if(argc != 2) {
        printf("Usage: %s <port>",argv[0]);
        return 1;
    }

    // Socket
    printf("Listening to clients...\n");

    // Create a socket using TCP

    servid = socket(AF_INET,SOCK_DGRAM, IPPROTO_UDP);
    if ( servid < 0 ){
        printf("Socket Error!\n");
        return 1;
    }
    // Address: Family, IP address, port
    servsock.sin_family = AF_INET;
    servsock.sin_addr.s_addr = INADDR_ANY;
    // Port from user
    servsock.sin_port = htons(atoi(argv[1]));


    // Bind to a port
    if (bind(servid, (struct sockaddr*) &servsock,sizeof(servsock))<0) {
        printf("Failed to bind!\n");
        return 1;
    }

    // Forever accept connections
    while(1) {

        socksize = sizeof(clientsock);
        msglen = recvfrom(servid,buf, 50, 0, (struct sockaddr *) &clientsock, &socksize);
        if(msglen >= 0 ) {
            // if we received a message, create a child process
            if ((pid = fork()) == 0){
                // Runs in the child process
                sleep(50);
                time(&currenttime);
                sendto(servid, ctime(&currenttime), 50, 0, (struct sockaddr *) &clientsock, socksize);
                close(servid);
                exit(0);
            }
        }
    }
    close(servid);
    return 0;

}