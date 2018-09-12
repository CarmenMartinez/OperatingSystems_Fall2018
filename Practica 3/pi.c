#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

#define ITERATIONS 2000000000

int main(){
	long double pi = 0, x;
	int i = 0;
	struct timeval ts;
	long long stop_ts;
	long long start_ts;
	int elapsed_time;
	
	gettimeofday(&ts, NULL);
	start_ts = ts.tv_sec * 1000000 + ts.tv_usec;
	
	
	for(i = 0; i < ITERATIONS; i++){
		x = pow(-1, i);
		x /= (2*i)+1;
		pi += x;
		x = 0;
	}
	
	gettimeofday(&ts, NULL);
	stop_ts = ts.tv_sec * 1000000 + ts.tv_usec;
	
	elapsed_time = (int) (stop_ts - start_ts);
	
	printf("The value of pi/4 is %0.19Lf\n", pi);
	printf("And it took %d microseconds\n", elapsed_time);
	return 0;
}