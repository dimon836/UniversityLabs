#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {
    int retval, shmid;
    void *memory = NULL;
    char *p;

    shmid = shmget((key_t)123456789, 6, (IPC_CREAT|IPC_EXCL)|0666);

    if (shmid < 0) {
        printf("\nThe Creation has gone as a failure, Sorry");
        return printf("\n%d\n", errno);
    }

    printf("\nWe are getting the shared memory created %d", shmid);
    memory = shmat(shmid, NULL, 0);

    if(memory == NULL) {
        printf("\nAttachment failure, Sorry");
        return 0;
    }
    p = (char*) memory;

    memset(p, '\0', 6);
    memcpy(p, "hello", 6);
    retval = shmdt(p);
    if(retval < 0) {
        printf("\n Suffered Detachment");
        return 0;
    }
}
