#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSIZE 4096
#define SHMKEY 5678

int main()
{
    int shmid, counter, num = 1;
    key_t key = SHMKEY;
    int* shm_addr;

    shmid = shmget(key, SHMSIZE, 0666);
    printf("Accessed Shared Memory with ID: %d\n", shmid);

    shm_addr = (int *) shmat(shmid, NULL, 0);
    printf("Shared Memory Address: %d\n", shm_addr);

    while ( num == 1)
        printf("Enter 1 to increment ");
        scanf("%d", &num);
        counter = *shm_addr;
        counter = counter + 1;
        *shm_addr = counter;
        printf("Counter Value: %d\n", counter);
    }
    
    return 0;
}
