#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSIZE 4096
#define SHMKEY 5678

int main()
{
    int shmid, counter = 1;
    key_t key = SHMKEY;
    int* shm_addr;

    shmid = shmget(key, 4096, IPC_CREAT | 0666);
    printf("Created Shared Memory with ID: %d\n", shmid);
    
    shm_addr = (int *) shmat(shmid, NULL, 0);
    printf("Shared Memory Address: %d\n", shm_addr);

    *shm_addr = counter;

    printf("Waiting for clients...\n");
    while(1)
    {
        if (*shm_addr != counter){
            printf("Counter was incremented to: %d\n", *shm_addr);
            counter = *shm_addr;
        }
    }

    return 0;
}
