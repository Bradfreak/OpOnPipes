#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>


int main() {
  int fp, i = 2;
  char filename[20], fch[1], eofc[1];
  char ln[20];

  printf("Enter the filename \n");
  scanf("%s", filename);

  fp = open(filename, O_RDONLY);
  if(fp == -1) {
     perror("Error opening file");
     return(-1);
  }

  int fpi[2];

  if ( pipe(fpi) == -1) {
    printf("Pipe creation failed\n");
    exit(2);
  }

  int pid = fork();

  if(pid > 0) {
    close(fpi[0]);
    dup2(fpi[1], 1);
    while(read(fp, &fch, 1) > 0) {
      if(fch[0] < 123 && fch[0] > 96) {
        fch[0] -= 32;
      }
      write(1, fch, 1);
    }
    close(fpi[1]);
    close(fp);
  }
  else{
    close(fpi[1]);
    dup2(fpi[0], 0);
    while(read(0, fch, 1) > 0){
      write(1, "1.", 2);
      write(1, fch, 1);
    }
    while(read(0, fch, 1) > 0){
      write(1, fch, 1);
      if(fch[0] == '\n'){
        if(read(0, eofc, 1) > 0) {
          sprintf(ln, "%d.", i);
          write(1, ln, (i/10)+2);
          write(1, eofc, 1);
          i++;
        }
        else {
          break;
        }
      }
    } 
    close(fpi[0]); 
    exit(0);
  }
}
