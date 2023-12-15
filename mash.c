#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>



#define MAXSTR 255
#define ARGCNT 5

//counts the number of white spaces in a string and adds 1 to represent words counted
int whiteSpaceCounter(char * line){
    int count = 0;
    for (int i = 0; i < strlen(line); i++){
        if (line[i] == ' '){
            count++;
        }
    }
    //number of words = number of spaces + 1
    return count+1;
}


//parses a string into an array of strings
char ** parse(char * line, char * file){
   
    //remember dummy, space at the end n + 2 not 1

    char ** args = malloc( (whiteSpaceCounter(line)+1)* sizeof(char*));
    //source of much of my frustration, fgets was capturing newline and failing execvp because of it
    char * token = strtok(line, " \n");
    int i = 0;
    while (token != NULL){
        args[i] = token;
        token = strtok(NULL, " \n");
        i++;
    }

    args[i] = file;
    printf("file name at args[%i]=%s\n",i, args[i]);
    args[i+1] = NULL;
    return args;
}


int main(int argc, char *argv[])
{
    char cmd1[MAXSTR];
    char cmd2[MAXSTR];
    char cmd3[MAXSTR];
    char file[MAXSTR];

    // Additional code goes here

//build variables to store user input
printf("cmd1->");
fgets(cmd1, sizeof(cmd1), stdin);
printf("cmd2->");
fgets(cmd2, sizeof(cmd2), stdin);
printf("cmd3->");
fgets(cmd3, sizeof(cmd3), stdin);
printf("file->");
fscanf(stdin, "%s", file);

//build char arrays to store parsed user input
char ** command1 = parse(cmd1 , file);
char ** command2 = parse(cmd2 , file);
char ** command3 = parse(cmd3,  file);

//print parsed user input of command 1
for (int i = 0; command1[i] != NULL; i++) {
    printf("command1[%d] = %s\n", i, command1[i]);
}



//fork original parent process by nesting 3 levels. Use wait() to wait for porcesses to exit/

int process1 = fork();
if (process1 < 0){
    printf("fork failed\n");
    exit(1);
}
else if (process1 == 0){
    //child process 1
    int process2 = fork();
    if (process2 < 0){
        printf("fork failed\n");
        exit(1);
    }
    else if (process2 == 0){
        //child process 2
        int process3 = fork();
        if (process3 < 0){
            printf("fork failed\n");
            exit(1);
        }
        else if (process3 == 0){
            //child process 3
            printf("child process 3\n");
            int status = execvp(command3[0], command3);
            printf("CMD3:[SHELL 3] STATUS CODE=%d\n", status);
            exit(1);
        }
        else{
            //parent process 2
            printf("parent process 2\n");
            wait(NULL);
            int status = execvp(command2[0], command2);
            printf("CMD2:[SHELL 2] STATUS CODE=%d\n", status);
            exit(1);
        }
    }
    else{
        //parent process 1
        printf("parent process 1\n");
        wait(NULL);
        int status = execvp(command1[0], command1);
        printf("CMD1:[SHELL 1] STATUS CODE=%d\n", status);
        exit(1);
    }
}
else{
    //parent process
  
    wait(NULL);
    printf("parent process\n");
    printf("file=%s\n",file);
    exit(1);

}

return 0;
}

