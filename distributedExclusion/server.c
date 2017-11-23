#include<stdio.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include <pthread.h>
#include<sys/types.h>
#include<stdlib.h>


typedef struct thread_data {
    int sockfd;
    int cs;
    int status;
}thread_data;

void *handler(void *threaddata) {
    thread_data *data = (thread_data *)threaddata;
    int sockfd = data->sockfd;
    int cs = data->cs;
    char buf[50];
    char unlockMessage[50] = "UNLOCKED";
    char lockMessage[50] = "LOCKED";
    if (!data->status) {

      send(cs, unlockMessage, 50, 0);
      data->status = 1;
      printf("MUTEX Locked\n");
      printf("Connected to client\n");
      recv(cs, buf, 50, 0);
      printf("Message Received: %s",buf);
      printf("\nEnter message to send: ");
      fgets(buf, 50, stdin);
      send(cs, buf, 50, 0);
      close(cs);
      data->status = 0;
      printf("\nMUTEX unlocked. Disconnected from client\n");
    } else {
      send(cs, lockMessage, 50, 0);
      close(cs);
    }
    pthread_exit(NULL);
  }


int main()
{
    int servid, clientid;
    struct sockaddr_in servaddr, clientaddr;
    pthread_t temp;
    int lock = 0;
    char buf[50];


    servid = socket(AF_INET, SOCK_STREAM, 0);

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5000);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    printf("Binding server to socket\n");
    bind(servid, (struct sockaddr *)&servaddr, sizeof(servaddr) );

    printf("Listening\n");
    listen(servid, 5);
    thread_data td;
    td.sockfd = servid;
    td.status = lock;
    while(1){
        unsigned int socksize = sizeof(clientaddr);
        clientid = accept(servid, (struct sockaddr *)&clientaddr, &socksize);
        td.cs = clientid;
        pthread_create(&temp, NULL, handler, (void *)&td);

    }
    close(servid);
    pthread_exit(NULL);
    return 0;
}