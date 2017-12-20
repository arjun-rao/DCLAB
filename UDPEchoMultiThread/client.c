// Headers
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

// Message to send

void echo_str(int sockid, struct sockaddr * address){
    char in[50],out[50];
    unsigned int socksize = sizeof(*address);
    printf("Enter a string:");
    scanf("%[^\n]s",in);

    //Send to server
    if (sendto(sockid, in, 50, 0, address, socksize) < 0)
        printf("failed to send \n");

    //receive message from server
    recvfrom(sockid,out,50,0,address, &socksize);
    printf("Received: %s\n",out);
}

// socket, address, connect , Send & receive
int main(int argc, char* argv[])
{
    int sockid;
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

    // Send & Receive a message
    echo_str(sockid,(struct sockaddr *) &sock);

    close(sockid);

    return 0;

}