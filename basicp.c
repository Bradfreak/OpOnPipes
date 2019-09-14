#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAX   1000000

int main(){
    int p[2];

    if(pipe(p) < 0){
        exit(1);
    }

   char temp[1];
   char eofc[1];
   int fp, i = 2;
   char str[1], filename[MAX];
   char ln[20];
   printf("Enter the filename\n");
   scanf("%s", filename);

   fp = open(filename , O_RDONLY);
   if(fp == -1) {
      perror("Error opening file");
      return(-1);
   }

   int f = fork();
   if(f != 0){
       close(p[0]);
       while( read(fp, &str, 1) > 0){
           write(p[1], str, 1);
       }
       close(p[1]);
       waitpid(f, NULL, 0);
   }
   else{
       close(p[1]);
       while(read(p[0], &temp, 1) > 0){
           write(1, temp, 1);
       }
       close(p[0]);
   }
   close(fp);
   exit(0);
}
