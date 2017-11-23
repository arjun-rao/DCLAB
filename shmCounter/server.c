#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSIZE 4096
#define SHMKEY 5678

int main()
{
    int shmid, counter;
    key_t key = SHMKEY;
    int* shm_addr;

    shmid = shmget(key, 4096, IPC_CREAT | 0666);
    printf("Created Shared Memory with ID: %d\n", shmid);
    
    shm_addr = (int *) shmat(shmid, NULL, 0);
    printf("Shared Memory Address: %d\n", shm_addr);

    printf("Enter the counter value\n");
    scanf("%d", &counter );
    *shm_addr = counter;

    while(1);

    return 0;
}
