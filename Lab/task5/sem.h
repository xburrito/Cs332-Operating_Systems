// Albert Chang - Task 5
// Csc 33200 - S

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union arg{
	int val;
	struct semid_ds *buff;
	char *array;
};

// Create semaphore based on key param to init_val
void sem_create(int semid, int init_val) {
 	int semval;
	union semun {
		int val;
 		struct semid_ds *buff;
 		unsigned short *array;
  }

	s;
	s.val = init_val;
	if((semval = semctl(semid, 0, SETVAL, s)) < 0)
	  printf("\n Error when executing semctl!");
}

// Remove semaphore with semaphore_id from kernel
static void sem_term (sem) int sem; {
  if (semctl(sem,0,IPC_RMID,0) == -1)
	  perror("semctl (terminate)");
  printf("Semaphore with value of sem = %d is terminated \n",sem);
}

// Executes operation (op) on semaphore:
  // If op = -1, P-operation will be used
    // * if (semval > 0), val decrements by 1
    // * if (semval == 0), caller gets blocked
  // if op = 1, V-operation will be used
    // * if (semval == 1), current val gets incremented
static void semcall(sem, op) int sem, op; {
  struct sembuf sb;
  sb.sem_num = 0;
  sb.sem_op = op;
  sb.sem_flg = 0; // Block Calls
  if (semop(sem, &sb, 1) == -1)
	  perror("semop");
}

// P-operation. Called during entry to critical region
static void P(sem) int sem; {
  semcall(sem, -1);
}

// V-operation. Called when exiting critical region
static void V(sem) int sem; {
  semcall(sem, 1);
}
