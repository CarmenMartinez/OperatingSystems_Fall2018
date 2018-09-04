#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXPASSWD 50
#define MAXUSERS 50

char credentials[MAXPASSWD][MAXUSERS];

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
	strcpy(credential, credentials[0]);
	
	passwd = strtok(credential, s);
	passwd = strtok(NULL, s);

	return passwd;
}

int verifyUser(char *user, char *passwd){
	int i, x;
	char * vUser = malloc(sizeof *vUser);
	char * vPasswd = malloc(sizeof *vPasswd);
	
	//printf("Entered user%s\n", user);
	//printf("Entered passwd%s\n", passwd);
	//printf("Checking with %s\n", credentials[0]);	
	
	vPasswd = getPasswd(0);
	//printf("GetPasswd %s\n", vPasswd);
	strcpy(vUser, getUser(1));
	//vPasswd = getUser(1);
	//printf("GetUser %s\n", vUser);
	
	return 1;
	/*
	for(i = 0; i < 50; i++){
		printf("Entre al for");
		vUser = getUser(i);
		printf("%s\n", vUser);
		if(strncmp(user, vUser, MAXPASSWD) == 0){
			vPasswd = getPasswd(i);
			printf("%s\n", vPasswd);
			if(strncmp(passwd, vPasswd, MAXPASSWD) == 0){
				return 1;
			}
		}
	}*/
	return 0;
}					

int main(){
	FILE * fpasswd;
	//char credentials[MAXPASSWD][MAXUSERS];
	int i, nUsers = 0;
		
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
	while(1){
		printf("User: ");
		fgets(user, MAXUSERS, stdin);
		printf("Password: ");
		fgets(passwd, MAXUSERS, stdin);
		if(verifyUser(user, passwd) == 1){
			printf("User verified");
			//hacer todo el desvergue
		};
	}
	
	for(int i = 0; i < nUsers; i++){
		printf("%s",credentials[i]);
	}	
	return 0;
}