#include <sys/sem.h> 
#include <sys/types.h> 
#include <sys/ipc.h> 


//INICALIZAR EL SEMAFORO
int seminit(int idsem, int val)
{
	int sem_id;
	//Obtener un arreglo de semaforos (key, nsem, flags) 
	sem_id = semget((key_t)idsem,1,0666|IPC_CREAT); 
	semctl(sem_id,0,SETVAL,val);
	return(sem_id);
}

//WAIT SEMAFORO
void semwait(int idsem)
{
	struct sembuf s;
	s.sem_num = 0;
	s.sem_op = -1;
	//Undonea el semaforo cuando el proceso termina
	s.sem_flg = SEM_UNDO; 
	
	semop(idsem,&s,1);
	return;
}

//SIGNAL WAIT
void semsignal(int idsem)
{
	struct sembuf s;
	s.sem_num=0;
	s.sem_op=1;
	s.sem_flg=SEM_UNDO;
	
	semop(idsem,&s,1);
	return;
}

void semerase(int idsem)
{
	semctl(idsem,0,IPC_RMID,0);	// Eliminar el arreglo de semaforos
	return;
}

