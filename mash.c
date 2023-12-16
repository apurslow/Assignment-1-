// EXTRA CREDIT FEATURES: EC1 implemented

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>



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
    //printf("file name at args[%i]=%s\n",i, args[i]);
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

// //print parsed user input of command 1
// for (int i = 0; command1[i] != NULL; i++) {
//     printf("command1[%d] = %s\n", i, command1[i]);
// }



//measure each command's length of execution time
clock_t start1, end1, start2, end2, start3, end3;



//fork original parent process by nesting 3 levels. Use wait() to wait for porcesses to exit/
//initialize start1
start1 = clock();
int process1 = fork();
//if less than 0, fork failed
if (process1 < 0){
    printf("fork failed\n");
    exit(1);
}
//if 0, child process 1
else if (process1 == 0){
    //child process 1
    start2 = clock();
    //print out clock time of start1
   
    int process2 = fork();
    if (process2 < 0){
        printf("fork failed\n");
        exit(1);
    }
    else if (process2 == 0){
        //child process 2
        start3 = clock();
        int process3 = fork();
        if (process3 < 0){
            printf("fork failed\n");
            exit(1);
        }
        else if (process3 == 0){
            //child process 3
            
            //printf("child process 3\n");
            int status = execvp(command3[0], command3);
            printf("CMD3:[SHELL 3] STATUS CODE=%d\n", status);
            exit(1);
        }
        else{
            //parent process 2
            //printf("parent process 2\n");
            wait(NULL);
            end3 = clock();
            printf("process 3 id = %d\n", process3);
            int status = execvp(command2[0], command2);
            printf("CMD2:[SHELL 2] STATUS CODE=%d\n", status);
            exit(1);
        }

        
    }
    else{
        //parent process 2
        //printf("parent process 1\n");
        wait(NULL);
        end2 = clock();
        printf("process 2 id = %d\n", process2);
        int status = execvp(command1[0], command1);
        printf("CMD1:[SHELL 1] STATUS CODE=%d\n", status);
        exit(1);
    }
    
    
    
}
//if greater than 0, parent process 1
else{
    //parent process 1
    wait(NULL);
    end1 = clock();
    printf("process 1 id = %d\n", process1);
    //exit(1);

}
    
    
    double total1 = ((double) (end1 - start1)) / (CLOCKS_PER_SEC/1000);
    double total2 = ((double) (end2 - start1)) / (CLOCKS_PER_SEC/1000);
    double total3 = ((double) (end3 - start1)) / (CLOCKS_PER_SEC/1000);
    double totalExecutionTime = total1 + total2 + total3;

    printf("CMD1:[SHELL 1] TOTAL TIME= %f ms\n", total1);
   
    printf("CMD2:[SHELL 2] TOTAL TIME= %f ms\n", total2);
   
    printf("CMD3:[SHELL 3] TOTAL TIME= %f ms\n", total3);
   
    printf("TOTAL EXECUTION TIME= %f ms\n", totalExecutionTime);

return 0;
}

