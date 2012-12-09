#include <stdio.h>

#define ERROR (-1)
#define PIPE_READ 0
#define PIPE_WRITE 1
#define STDIN 0
#define STDOUT 1

int main(){
  int pid[3] = {0};
  int pfd[2][2] = {0};
  
  if( pipe(pfd[0]) == ERROR ){
    perror("The following error occurred");
    exit(ERROR);
  }
  if( pipe(pfd[1]) == ERROR ){
    perror("The following error occurred");
    exit(ERROR); 
  }
  
  if( (pid[0] = fork() ) == ERROR ){
    perror("The following error occurred");
    exit(ERROR); 
  }
  if( pid[0] == 0 ){
  
  }
  else{
    if( (pid[1] = fork()) == ERROR ){
    }
  }

  return 0;
}
