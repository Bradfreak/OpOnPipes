#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#define MAX   1000000

int main(){
    int p[2];

    if(pipe(p) < 0){
        exit(1);
    }

   char temp;
   FILE *fp;
   char str[MAX], filename[MAX];

   scanf("%s", filename);

   fp = fopen(filename , "r");
   if(fp == NULL) {
      perror("Error opening file");
      return(-1);
   }

   int f = fork(), len;
   if(f != 0){
       close(p[0]);
       while( fgets (str, MAX, fp)!=NULL ) {
           len = strlen(str);
           write(p[1], str, len);
       }
       close(p[1]);
       waitpid(f, NULL, 0);
   }
   else{
       close(p[1]);
       while(read(p[0], &temp, 1) > 0){
           printf("%c", temp);
       }
       close(p[0]);
   }
   fclose(fp);
   exit(0);
}
