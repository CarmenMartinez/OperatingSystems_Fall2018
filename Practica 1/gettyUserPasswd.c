#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXPASSWD 50
#define MAXUSERS 50

char credentials[MAXPASSWD][MAXUSERS];
int nUsers = 0;

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
		printf("%d user: %s\n", i, vUser);
		printf("%s vs %s\n", user, vUser);
		if(strcmp(user, vUser) == 0){
			strcpy(vPasswd, getPasswd(i));
			sscanf(vPasswd, "%s", withoutPass);
			printf("get in\n");
			printf("%s vs %s\n", passwd, withoutPass);
			printf("%d password: %s\n", i, withoutPass);
			printf("%d\n", strcmp(passwd, withoutPass));
			if(strcmp(passwd, withoutPass) == 0){
				printf("User verified\n");
				return 1;
			}
		}
	}
	
	
	strcpy(vPasswd, getPasswd(0));
	strcpy(vUser, getUser(1));
	
	return 0;
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
		printf("Passwd %s\n", sPasswd);
		if(verifyUser(sUser, sPasswd) == 1){
			printf("User verified");
			m = 0;
			//hacer todo el desvergue
		};
	}
	
	for(int i = 0; i < nUsers; i++){
		printf("%s",credentials[i]);
	}	
	return 0;
}