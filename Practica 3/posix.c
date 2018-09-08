#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include <pthread.h>
#include<sys/time.h>

#define NTHREADS 4
#define ITERATIONS 2000000000

long double cont = 0;
long double contparc[NTHREADS];

void * tfunc(void *args);

int main() {
	
	long double pi = 0, x;
	int i = 0;
	
	//time control
	struct timeval ts;
	long long stop_ts;
	long long start_ts;
	int elapsed_time;
	
	//thread
	int args[NTHREADS];
	pthread_t tid[NTHREADS];
	
	gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec * 1000000 + ts.tv_usec;
	
	for (i = 0; i < NTHREADS; i++) {
		contparc[i] = 0;
	}
	
	for (i = 0; i < NTHREADS; i++) {
		args[i] = i;
		pthread_create(&tid[i], NULL, tfunc, (void *) &args[i]);
	}
	
	for (i = 0; i < NTHREADS; i++) {
		pthread_join(tid[i], NULL);
	}

	for (i = 0; i < NTHREADS; i++) {
		cont += contparc[i];
	}
	
	gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec * 1000000 + ts.tv_usec;
	
	elapsed_time = (int) (stop_ts - start_ts);
	
	printf("The value of pi/4 is %Lf\n", cont);
	printf("And it took %d microseconds\n", elapsed_time);
	
	return 0;
}

void * tfunc(void *args) {
	
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
	
	contparc[tnum] = pi;
}