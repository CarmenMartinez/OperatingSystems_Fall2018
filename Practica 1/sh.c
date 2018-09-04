#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int nParams = 0;

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
	int i = 0, j;
	
	for (j = 0; j < sizeof(params); j ++) {
		params[j] = malloc(sizeof * params);
	}
	
	strcpy(param, command);
	printf("Param getParam: %s\n", param);
	
	strtok(param, s);
	printf("Param getParam strtok: %s\n", param);
	nParams = 0;	
	while((param = strtok(NULL, s)) != NULL){
		strcpy(params[i], param);
		printf("Params[%d] getParam: %s\n",i, params[i]);
		i ++;
		nParams ++;
	}
		
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
		}else if(strcmp(command, "shutdown")== 0){
			printf("Ayo ayo amigo ayo\n");
			exit(1);
		}else{
			char* singleCommand = getCommand(command);
			printf("Single Command: %s\n", singleCommand);
			printf("Command: %s\n", command);
			char** params = getParams(command);
			int i = 0;
			printf("nParams %d\n", nParams);
			for (i = 0; i < nParams; i ++) {
				printf("Param %d: %s\n",i, params[i]);
			}
			printf("huehuehue\n");
		}
	}
	return 0;
}