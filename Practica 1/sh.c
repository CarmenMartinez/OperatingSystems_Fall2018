#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>



int nParams = 0;
int flag = 0;

char* getCommand(char* command) {
	char * singleCommand = malloc(sizeof * singleCommand);
	const char s[1] = " ";
	strcpy(singleCommand, command);
	strtok(singleCommand, s);
	return singleCommand;
}

char** getParams(char* command) {
	char ** params = malloc(sizeof * command);
	char * param = malloc (sizeof * param);
	const char s[1] = " ";
	int i = 3, j;
	
	for (j = 0; j < sizeof(params); j ++) {
		params[j] = malloc(sizeof * params);
	}
	
	strcpy(param, command);
	strcpy(params[0], "sh");
	strcpy(params[1], "-c");
	strcpy(params[2], param);
	//strtok(param, s);
	nParams = 0;	
	while((param = strtok(NULL, s)) != NULL){
		strcpy(params[i], param);
		i ++;
		nParams ++;
	}
	
	if(strcmp(params[i-1], "&") == 0) {
		flag = 1;
	}
	
	params[i] = NULL;
	return params;
}

int main(){
	char * command = malloc (sizeof * command);
	while(1){
		printf("sh>");
		gets(command, stdin);
		if(strcmp(command, "exit") == 0){
			printf("This is it folks\n");
			exit(0);
		}else if(strcmp(command, "shutdown") == 0){
			printf("Ayo ayo amigo ayo\n");
			exit(1);
		}else{
			char* singleCommand = getCommand(command);
			char** params = getParams(command);
			int status;
			pid_t p;
			p = fork();
			if(p == 0) {
				execv("/bin/sh", params);
			}
			
			//if (!flag) {
				wait(&status);
			//}
			//	flag = 0;
			
			
		}
		fflush(stdin);
	}
	return 0;
}