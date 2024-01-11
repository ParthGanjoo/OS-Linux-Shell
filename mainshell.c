#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

char *copy[1000];

// reads command
char *readcommand(){
    char *temp;
    temp = malloc(1000 * sizeof(char));
    fgets(temp, 1000, stdin);
    if (temp == NULL){
        temp = "Input error";
        return temp;
    }
    int i = 0;
    while (temp[i]!='\n'){
        i++;
    }
    if (temp[0] == '\n'){
        return temp;
    }

    temp[i] = '\0';
    return temp;
}

//parses commands
char **splitcommand(char *commandstr){
    char *tkn;
    char ** tkns;
    int i = 0;
    tkns = malloc(1000 * sizeof(char *));
    tkn = strtok(commandstr, " \n");
    while (tkn!=NULL){
        tkns[i] = tkn;
        i++;
        tkn = strtok(NULL, " \n");
    }
    if (tkn == NULL){
        tkns[i] = tkn;
        i++;
        tkn = strtok(NULL, " \n");
    }
    tkns[i] = NULL;
    return tkns;
}

//cd command function
void cd(char **command){
    char s[100];

    //cd should have something in its first index
    if (command[1] == NULL){
        printf("Incorrect command\n");
        return;
    }
    else if(command[2] != NULL){
        printf("Too many arguments\n");
    }
    // ".." goes to previous directory
    else if (strcmp(command[1], "..") == 0){
        chdir("..");
        printf("%s \n ", getcwd(s, sizeof(s)));
    }

    // "/" goes to root directory
    else if (strcmp(command[1], "/") == 0){
        chdir("/");
        printf("%s \n ", getcwd(s, sizeof(s)));
    }
    
    else if (chdir(command[1]) !=0){
        printf("Directory not found\n");
        return;
    }

    
}

//echo command function
void echo(char **command)
{
    // prints extra line if no command at first index
    if(command[1] == NULL)
    {
        printf("\n");
        return;
    }
    // "-n" omits a new line
    else if (strcmp(command[1], "-n") == 0){
        for (int i = 2; command[i]!=NULL; i++){
            printf("%s ", command[i]);
        }
    }
    // next command starts from new line
    else{
        for (int i = 1; command[i]!=NULL; i++){
            printf("%s ", command[i]);
        }
        printf("\n");
    }
}

// pwd command function
void pwd(char **command)
{
    char wd[1000];

    // gives working directory
    if (command[1] == NULL){
        printf("%s \n", getcwd(wd, sizeof(wd)));

    }
    // "-L" gives working directory
    else if (strcmp(command[1], "-L") == 0){
        printf("%s \n", getcwd(wd, sizeof(wd)));
    }
    // "-P" gives working directory
    else if (strcmp(command[1], "-P") == 0){
        printf("%s \n", getcwd(wd, sizeof(wd)));
    }
    // any command other than -L and -P will also work as pwd only
    else {
        printf("%s \n", getcwd(wd, sizeof(wd)));
    }    
}

void internalcommand(char **command)
{

    if(strcmp(command[0], "echo") == 0){
        echo(command);
    }
    else if (strcmp(command[0], "pwd") == 0){
        pwd(command);
    }
    else if (strcmp(command[0], "cd") == 0){
        cd(command);
    }
}

// pthread functions start
void *rundatepthread(void *arg){
    char *path=(char*)malloc(sizeof(char)*100);
    strcpy(path,"/home/parth/Desktop/date ");
    int i=1;
    // cmd={"mkdir","fol1"};
    while(copy[i]!=NULL){
        strcat(path, copy[i]);
        strcat(path," ");
        i++;
    }
    //printf("%s\n",path);
    system(path);
    return NULL;
}
void makedatepthread(){
    pthread_t newthread;
    pthread_create(&newthread, NULL, rundatepthread, NULL);
    pthread_join(newthread, NULL);
}

void *runlspthread(void *arg){
    char *path=(char*)malloc(sizeof(char)*100);
    strcpy(path,"/home/parth/Desktop/ls ");
    int i=1;
    // cmd={"mkdir","fol1"};
    while(copy[i]!=NULL){
        strcat(path, copy[i]);
        strcat(path," ");
        i++;
    }
    //printf("%s\n",path);
    system(path);
    return NULL;
}
void makelspthread(){
    pthread_t newthread;
    pthread_create(&newthread, NULL, runlspthread, NULL);
    pthread_join(newthread, NULL);
}

