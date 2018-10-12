#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include "semaforos.h"

#define CICLOS 10
#define NPROCESS 3

char* paises [3] = {"Peru", "Bolivia", "Colombia"};
int* bandera;
SEMAPHORE sem;

#define atomic_xchg(A,B)  __asm__ __volatile__( \
										"	lock xchg %1,%0 ;\n" \
									: "=ir" (A)					 \
									: "m" (B), "ir" (A)			 \
									);

void proceso(int i) {
	int k, lEntrada, lSalida;
	for(k = 0 ; k < CICLOS; k++) {
		
		// Llamada waitsem implementada en la parte 3
		lEntrada = 1;
		do { 
			atomic_xchg(lEntrada, bandera[0]); 
		} while(lEntrada != 0);		
		waitSem(sem);
		
		printf("Entra %s ",paises[i]);
		fflush(stdout);
		sleep(rand()%3);
		printf("- %s Sale\n",paises[i]);
		
		// Llamada waitsignal implementada en la parte 3
		lSalida = 1;
		bandera[1] = 0;
		do { 
			atomic_xchg(lSalida,bandera[1]); 
		} while(lSalida != 0);
		signalSem(sem);
		
		// Espera aleatoria fuera de la sección crítica
		sleep(rand()%3);
		bandera[0] = 0;
		bandera[1] = 0;		
	}
	exit(0);
	// Termina el proceso
}

int main () {
	int semID  = shmget(IPC_PRIVATE, sizeof(SEMAPHORE), IPC_CREAT | 0666);
	int banderaID  = shmget(IPC_PRIVATE, sizeof(int) * 2, IPC_CREAT | 0666);
	
	bandera = (int*) shmat(banderaID, NULL, 0);
	sem = (SEMAPHORE) shmat(semID, NULL, 0);
	
	bandera [0] = 0;
	bandera [1] = 0;
	
	initSem (sem);
	int i;
	pid_t p;
	for (i = 0; i < NPROCESS; i ++) {
		p = fork();
		if(p == 0) {
			proceso(i);
		}
	}
	int status;
	
	for (i = 0; i < NPROCESS; i ++) {
		p = wait(&status);
	}
		
	shmdt(bandera);
	shmdt(sem);
	
}