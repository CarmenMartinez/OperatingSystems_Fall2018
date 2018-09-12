#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/shm.h>

#define ITERATIONS 2000000000
#define NPROCESS 4

int main(){
	int i = 0, high, low, j, memory;
	pid_t p;
	long double pi = 0, x;
	int status;
	long double res_pi = 0;
	//key_t key;
	
	//time managment
	struct timeval ts;
	long long stop_ts;
	long long start_ts;
	int elapsed_time;
	
	gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec * 1000000 + ts.tv_usec;
	
	//crear memoria
	memory = shmget(IPC_PRIVATE, sizeof(long double)*NPROCESS, IPC_CREAT | IPC_EXCL | 0666);
	long double * res;
	res = (long double*) shmat(memory, NULL, 0);
	for(j = 0; j < NPROCESS; j++){
		high = (ITERATIONS / 4) * (j+1);
		low = (ITERATIONS / 4) * (j);
		p = fork();
		if (p == 0){
			pi = 0;
			for(i = low; i < high; i++){
				x = pow(-1, i);
				x /= (2*i)+1;
				pi += x;
				x = 0;
			}
			res[j] = pi;
			exit(0);
		}
	}
	
	for(j = 0; j < NPROCESS; j++){
		wait(&status);
	}
	for(j = 0; j < NPROCESS; j++){
		res_pi += res[j];
	}
	gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec * 1000000 + ts.tv_usec;
	
	elapsed_time = (int) (stop_ts - start_ts);
	
	printf("The value of pi/4 is %0.19Lf\n", res_pi);
	printf("And it took %d microseconds\n", elapsed_time);
	
	return 0;
}

