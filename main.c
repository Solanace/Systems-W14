#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#define KEY 214263

int main(int argc, char **argv) {
	// printf("KEY: %d\n", KEY);
	int sem_desc;
	if (argc > 1) {
		if (!strcmp(argv[1], "-c")) {
			// printf("Creating semaphore\n");
			sem_desc = semget(KEY, 1, 0644 | IPC_CREAT | IPC_EXCL);
			if (sem_desc < 0) {
				printf("Semaphore already exists!\n");
			}
			else {
				union semun {
					int val;
					struct semid_ds *buf;
					unsigned short *array;
					struct seminfo *__buf;
				} arg;
				arg.val = atoi(argv[2]);
				if (semctl(sem_desc, 0, SETVAL, arg) < 0) {
					printf("Error encountered while setting value of semaphore\n");
					printf("%s\n", strerror(errno));
				}
				printf("Semaphore created with a semid of %d\n", sem_desc);
			}
		}
		else if (!strcmp(argv[1], "-v")) {
			// printf("Viewing semaphore\n");
			sem_desc = semget(KEY, 1, 0);
			int sem_val = semctl(sem_desc, 0, GETVAL);
			if (sem_val < 0) {
				printf("Error encountered while viewing semaphore\n");
				printf("%s\n", strerror(errno));
			}
			else printf("Semaphore value: %d\n", sem_val);
		}
		else if (!strcmp(argv[1], "-r")) {
			// printf("Removing semaphore\n");
			sem_desc = semget(KEY, 1, 0);
			int sem_val = semctl(sem_desc, 0, IPC_RMID);
			if (sem_val < 0) {
				printf("Error encountered while removing semaphore\n");
				printf("%s\n", strerror(errno));
			}
			else printf("Semaphore removed: %d\n", sem_desc);
		}
	}
	return 0;
}
