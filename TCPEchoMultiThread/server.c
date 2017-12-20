// Headers
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

// Message to send

void echo_str(int socket){
    char msg[50];
    recv(socket,msg,50,0);
    printf("Received from client: %s\n",msg);
    //Echo to client
    send(socket, msg, 50, 0);
}


static void * handler (void * clientid) {
    // detach
    pthread_detach(pthread_self());

    // process request
    echo_str((int) clientid);
    close((int)clientid);

    // gracefully exit
    pthread_exit(0);
    return NULL;
}

// Socket, address, bind, listen and forever accept
int main(int argc, char* argv[])
{
    int servid, clientid;
    unsigned int socksize;
    // Socket address
    struct sockaddr_in servsock, clientsock;
    pthread_t thread;


    if(argc != 2) {
        printf("Usage: %s <port>",argv[0]);
        return 1;
    }

    // Socket
    printf("Listening to clients...\n");

    // Create a socket using TCP

    servid = socket(AF_INET,SOCK_STREAM, 0);

    // Address: Family, IP address, port
    servsock.sin_family = AF_INET;
    servsock.sin_addr.s_addr = INADDR_ANY;
    // Port from user
    servsock.sin_port=htons(atoi(argv[1]));


    // Bind to a port
    bind(servid, (struct sockaddr*) &servsock,sizeof(servsock));

    // Listen for upto 5 concurrent connections
    listen(servid,5);

    socksize = sizeof(clientsock);
    // Forever accept connections
    while(1) {
        clientid = accept(servid,(struct sockaddr*) &clientsock, &socksize );
        printf("Connected to client...\n");

        // process request on a separate thread
        // variable to store thread id, NULL, function to run static void * foo(void * params)
        pthread_create (&thread,NULL,&handler,(void *) clientid);
    }


    close(servid);
    return 0;

}