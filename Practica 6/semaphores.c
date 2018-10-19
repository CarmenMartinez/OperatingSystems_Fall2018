#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include "semaphores.h"

#define CICLOS 10

char *pais[3]={"Peru","Bolvia","Colombia"};

int idsem;
int *g;

void proceso(int i)
{
	int k;

	for(k=0;k<CICLOS;k++)
	{
		semwait(idsem);	
		
		// Inicia sección Crítica
		printf("Entra %s",pais[i]);
		fflush(stdout);
		sleep(rand()%3);
		printf("- %s Sale\n",pais[i]);
		
		// Termina sección Crítica
		semsignal(idsem);
		
		// Espera aleatoria fuera de la sección crítica
		sleep(rand()%3);
	}
}

int main() {
	int pid;
	int status;
	int args[3];
	int i;
	
	srand(getpid());
	
	idsem = seminit(0x1234,2); 
	
	for(i=0;i<3;i++){
	// Crea un nuevo proceso hijo que ejecuta la función proceso()
	pid=fork();
	if(pid==0)
		proceso(i);
	}
	
	for(i=0;i<3;i++)
		pid = wait(&status);
	
	semerase(idsem);
}
