#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define ERROR (-1)
#define PIPE_READ 0
#define PIPE_WRITE 1
#define STDIN 0
#define STDOUT 1

int main(){
  int pid[3] = {0};
  int pfd[2][2] = {0};
  int fd = 0;
  int i;

  if( pipe(pfd[0]) == ERROR ){
    perror("The following error occurred");
    exit(ERROR);
  }
  if( pipe(pfd[1]) == ERROR ){
    perror("The following error occurred");
    exit(ERROR); 
  }

  if( (fd = open("foo", O_CREAT | O_WRONLY, S_IREAD | S_IWRITE)) == ERROR ){
    perror("The following error occurred");
    exit(ERROR); 
  }

  if( (pid[0] = fork() ) == ERROR ){
    perror("The following error occurred");
    exit(ERROR); 
  }
  if( pid[0] == 0 ){
    close(STDOUT);
    dup(pfd[0][PIPE_WRITE]);
    for( i = 0 ; i < 2 ; i++ ){
      close(pfd[i][PIPE_READ]);
      close(pfd[i][PIPE_WRITE]);
    }
    close(fd);
    execlp( "ps", "ps", "aux", (char *)NULL);
  }
  else{
    if( (pid[1] = fork()) == ERROR ){
      perror("The following error occurred");
      exit(ERROR);
    }
    if( pid[1] == 0 ){
      close(STDIN);
      dup(pfd[0][PIPE_READ]);
      close(STDOUT);
      dup(pfd[1][PIPE_WRITE]);
      for( i = 0 ; i < 2 ; i++ ){
        close(pfd[i][PIPE_READ]);
        close(pfd[i][PIPE_WRITE]);
      }
      close(fd);
      execlp("grep", "grep", "u99098", (char *)NULL );
    }
    else{
      if( (pid[2] = fork()) == ERROR ){
        perror("The following error occurred");
        exit(ERROR);
      }
      if( pid[2] == 0 ){
        close(STDIN);
        dup(pfd[1][PIPE_READ]);
        close(STDOUT);
        dup(fd);
        for( i = 0 ; i < 2 ; i++ ){
          close(pfd[i][PIPE_READ]);
          close(pfd[i][PIPE_WRITE]);
        }
        close(fd);
        execlp("wc", "wc", (char *)NULL);
      }
      else{
        for( i = 0 ; i < 2 ; i++ ){
          close(pfd[i][PIPE_READ]);
          close(pfd[i][PIPE_WRITE]);
        }
        close(fd);
        wait( (int *)0 );
        wait( (int *)0 );
        wait( (int *)0 );
      }
    }
  }

  return 0;
}
