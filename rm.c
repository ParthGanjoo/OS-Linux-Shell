#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include<stdlib.h>

//rm command function
void main(int argc, char **argv)
{
    // "i" asks for confirmation before removing
    if(strcmp(argv[1], "-i") == 0)
    {   
        //if 2nd index is null after 1st index is not null
        if(argv[1] == NULL || argv[2] == NULL)
	    {
	        printf("Insufficient arguments\n");
	        return;
	    }

        for(int i = 2; argv[i]!=NULL; i++)
        {
            
            //asks for confirmation
            printf("rm: remove regular empty file '%s' (y/n)? ", argv[i]);
            char *answer = malloc(5 * sizeof(char));
            fgets(answer, 5, stdin);
            if(answer[0] == 'y' && answer[0] == 'Y')
            {
                return;
            }
            int x;
            x = remove(argv[i]);
            if(x == 0)
            {
                printf("%s: removed successfully\n", argv[i]);
            }
            else
            {
                printf("%s: removal cancelled\n", argv[i]);
            }

        }
    }

    //if 1st index is empty
    else if(argv[1] == NULL){
        printf("Insufficient arguments\n");
    }
    // "-d" removes empty directories
    else if(strcmp(argv[1], "-d") == 0)
    {

        if(argv[1] == NULL || argv[2] == NULL)
	    {
	        printf("Insufficient arguments\n");
	        return;
	    }

        for(int i = 2; argv[i] != NULL; i++)
        {
            
            int y;
            y = remove(argv[i]);
            if(y == 0)
            {
                printf("%s: removed successfully\n", argv[i]);
            }
            else
            {
                printf("%s: cannot remove file or directory\n", argv[i]);
            }
        }

    }
    //removes 2 at the same time with help of the same command
    else if (argv[1]!= NULL && argv[2]!=NULL){
        if(argv[1] == NULL)
        {
            printf("Insufficient arguments\n");
            return;
        }
        int x1, x2;
        x1 = remove(argv[1]);
        x2 = remove(argv[2]);
        if(x1 == 0 && x2 == 0)
        {
            printf("%s, %s: removed successfully\n", argv[1], argv[2]);
        }
        else
        {
            printf("%s, %s: cannot remove file or directory\n", argv[1], argv[2]);
        }
    
    }
    else if(argv[1]!=NULL){
        if(argv[1] == NULL)
        {
            printf("Insufficient arguments\n");
            return;
        }
        int z;
        z = remove(argv[1]);
        if(z == 0)
        {
            printf("%s: removed successfully\n", argv[1]);
        }
        else
        {
            printf("%s: cannot remove file or directory\n", argv[1]);
        }
    }
}
  
