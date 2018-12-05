#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main(){
  char input[200];

  key_t key;
  int shmid;
  char *data;

  key = ftok("share.c", 'R');
  shmid = shmget(key, 200, 0644);
  data = shmat(shmid, (void *)0, 0);

  if(shmid!=-1){
    printf("shared contents: %s\n", data);
  }
  else{
    shmid = shmget(key, 200, 0644 | IPC_CREAT);
    data = shmat(shmid, (void *)0, 0);
    printf("shared memory just created! Chill!\n");
  }

  printf("Do you wanna change this data? (y/n): ");
  scanf ("%s", input);

  if(!strcmp(input,"y")){
    printf("Enter you string: ");
    scanf("%s", input);
    printf("%s\n", input);
    strncpy(data, input, 200);
  }

  printf("Do you wanna delete this segment? (y/n): ");
  scanf ("%s", input);

  if(!strcmp(input,"y")){
    printf("Deleted! :(\n");
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
  }

  return 0;
}
