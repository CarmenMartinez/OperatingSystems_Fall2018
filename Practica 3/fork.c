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

#define ITERATIONS 2000000000
#define NPROCESS 4

int activeSons = 0;

//time managment
struct timeval ts;
long long stop_ts;
long long start_ts;
int elapsed_time;

void handleChild();

int main(){
	int i = 0, high, low, j;
	pid_t p;
	long double pi = 0, x;
	
	gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec * 1000000 + ts.tv_usec;
	
	//crear memoria
	printf("papa malo\n\n");
	for(j = 0; j < NPROCESS; j++){
		high = (ITERATIONS / 4) * (j+1);
		low = (ITERATIONS / 4) * (j);
		//printf("low = %d\n", low);
		//printf("high = %d\n", high);
		p = fork();
		if (p == 0){
			printf("nino %d malo\n", j);
			activeSons++;
			printf("%d low = %d\n", j, low);
			printf("%d high = %d\n", j, high);
			pi = 0;
			for(i = low; i < high; i++){
				x = pow(-1, i);
				x /= (2*i)+1;
				pi += x;
				x = 0;
			}
			printf("The value of %d pi/4 is %0.19Lf\n", j, pi);
			//pedir memoria
			//guardar en memoria
			exit(0);
		}
	}
	
	signal(SIGCHLD, handleChild);	
	
	return 0;
}

void handleChild() {
	int status;
	wait(&status);
	
	/*if(activeSons > 0){
		activeSons--;
		return;
	}*/
	
	gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec * 1000000 + ts.tv_usec;
	
	elapsed_time = (int) (stop_ts - start_ts);
	
	//printf("The value of pi/4 is %Lf\n", pi);
	printf("And it took %d microseconds\n", elapsed_time);
}
