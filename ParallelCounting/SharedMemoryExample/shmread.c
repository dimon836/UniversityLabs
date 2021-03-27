//
// Created by Dima on 18.01.2021.
//

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>

int main() {
    int shmid; // retval,
    void *memory = NULL;
    char *p;

    shmid = shmget((key_t)123456789, 6, IPC_CREAT|0666);
    if (shmid < 0) {
        printf("\n The Creation has gone as a failure, Sorry");
    }
    printf("\n We are getting the shared memory created %d", shmid);
    memory = shmat(shmid, NULL, 0);
    if (memory == NULL) {
        printf("\n Attachment failure, Sorry");
        return 0;
    }
    p = (char*)memory;

    printf("\n MESSAGE is %s \n", p);
//    retval = shmdt(p);
//    if(retval < 0) {
//        printf("\n Suffered Detachment");
//        return 0;
//    }
    shmctl(shmid, IPC_RMID, NULL); // retval =
    return 0;
}

