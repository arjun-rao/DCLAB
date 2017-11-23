#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMKEY 2017
#define SHMSIZE 1024

typedef struct event{
    int count,src,dest,timestamp;
    int message;
} event;

int shm_id;
event * shm_addr;

int pid,timestamp = 0;

void receiveEvent(){
    event current = *shm_addr;
    if (current.message && current.dest == pid)
    {
        current.message = 0;
        printf("\nReceived message from %d with timestamp: %d\n",current.src,current.timestamp);
        if (current.timestamp >= timestamp){
            timestamp = current.timestamp+1;
            printf("\nUpdated logical clock to %d\n",timestamp);
        }
        else {
            printf("\n No change to logical clock, value is: %d\n",timestamp);
            timestamp++;
        }

    }
    *shm_addr = current;
}

void localEvent(){
    receiveEvent();
    printf("\nLocal event at time: %d\n",timestamp);
    timestamp++;
}
void sendEvent(){
    int destID;
    printf("Enter destination:");
    scanf("%d",&destID);
    receiveEvent();
    if (shm_addr-> count < destID)
    {
        printf("Invalid destination");
    } else {
        event current = *shm_addr;
        current.src = pid;
        current.dest = destID;
        current.message = 1;
        current.timestamp = timestamp++;
        *shm_addr = current;
        printf("\nSent message to %d with timestamp: %d\n",current.dest,current.timestamp);
    }
}


int main(){

    int ch;
    key_t key = SHMKEY;


    event current;
    shm_id = shmget(key, SHMSIZE, 0666);
    if (shm_id == -1){
        shm_id = shmget(key, SHMSIZE, IPC_CREAT |0666);
        shm_addr =  (event *) shmat(shm_id, NULL, 0);
        current.count = 1;
        current.message = 0;
        current.timestamp = 0;
        pid = current.count;
        *shm_addr = current;
    }
    else {
        shm_addr =  (event *) shmat(shm_id, NULL, 0);
        current = *shm_addr;
        pid = ++current.count;
        current.message = 0;
        current.timestamp = 0;
        *shm_addr = current;
    }
    printf("Process PID = %d",pid);

    while(1){
        printf("\nlogical clock value: %d\n",timestamp);
        printf("\n1. Local event\n2. Send event\n3.Exit\nEnter choice:");
        scanf("%d",&ch);
        switch(ch) {
            case 1:
                localEvent();
                break;
            case 2:
                sendEvent();
                break;
            case 3:
            case 4: //secret reset
                current.count = 0;
                current.message = 0;
                current.timestamp = 0;
                *shm_addr = current;
                break;
            default:
                printf("\n");
        }
        if (ch == 3) break;
    }
}