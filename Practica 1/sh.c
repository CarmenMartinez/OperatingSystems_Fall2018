#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main(){
	char * command = malloc (sizeof * command);
	while(1){
		printf("sh>");
		gets(command, stdin);
		if(strcmp(command, "exit") == 0){
			printf("Salir\n");
			return 0;
		}
	}
}