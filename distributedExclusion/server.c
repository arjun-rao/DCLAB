#include<stdio.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>

int main()
{
    int servid, clientid;
    struct sockaddr_in servaddr, clientaddr;

    servid = socket(AF_INET, SOCK_STREAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5000);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    printf("Binding server to socket\n");
    bind(servid, (struct sockaddr *)&servaddr, sizeof(servaddr) );

    printf("Listening\n");
    listen(servid, 5);
   
    while(1){
        unsigned int socksize = sizeof(clientaddr);
        clientid = accept(servid, (struct sockaddr *)&clientaddr, &socksize);

        printf("Connected to client\n");
       
        
    }
    close(clientid);
    close(servid);
    return 0;
}