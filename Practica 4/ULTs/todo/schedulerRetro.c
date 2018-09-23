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

void scheduler(int arguments) {
	int old,next;
	int changethread = 0;
	int waitingthread = 0;
	
	int event=arguments & 0xFF00;
	int callingthread=arguments & 0xFF;

	if(event == TIMER){
		int i, nextTemp;
		if(numThreads > 0) {
			if(minPriority < 9)
				_enqueue(&priorities[minPriority + 1], callingthread);
			else
				_enqueue(&priorities[9], callingthread);
			for(i = 0; i < 10; i ++) {
				if(_emptyq(&priorities[i]) == 0) {
					minPriority = i;
					nextTemp = _dequeue(&priorities[i]);
					_enqueue(&ready,nextTemp);
					threads[callingthread].status = READY;
					changethread = 1;
					break;
				}
			}
		}
	}
	
	if(event == NEWTHREAD) {
		threads[callingthread].status = READY;
		_enqueue(&priorities[0],callingthread);
		minPriority = 0;
		numThreads ++;
	}
	
	if(event == BLOCKTHREAD) {
		int i, nextTemp;
		threads[callingthread].status=BLOCKED;
		_enqueue(&waitinginevent[blockevent],callingthread);
		
		for(i = 0; i < 10; i ++) {
			if(_emptyq(&priorities[i]) == 0) {
				minPriority = i;
				nextTemp = _dequeue(&priorities[i]);
				_enqueue(&ready, nextTemp);
				changethread = 1;
				break;
			}
		}
	}

	if(event == ENDTHREAD) {
		threads[callingthread].status=END;
		changethread = 1;
		numThreads--;
		
		int i, nextTemp;
		
		for(i = 0; i < 10; i ++) {
			if(_emptyq(&priorities[i]) == 0) {
				minPriority = i;
				nextTemp = _dequeue(&priorities[i]);
				_enqueue(&ready, nextTemp);
				break;
			}
		}
	}
	
	if(event == UNBLOCKTHREAD) {
		threads[callingthread].status=READY;
		if(minPriority < 9)
			_enqueue(&priorities[minPriority + 1], callingthread);
		else
			_enqueue(&priorities[9], callingthread);
	}

	
	if(changethread) {
		old = currthread;
		next = _dequeue(&ready);
		
		threads[next].status=RUNNING;
		_swapthreads(old,next);
	}

}
