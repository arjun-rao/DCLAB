#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMSIZE 1024
#define SHMKEY 1234

int main() {
    int *shm_addr, counter, shm_id,ch=1;
    key_t key = SHMKEY;

    shm_id = shmget(key, SHMSIZE, 0666);

    shm_addr = (int *) shmat(shm_id, NULL, 0);
    printf("Address space for shared memory with ID(%d): %p\n", shm_id, shm_addr);

    while(ch==1){
        printf("Press 1 to increment counter:");
        scanf("%d",&ch);
        counter = *shm_addr;
        counter ++;
        *shm_addr = counter;
        printf("Counter: %d\n",counter);
    }

    return 0;
}
