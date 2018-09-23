#include <scheduler.h>
#include <stdio.h>

extern THANDLER threads[MAXTHREAD];
extern int currthread;
extern int blockevent;
extern int unblockevent;

QUEUE priorities[10];
QUEUE ready;
QUEUE waitinginevent[MAXTHREAD];

int minPriority = 0;
int numThreads = -1;

void scheduler(int arguments)
{
	int old,next;
	int changethread=0;
	int waitingthread=0;
	
	int event=arguments & 0xFF00;
	int callingthread=arguments & 0xFF;

	if(event==TIMER){
		int i, nextTemp;
		if(numThreads > 0) {
			//printf("TIMER numThreads %d | minPriority %d\n", numThreads, minPriority);
			if(minPriority < 9)
				_enqueue(&priorities[minPriority + 1], callingthread);
			else
				_enqueue(&priorities[9], callingthread);
			for(i = 0; i < 10; i ++) {
				if(_emptyq(&priorities[i]) == 0) {
					//printf("TIMER not empty queue %d\n", i);
					minPriority = i;
					nextTemp = _dequeue(&priorities[i]);
					_enqueue(&ready,nextTemp);
					threads[callingthread].status = READY;
					changethread = 1;
					break;
				}
			}
		}
		
		/*if(_emptyq(&ready) == 0){
			threads[callingthread].status = READY;
			_enqueue(&ready, callingthread);
			changethread = 1;
		}*/
	}
	
	if(event==NEWTHREAD)
	{
		// Un nuevo hilo va a la cola de listos
		threads[callingthread].status = READY;
		_enqueue(&priorities[0],callingthread);
		minPriority = 0;
		numThreads ++;
		//printf("numThreads en NEWTHREAD %d\n", numThreads);
	}
	
	if(event == BLOCKTHREAD)
	{
		//printf("ENTRE a BLOCKED\n");
		threads[callingthread].status=BLOCKED;
		_enqueue(&waitinginevent[blockevent],callingthread);
		
		int i, nextTemp;
		
		for(i = 0; i < 10; i ++) {
			if(_emptyq(&priorities[i]) == 0) {
				//printf("cola no vacia %d\n", i);
				minPriority = i;
				nextTemp = _dequeue(&priorities[i]);
				_enqueue(&ready, nextTemp);
				//threads[callingthread].status = READY;
				changethread = 1;
				break;
			}
		}
	}

	if(event == ENDTHREAD)
	{
		//printf("ENDTHREAD\n");
		threads[callingthread].status=END;
		changethread = 1;
		numThreads--;
		
		int i, nextTemp;
		
		for(i = 0; i < 10; i ++) {
			if(_emptyq(&priorities[i]) == 0) {
				//printf("cola no vacia %d\n", i);
				minPriority = i;
				nextTemp = _dequeue(&priorities[i]);
				_enqueue(&ready, nextTemp);
				//threads[callingthread].status = READY;
				changethread = 1;
				break;
			}
		}
	}
	
	if(event == UNBLOCKTHREAD)
	{
		threads[callingthread].status=READY;
		//_enqueue(&ready,callingthread);
		//printf("UNBLOCK\n");
		if(minPriority < 9)
			_enqueue(&priorities[minPriority + 1], callingthread);
		else
			_enqueue(&priorities[9], callingthread);

	}

	
	if(changethread)
	{
		old = currthread;
		next = _dequeue(&ready);
		
		threads[next].status=RUNNING;
		_swapthreads(old,next);
	}

}
