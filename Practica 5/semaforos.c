#include <libthreads.h>
#include <commondata.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>


struct SEMAPHORE {
	int count;
	QUEUE blockprocess;
};

typedef struct SEMAPHORE* SEMAPHORE;

void waitSem(SEMAPHORE s) {
	s->count --;
	if(s->count < 0) {
		//Se ingresa el proceso a la cola de procesos bloqueados
		_enqueue(&(s->blocprocess), getpid());
		//Se bloquea el proceso actual
		kill(getpid(), SIGSTOP);
	}
}

void signalSem(SEMAPHORE s) {
	s->count ++;
	if(s->count <= 0) {
		//Se quita el proceso de la lista de bloqueados
		int pid = _dequeue(&(s->blocprocess));
		//Se desbloquea el proceso
		kill(pid, SIGCONT);
	}
}

void initSem(SEMAPHORE s) {
	s->count = 1;
	_initqueue(&(s->blocprocess));
}