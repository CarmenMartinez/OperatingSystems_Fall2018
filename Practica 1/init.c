#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>

#define NPROCESS 6

char* gettyParam[] = {"-e", "./getty", NULL};

void handleChild();

int main(){
	pid_t p;
	int status, i;
	char command[50];
	char pid[4];


	for(i = 0; i < NPROCESS; i++){
		p = fork();
		if(p == 0){
			//Creacion de 6 procesos 
			execvp("xterm", gettyParam);
		}
		
	}

	signal(SIGCHLD, handleChild);			

	while(1){
		fgets(command, 50, stdin);	
		if(strncmp(command, "shutdown", 8) == 0){
			//0 = grupo de procesos
			//-PID = grupo de procesos absoluto
			kill(0, SIGTERM);
		}
	}		
}

void handleChild() {
	int status;
	wait(&status);
	printf("handleChild %d\n", status);
	if(status != 0){
		kill(0, SIGTERM);
	}
	pid_t p;
	p = fork();
	if(p == 0){
		//Creacion de 6 procesos 
		execvp("xterm", gettyParam);
	}
}