void *runmkdirpthread(void *arg){
    char *path=(char*)malloc(sizeof(char)*100);
    strcpy(path,"/home/parth/Desktop/mkdir ");
    int i=1;
    // cmd={"mkdir","fol1"};
    while(copy[i]!=NULL){
        strcat(path, copy[i]);
        strcat(path," ");
        i++;
    }
    //printf("%s\n",path);
    system(path);
    return NULL;
}
void makemkdirpthread(){
    pthread_t newthread;
    pthread_create(&newthread, NULL, runmkdirpthread, NULL);
    pthread_join(newthread, NULL);
}

void *runrmpthread(void *arg){
    char *path=(char*)malloc(sizeof(char)*100);
    strcpy(path,"/home/parth/Desktop/rm ");
    int i=1;
    // cmd={"rm","fol1"};
    while(copy[i]!=NULL){
        strcat(path, copy[i]);
        strcat(path," ");
        i++;
    }
    //printf("%s\n",path);
    system(path);
    return NULL;
}
void makermpthread(){
    pthread_t newthread;
    pthread_create(&newthread, NULL, runrmpthread, NULL);
    pthread_join(newthread, NULL);
}

void *runcatpthread(void *arg){
    char *path=(char*)malloc(sizeof(char)*100);
    strcpy(path,"/home/parth/Desktop/cat ");
    int i=1;
    // cmd={"cat","fol1"};
    while(copy[i]!=NULL){
        strcat(path, copy[i]);
        strcat(path," ");
        i++;
    }
    //printf("%s\n",path);
    system(path);
    return NULL;
}
void makecatpthread(){
    pthread_t newthread;
    pthread_create(&newthread, NULL, runcatpthread, NULL);
    pthread_join(newthread, NULL);
}
// pthread functions end

void externalcommand(char **command){

    pid_t processid;
    int status;
    if(strcmp(command[0], "date") == 0)
    {
        processid = fork();
        
        if(processid == 0)
        {
            //char *args[] = {"date", NULL};
            execv("/home/parth/Desktop/date", command);
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
    else if(strcmp(command[0], "ls") == 0)
    {
        processid = fork();
        
        if(processid == 0)
        {
            //char *args[] = {"ls", NULL};
            execv("/home/parth/Desktop/ls", command);
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
    else if(strcmp(command[0], "mkdir") == 0)
    {
        processid = fork();
        
        if(processid == 0)
        {
            //char *args[] = {"mkdir", NULL};
            execv("/home/parth/Desktop/mkdir", command);
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
    else if(strcmp(command[0], "rm") == 0)
    {
        processid = fork();
        
        if(processid == 0)
        {
            //char *args[] = {"mkdir", NULL};
            execv("/home/parth/Desktop/rm", command);
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
    else if(strcmp(command[0], "cat") == 0)
    {
        processid = fork();
        
        if(processid == 0)
        {
            //char *args[] = {"mkdir", NULL};
            execv("/home/parth/Desktop/cat", command);
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
}

int main(){
    char *commandstr;
    char **commandarr;
    char **command;
    
    
    while(1){
        printf(">> ");
        commandstr = readcommand();
        if (strcmp(commandstr,"\0")==0){
            // puts(commandstr);
            commandarr = splitcommand(commandstr);
            internalcommand(commandarr);

            int k = 0;
            int j = 0;
            while (commandarr[k] != NULL){
                if (strcmp(commandarr[k], "&t") == 0){
                    j++;
                }
                k++;
            }
            if (j == 0){
                externalcommand(commandarr);
            }
            
            else if (j == 1){
                int k = 0;
                while (commandarr[k] != NULL){
                    if (strcmp(commandarr[k], "&t") == 0){
                        commandarr[k] = NULL;
                    }
                    k++;
                }
                k = 0;
                while (commandarr[k]!=NULL){
                    copy[k] = commandarr[k];
                    k++;
                }

                if (strcmp(copy[0], "date") == 0){
                    makedatepthread();
                    
                }
                else if (strcmp(copy[0], "ls") == 0){
                    makelspthread();
                    
                }
                else if (strcmp(copy[0], "mkdir") == 0){
                    makemkdirpthread();
                    
                }
                else if (strcmp(copy[0], "cat") == 0){
                    makecatpthread();
                    
                }
                else if (strcmp(copy[0], "rm") == 0){
                    makermpthread();
                    
                }
            }
        }
        else{
            continue;
        }
        

    }
}