#include<stdio.h>
#include<stdlib.h>
#include<string.h>



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
			
		}
	}
	return 0;
}