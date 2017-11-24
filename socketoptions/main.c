#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <errno.h>
/*
struct linger
{
    int l_onoff;		/* Nonzero to linger on close.  
    int l_linger;		/* Time to linger.  
};*/

int sockfd,sendbuf,recvbuf,nodelay,keepalive,status;
int optlen = sizeof(status);
struct linger linopt;


void get_sockopts()
{

	//SO_KEEPALIVE 
	status = getsockopt(sockfd,SOL_SOCKET,SO_KEEPALIVE,&keepalive,&optlen);
	
	if (status == 0){
		printf("\nSO_KEEPALIVE is set to %s\n",keepalive?"ON":"OFF");
	}
	
	//SO_SNDBUF
	status = getsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,&sendbuf,&optlen);
	
	if (status == 0){
		printf("\nSO_SNDBUF is set to %d\n",sendbuf);
	}
	
	//SO_RCVBUF
	status = getsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&recvbuf,&optlen);
	
	if (status == 0){
		printf("\nSO_RCVBUF is set to %d\n",recvbuf);
	}
	
	//SO_LINGER
	status = getsockopt(sockfd,SOL_SOCKET,SO_LINGER,&linopt,&optlen);
	
	if (status == 0){
		printf("\nSO_LINGER is set to %s with time to linger: %d\n",linopt.l_onoff?"ON":"OFF",linopt.l_linger);
	}
	
	//TCP_NODELAY
	getsockopt(sockfd,IPPROTO_TCP,TCP_NODELAY,&nodelay,&optlen);
	printf("\nTCP_NODELAY is set to %s\n",nodelay?"ON":"OFF");
	


}

int main(){
	
	
	printf("Getting default socket options for a new socket...\n");
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	get_sockopts();
	
	// change KEEPALIVE
	keepalive = !keepalive;
	optlen = sizeof(keepalive);
	status = setsockopt(sockfd,SOL_SOCKET,SO_KEEPALIVE,&keepalive,optlen);
	
	// change SENDBUF
	sendbuf = 1;
	optlen = sizeof(sendbuf);
	status = setsockopt(sockfd,SOL_SOCKET,SO_SNDBUF,&sendbuf,optlen);
	
	// change RECVBUF
	recvbuf = 1;
	optlen = sizeof(recvbuf);
	status = setsockopt(sockfd,SOL_SOCKET,SO_RCVBUF,&recvbuf,optlen);
	
	// change TCP_NODELAY
	nodelay = !nodelay;
	optlen = sizeof(nodelay);
	status = setsockopt(sockfd,IPPROTO_TCP,TCP_NODELAY,&nodelay,optlen);
	
	// change SO_LINGER
	optlen = sizeof(linopt);
	linopt.l_onoff = !linopt.l_onoff;
	linopt.l_linger = 10;
	status = setsockopt(sockfd,SOL_SOCKET,SO_LINGER,&linopt,optlen);
	
	printf("\nAfter configuration, the socket options are: \n");
	
	get_sockopts();
	
	
	
}
