#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

pid_t processid;
int status;

// cat command function
void main(int argc, char **argv){
	// if 1st index is null
	if (argv[1] == NULL){
		char line[10000];
		while(1){
			fgets(line, 10000, stdin);
			if (strcmp(line, "exit") == 0){
				processid = fork();
        
		        if(processid == 0)
		        {
		            //char *args[] = {"mkdir", NULL};
		            execv("/home/parth/Desktop/mainshell", argv);
		        }
		        else if(processid < 0)
		        {
		            printf("Error in fork\n");
		            return;
		        }
		        else if(processid > 0)
		        {
		            processid = waitpid(processid, &status, 0);
		            if ((processid ) == -1){
		                perror("wait() error");
		            }
		        }
			}
			printf("%s\n", line);
		}free(line);

	}
	else if(argv[2] != NULL){
		printf("Too many arguments\n");
	}
	// if 1st index is "-n" prints every statement with its line count
	else if (strcmp(argv[1], "-n") == 0){
		int count = 1;
		char line[10000];
		while(1){
			fgets(line, 10000, stdin);
			printf("\t%d %s\n", count, line);
			count++;
		}
		free(line);
	}
	// if 1st index is "-b" prints every statement with its line count, excluding the count of the statement that is null
	else if (strcmp(argv[1], "-b") == 0){
		int count = 1;
		char line[1000];
		while(1){
			int i = 0;
			fgets(line, 1000, stdin);
			if (line[i] == '\n' || line[i] == ' '){
				
				printf("\t%s\n", line);
				continue;
			}
			else{
				printf("\t%d %s\n", count, line);
			}
			count++;
			i++;
			
		}
		free(line);
	}
	// if command is anything other than cat, cat -b and cat -n, it is not allowed
	else {
		printf("Incorrect command\n");
	}
}