#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

//commondata
#define MAXTHREAD 10

typedef struct _QUEUE {
	int elements[MAXTHREAD];
	int head;
	int tail;
} QUEUE;


//libthreads

void _initqueue(QUEUE *q) {
	q->head=0;
	q->tail=0;
}
	

void _enqueue(QUEUE *q,int val) {
	q->elements[q->head]=val;
	// Incrementa al apuntador
	q->head++;
	q->head=q->head%MAXTHREAD;
}


int _dequeue(QUEUE *q) {
	int valret;
	valret=q->elements[q->tail];
	// Incrementa al apuntador
	q->tail++;
	q->tail=q->tail%MAXTHREAD;
	return(valret);
}

//Semaforos

struct SEMAPHORE {
	int count;
	QUEUE blockprocess;
};

typedef struct SEMAPHORE* SEMAPHORE;

void waitSem(SEMAPHORE s) {
	s->count --;
	if(s->count < 0) {
		//Se ingresa el proceso a la cola de procesos bloqueados
		_enqueue(&(s->blockprocess), getpid());
		//Se bloquea el proceso actual
		kill(getpid(), SIGSTOP);
	}
}

void signalSem(SEMAPHORE s) {
	s->count ++;
	if(s->count <= 0) {
		//Se quita el proceso de la lista de bloqueados
		int pid = _dequeue(&(s->blockprocess));
		//Se desbloquea el proceso
		kill(pid, SIGCONT);
	}
}

void initSem(SEMAPHORE s) {
	s->count = 1;
	_initqueue(&(s->blockprocess));
}


//