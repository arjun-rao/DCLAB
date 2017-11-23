#include<stdio.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>

int main()
{
    int sockid;
    char send_msg[50], recv_msg[50];
    struct sockaddr_in sockaddr;

    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(5000);
    sockaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    sockid = socket(AF_INET, SOCK_STREAM, 0);
    
    connect(sockid, (struct sockaddr *)&sockaddr, sizeof(sockaddr));
    printf("Connected to server\n");

    while(1){
       
        recv(sockid, recv_msg, 50, 0);

        if (strcmp(recv_msg, "LOCKED") == 0) {
            printf("Could not attain Mutual Exclusion\nStatus:%s\n", recv_msg );
            printf("Going to sleep\n");
            sleep(5);
        }
        else {
            printf("Mutual Exlusion\nStatus: %s\n", recv_msg );
            printf("Enter message\n");
            scanf("%s", send_msg);
            send(sockid, send_msg, 50, 0);
            recv(sockid, recv_msg, 50, 0);
            printf("Message from server: %s\n", recv_msg);
            close(sockid);
            break;
        }
    }
    return 0;
}