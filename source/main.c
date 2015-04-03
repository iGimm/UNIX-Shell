/*
 *
 * Shell
 * Created by iGimm on 18/03/15.
 *
 * This assignment is to create
 * a UNIX mini-shell based on fork & execlp.
 *
 * This shell should be capable of running
 * UNIX commands with up to four parameters.
 *
 *
 *
 * If a command uses less that four parameters
 * you can ignore the space allocated for the rest.
 *
 * If a command uses more than four parameters
 * we will truncate it to four parameters.
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAXLINE 4096

int main(void){
    char	buf[MAXLINE];
    char	dest[MAXLINE];
    pid_t	pid;
    int		status;
    
    printf(">");                                  /* print prompt */
    while (fgets(buf, MAXLINE, stdin) != NULL) {  /* Read and store the input into the buffer */
        if(buf[strlen(buf)-1] == '\n'){
            buf[strlen(buf)-1] = '\0';            /* replace newline with null */
            
        }
        
        if((pid = fork()) <0){         /* if fork() <0 there was no enough memory to create the child process*/
            printf("fork error ");
            exit(1);
            
        }else if(pid == 0){            /* child process was successfully created */
			
            char *tok = NULL;
			char *cmd[4];
            int i = 0;
			tok = strtok(buf, " ");    /* start tokenizing buf with DELIM " "*/
			
			while (tok) {
				cmd[i] = strdup(tok);  /* each token is stored into one position of the array cmd */
				tok    = strtok(NULL, " ");
				i++;
				
			}
			
			if(i > 4){                 /* if there are more than four arguments to be sent to exec we notify the user */
				printf("You exceded the number of parameters.\n");
			}
            
            switch (i-1) {             /* Switch sentence help to know how many arguments are sent to exec */
                case 0:
                    execlp(buf, " ", (char *)0);
                    printf("couldn't execute: %s \n", buf);
                    exit(127);
                    break;
                case 1:
                    execlp(buf,cmd[0],cmd[1], (char *)0);
                    printf("couldn't execute: %s \n", buf);
                    exit(127);
                    break;
                case 2:
                    execlp(buf, cmd[0], cmd[1], cmd[2], (char *)0);
                    printf("couldn't execute: %s \n", buf);
                    exit(127);
                    break;
                case 3:
                    execlp(buf, cmd[0],cmd[1],cmd[2],cmd[3], (char *)0);
                    printf("couldn't execute: %s \n", buf);
                    exit(127);
                    break;
                    
                default:
                    break;
            }
            
            exit(127);
        }
        
        if((pid = waitpid(pid, &status, 0)) < 0){ /* parent process */
            printf("waitpid error ");
            exit(1);
            
        }
        printf("> ");
    }
    exit(0);
}

