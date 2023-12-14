#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXSTR 255
#define ARGCNT 5


int main(int argc, char *argv[])
{
char cmd1[MAXSTR];
char cmd2[MAXSTR];
char cmd3[MAXSTR];
char file[MAXSTR];

// Additional code goes here
char ** args = malloc( ARGCNT * sizeof(char*));
*(args + 0) = cmd1;
*(args + 1) = cmd2;
*(args + 2) = cmd3;
*(args + 3) = file;
*(args + 4) = NULL;
printf("cmd1->");
fgets(cmd1, sizeof(cmd1), stdin);
printf("cmd2->");
fgets(cmd2, sizeof(cmd2), stdin);
printf("cmd3->");
fgets(cmd3, sizeof(cmd3), stdin);
printf("file->");
fscanf(stdin, "%s", file);

printf("char %lu=%d\n",strlen(cmd1),cmd1[strlen(cmd1)]);
for (int i=0;i<ARGCNT;i++) printf("i=%d args[i]=%s\n",i,*(args + i));


int status = execvp(args[0], args);
printf("STATUS CODE=%d\n",status);



return 0;
}
