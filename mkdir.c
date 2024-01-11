#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include<string.h>
#include<stdio.h>

//mkdir command function
void main(int argc, char *argv[])
{   
    // error if first index is empty
    if (argv[1] == NULL){
        printf("Insufficient arguments\n");
    }

    // "-v" displays message for directories created
    else if(strcmp(argv[1], "-v") == 0)
    {
        if(argv[1] == NULL || argv[2] == NULL)
        {
            printf("Insuffient arguments\n");
            return;
        }
        for(int i = 2; argv[i] != NULL; i++)
        {
            int c;
            c = mkdir(argv[i], 0777);
            if (c!=0){
                perror("mkdir");
            }
            else{
                printf("mkdir: created directory '%s' \n", argv[i]);
            }
        }
    }
    else
    {

        for(int i = 1; argv[i] != NULL; i++)
        {
            if(argv[1] == NULL)
        {
            printf("Insuffient arguments\n");
            return;
        }
        // created directories without giving completiton statement
        for(int i = 1; argv[i] != NULL; i++)
        {
            int c;
            c = mkdir(argv[i], 0777);
            if (c!=0){
                perror("mkdir");
            }
            else{
                return;
            }
        }
        }
    }
}