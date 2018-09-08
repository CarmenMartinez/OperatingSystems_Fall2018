#define _GNU_SOURCE
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

#define FIBER_STACK 1024*64
#define NTHREADS 4
#define ITERATIONS 20000


long double pi_final = 0;
long double pi_parc[NTHREADS];

static int threadFunction(void * args){
	int i;
	int tnum = *((int *) args);
	int min_val = tnum * (ITERATIONS / 4);
	int max_val = (tnum + 1) * (ITERATIONS / 4);
	long double pi = 0, x = 0;

	for (i = min_val; i < max_val; i ++) {
		x = pow(-1, i);
		x /= (2 * i) + 1;
		pi += x;
		x = 0;
	}
	printf("thread %d - %Lf\n", tnum, pi_parc[tnum]);
	pi_parc[tnum] = pi;
	printf("store value in %d - %Lf\n", tnum, pi_parc[tnum]);
}

int main(){
	int i = 0;
	void *stack;
	//time control
	struct timeval ts;
	long long stop_ts;
	long long start_ts;
	int elapsed_time;
	
	pid_t pids[NTHREADS];
	
	int status;
	int args[NTHREADS];
	
	gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec * 1000000 + ts.tv_usec;
	
	stack = malloc (FIBER_STACK);
	if ( stack == 0 ){
		perror("malloc: could not allocate stack");
		exit(1);
	}
	
	for (i = 0; i < NTHREADS; i++) {
		pi_parc[i] = 0;
	}
	
		
	for (i = 0; i < NTHREADS; i++) {
		args[i] = i;
		pids[i] = clone(threadFunction, (char*) stack + FIBER_STACK,
						SIGCHLD, &args[i]);
	}
	
	for (i = 0; i < NTHREADS; i++) {
		pids[i] = wait(&status);
		printf("Ya termine %d\n", i);
	}
	
	free(stack);
	
	for (i = 0; i < NTHREADS; i++) {
		printf("cuanto tiene pi_parc[%d] = %Lf\n", i, pi_parc[i]);
		pi_final += pi_parc[i];
	}
	
	gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec * 1000000 + ts.tv_usec;
	
	elapsed_time = (int) (stop_ts - start_ts);
	
	printf("The value of pi/4 is %Lf\n", pi_final);
	printf("And it took %d microseconds\n", elapsed_time);
	
	return 0;
}

