#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAXSTR 255
#define ARGCNT 5

//counts the number of white spaces in a string
int whiteSpaceCounter(char * line){
    int count = 0;
    for (int i = 0; i < strlen(line); i++){
        if (line[i] == ' '){
            count++;
        }
    }
    return count;
}
//parses a string into an array of strings
char ** parse(char * line){
    //print whiteSpaceCounter(line);
    int counter = whiteSpaceCounter(line);
    printf("counter=%d\n",counter);
    char ** args = malloc( (whiteSpaceCounter(line)+1) * sizeof(char*));
    char * token = strtok(line, " ");
    int i = 0;
    while (token != NULL){
        args[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL;
    return args;
}


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
char ** command1 = parse(cmd1);
printf("cmd2->");
fgets(cmd2, sizeof(cmd2), stdin);
char ** command2 = parse(cmd2);
printf("cmd3->");
fgets(cmd3, sizeof(cmd3), stdin);
char ** command3 = parse(cmd3);
printf("file->");
fscanf(stdin, "%s", file);

printf("char %lu=%d\n",strlen(cmd1),cmd1[strlen(cmd1)]);
for (int i=0;i<ARGCNT;i++) printf("i=%d command1[i]=%s\n",i,*(command1 + i));


int status = execvp(command1[0], command1);
printf("STATUS CODE=%d\n",status);



return 0;
}

