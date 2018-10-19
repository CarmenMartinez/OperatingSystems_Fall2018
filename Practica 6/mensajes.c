#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/msg.h>
#include <wait.h>

// Definir una estructura que se va a usar para mandar los mensajes
typedef struct {
	long msg_type;		// Tipo de mensaje, debe ser long
	char mensaje[100];	// Contenido
} MSGTYPE; 

#define CICLOS 10

char *pais[3]={"Peru","Bolvia","Colombia"};

MSGTYPE m;
int idmsn;

void proceso(int i)
{
	int k;

	for(k=0;k<CICLOS;k++)
	{
		msgrcv(idmsn,&m,sizeof(MSGTYPE)-sizeof(long),1,0);
		
		// Inicia sección Crítica
		printf("Entra %s",pais[i]);
		fflush(stdout);
		sleep(rand()%3);
		printf("- %s Sale\n",pais[i]);
		
		// Termina sección Crítica
		msgsnd(idmsn,&m,sizeof(MSGTYPE)-sizeof(long),0);
		
		// Espera aleatoria fuera de la sección crítica
		sleep(rand()%3);
	}
	exit(0);
}

int main() {
	int pid;
	int status;
	int args[3];
	int i;
	
	srand(getpid());
	
	//Obtener cola de mensajes
	idmsn = msgget(0x1234,0666|IPC_CREAT);
	
	//Inicializar mensajes
	m.msg_type=1;
    sprintf(m.mensaje,"Inicializando mensajes");
    msgsnd(idmsn,&m,sizeof(MSGTYPE)-sizeof(long),0);
	
	for(i=0;i<3;i++){
	// Crea un nuevo proceso hijo que ejecuta la función proceso()
	pid=fork();
	if(pid==0)
		proceso(i);
	}
	
	for(i=0;i<3;i++)
		pid = wait(&status);
	
	msgctl(idmsn,IPC_RMID,NULL);
}
