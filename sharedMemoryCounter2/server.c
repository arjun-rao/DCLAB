#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSIZE 1024
#define SHMKEY 1234

int main() {
    int *shm_addr, counter, shm_id;
    key_t key = SHMKEY;

    shm_id = shmget(key, SHMSIZE, IPC_CREAT | 0666);

    shm_addr = (int *) shmat(shm_id, NULL, 0);
    printf("Address space for shared memory with ID(%d): %p\n", shm_id, shm_addr);

    counter =  1;
    *shm_addr = counter;
    printf("Waiting for clients...\n");
    fflush(stdout);
    while(1)
    {
        if (*shm_addr != counter){
            printf("Counter was incremented to: %d\n", *shm_addr);
            fflush(stdout);
            counter = *shm_addr;
        }
    }

    return 0;
}
