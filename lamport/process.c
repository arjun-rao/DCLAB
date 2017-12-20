#include <stdio.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int count;
    int src;
    int dest;
    int timestamp;
    int message;
} share;

typedef struct {
    int pid;
    int *timestamp;
    share *shm_addr;
} thread_data;

#define SHMSIZE 1024
#define SHMKEY 1234

static void *receiver (void * d){
    pthread_detach(pthread_self());
    thread_data* data = (thread_data *) d;
    share *shm_addr = data->shm_addr;
    printf("\nProcess: %d\n",data->pid);
    while(1){
        if(data->pid == shm_addr->dest && shm_addr->message == 1){
            printf("\nMessage received from process %d, with timestamp: %d\n",  shm_addr->src,shm_addr->timestamp);
            if(*(data->timestamp) < shm_addr->timestamp){
                *(data->timestamp) = shm_addr->timestamp+1;
            }
            else {
                *(data->timestamp) += 1;
            }
            shm_addr->src = -1;
            shm_addr->dest = -1;
            shm_addr->timestamp = -1;
            shm_addr->message = 0;
            printf("\nCurrent Timestamp: %d\n$:",*(data->timestamp));
            fflush(stdout);
        }
    }

}


int main(){
    int pid,choice,shm_id,flag = 0,temp;
    int timestamp = 0;
    share *shm_addr;
    pthread_t thread;
    key_t key = SHMKEY;
    shm_id = shmget(key,SHMSIZE, 0666);
    if (shm_id == -1) {
        shm_id = shmget(key,SHMSIZE,IPC_CREAT|0666);
        flag = 1;
    }
    shm_addr = (share *) shmat(shm_id,NULL,0);
    thread_data data;
    data.shm_addr = shm_addr;
    if(flag){
        shm_addr->count = 1;
    }
    pid = shm_addr->count + 1;
    shm_addr->count = pid;
    shm_addr->message = 0;
    data.pid = pid;
    data.timestamp = &timestamp;
    pthread_create(&thread,NULL,&receiver, &data);

    while(1)
    {

        printf("\n1: local\n2: send\n3: exit\n");
        printf("\nCurrent Timestamp: %d\n$:",timestamp);
        scanf("%d",&choice);
        switch(choice){
            case 1:
                timestamp++;
                printf("\nLocal Event at %d\n",timestamp);
                break;
            case 2:
                timestamp++;
                printf("\nEnter dest:\n$:");
                scanf("%d",&temp);
                printf("\nMessage sent to %d with timestamp: %d\n",temp,timestamp);
                shm_addr->src = pid;
                shm_addr->dest = temp;
                shm_addr->timestamp = timestamp;
                shm_addr->message = 1;
                break;
            case 3:
                break;
            default:
                break;
        }
        if (choice == 3)exit(0);
    }
}
