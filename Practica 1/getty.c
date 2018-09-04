#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>
#include<unistd.h>

#define MAXPASSWD 50
#define MAXUSERS 50

char credentials[MAXPASSWD][MAXUSERS];
int nUsers = 0;
char shParam[] = {NULL};

char * getUser(int indice){
	char * user = malloc(sizeof *user);
	const char s[2] = ":";
	char credential[MAXPASSWD];
	
	memset(credential, '\0', sizeof(credential));
	strcpy(credential, credentials[indice]);
	
	user = strtok(credential, s);

	return user;
}
						
char * getPasswd(int indice){
	char * passwd = malloc(sizeof *passwd);
	const char s[2] = ":";
	char credential[MAXPASSWD];
	
	memset(credential, '\0', sizeof(credential));
	strcpy(credential, credentials[indice]);
	
	passwd = strtok(credential, s);
	passwd = strtok(NULL, s);

	return passwd;
}

int verifyUser(char *user, char *passwd){
	int i, x;
	char * vUser = malloc(sizeof *vUser);
	char * vPasswd = malloc(sizeof *vPasswd);
	char * withoutPass = malloc(sizeof *withoutPass);
	
	for(i = 0; i < nUsers; i++){
		strcpy(vUser, getUser(i));
		
		if(strcmp(user, vUser) == 0){
			strcpy(vPasswd, getPasswd(i));
			sscanf(vPasswd, "%s", withoutPass);
			if(strcmp(passwd, withoutPass) == 0){
				return 1;
			}
		}
	}
	
	
	strcpy(vPasswd, getPasswd(0));
	strcpy(vUser, getUser(1));
	
	return 0;
}

void waitChild(){
	int status;
	printf("bye, bye");
	wait(&status);
}

void openShell(){
	int status;
	pid_t p;
	p = fork();
	if(p == 0){
		//abrir la nueva ventana
		execlp("./sh", shParam, NULL);
		//waitpid(p, &status, 0);
		//wait(&status);
	}
	waitpid(p, &status, 0);
	signal(SIGCHLD, waitChild);
}



int main(){
	FILE * fpasswd;
	int i;
		
	//Read all the passwords from the passwd.txt file
	fpasswd = fopen("passwd.txt","r");
	for(i = 0; i < MAXPASSWD; i++){
		if(fgets(credentials[i], MAXPASSWD, fpasswd)==NULL){
			break;
		}
		nUsers++;
	}
	
	//Enter the right credentials
	char user[MAXUSERS], passwd[MAXUSERS];
	char * sUser;
	char * sPasswd = malloc(sizeof * sPasswd);
	int m = 1;
	
	while(m){
		printf("User: ");
		fgets(user, MAXUSERS, stdin);
		sscanf(user, "%s", sUser);
		printf("Password: ");
		fgets(passwd, MAXUSERS, stdin);
		sscanf(passwd, "%s", sPasswd);
		if(verifyUser(sUser, sPasswd) == 1){
			printf("User verified\n");
			openShell();
			//wait(NULL);
			printf("Regrese bitches!");
			//m = 0;
			//hacer todo el desvergue
		};
	}
	printf("Ya me sali alv");	
	return 0;
}