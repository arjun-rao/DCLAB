// Headers
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>

// Message to send

void getTime(int sockid, struct sockaddr * address){
    char out[50];
    unsigned int socksize = sizeof(*address);
    if (sendto(sockid, "time", 5, 0, address, socksize) < 0)
        printf("failed to send \n");
    //receive message from server
    recvfrom(sockid,out,50,0,address, &socksize);
    printf("Time is: %s\n",out);
}

// socket, address, connect , Send & receive
int main(int argc, char* argv[])
{
    int sockid;
    clock_t start, end;
    // Socket address
    struct sockaddr_in sock;

    if(argc != 2) {
        printf("Usage: %s <port>",argv[0]);
        return 1;
    }

    // Socket
    printf("Connecting to server...\n");

    // Create a socket using TCP

    sockid = socket(AF_INET,SOCK_DGRAM, IPPROTO_UDP);

    // Address: Family, IP address, port
    sock.sin_family = AF_INET;
    sock.sin_addr.s_addr = inet_addr("127.0.0.1");
    // Port from user
    sock.sin_port=htons(atoi(argv[1]));
    start = clock();
    // Get Time from Server
    getTime(sockid,(struct sockaddr *) &sock);
    end = clock();

    printf("Response time: %f seconds", ((double) end-start)/CLOCKS_PER_SEC);
    close(sockid);

    return 0;

}