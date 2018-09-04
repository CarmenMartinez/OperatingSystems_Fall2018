#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXPASSWD 50
#define MAXUSERS 50

char credentials[MAXPASSWD][MAXUSERS];

char * getUser(int indice){
	
	char* ayuda = "AYUDAGetUser";
	printf("%s\n", ayuda);
	int i, x = 0;
	char * user;
	int twoPoints = 0;
	for(i = 0; i < 	MAXPASSWD; i++){
		char* ayuda = "AYUDA";
		printf("%s %d\n", ayuda,i);
		if(credentials[indice][i] == ':'){
			char* ayuda = "AYUDAGetUserCredential indice i";
			printf("%s\n", ayuda);
			twoPoints = 1;
		}
		if(!twoPoints){
			char* ayuda = "AYUDAGetUser if not two points";
			printf("%s\n", ayuda);
			*user = credentials[indice][i];
			user++;
		}
	}
	return user;
}
						
char * getPasswd(int indice){
	int i, x = 0;
	char * passwd;
	int twoPoints = 0;
	for(i = 0; i < MAXPASSWD; i++){
		if(
		if(credentials[indice][i] == ':'){
			twoPoints = 1;
		}
		if(twoPoints){
			passwd[x] = credentials[indice][i];
			x++;
		}
	}
	return passwd;
}

int verifyUser(char *user, char *passwd){
	int i, x;
	char * vUser;
	char * vPasswd;
	
	printf("%s\n", user);
	printf("%s\n", passwd);
	printf("%s\n", credentials[0]);	
	char* ayuda = "AYUDA";
	printf("%s\n", ayuda);
	vUser = getUser(0);
	
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
	}
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
		if(veriflyUser(user, passwd) == 1){
			printf("User verified");
			//hacer todo el desvergue
		};
	}
	
	for(int i = 0; i < nUsers; i++){
		printf("%s",credentials[i]);
	}	
	return 0;
}