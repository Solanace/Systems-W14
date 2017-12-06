#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#define KEY 214263

int main(int argc, char **argv) {
	printf("KEY: %d\n", KEY);
	if (argc > 1) {
		if (!strcmp(argv[1], "-c")) {
			printf("Creating semaphore\n");
			int id = semget(KEY, 1, 0666 | IPC_CREAT);
			if (id < 0) {
				printf("Semaphore already exists!\n");
			}
			else {
				printf("Semaphore created with a key of %d\n", KEY);
				union semun {
					int val;
					struct semid_id *buf;
					ushort *array;
				} argument;
				argument.val = atoi(argv[2]);
				if (semctl(id, 0, SETVAL, argument) < 0) {
					printf("Could not set semaphore value\n");
				}
			}
		}
		
		else if (!strcmp(argv[1], "-v")) {
			printf("Viewing semaphore\n");
			int val = semctl(KEY, 0, 0);
			printf("Semaphore value: %d\n", val);
		}
		
		else if (!strcmp(argv[1], "-r")) {
			printf("Removing semaphore\n");
			semctl(KEY, 0, IPC_RMID);
		}
	}
	return 0;
}
	
