#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

// ls command function


int main(int argc, char **argv){
	DIR *d;
	struct dirent *dir;
	d = opendir(".");
	if (argv[1] == NULL){
		//for just "ls"
		if (d){
			while ((dir = readdir(d))!= NULL){
				printf("%s\t", dir->d_name);
			}
		printf("\n");
		closedir(d);
	}
}
	else if(argv[2] != NULL){
		printf("Too many arguments\n");
	}
	// "-m" gives commas between everything thats present
	else if(strcmp(argv[1], "-m") == 0){
		if (d){
			while ((dir = readdir(d))!= NULL){
				printf("%s, ", dir->d_name);
		}
		printf("\n");
		closedir(d);
	}
	}
	// "-1" gives next line after everything thats present
	else if(strcmp(argv[1], "-1") == 0){
		if (d){
			while ((dir = readdir(d))!= NULL){
				printf("%s\n", dir->d_name);
		}
		printf("\n");
		closedir(d);
	}
	}
	//if anything other than ls, ls -1, ls -m is given as command
	else{
		printf("Incorrect argument\n");
	}

}
