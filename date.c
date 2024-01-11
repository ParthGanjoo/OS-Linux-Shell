#include <stdio.h>
#include <time.h>
#include <string.h>

//date command function
int main(int argc, char **argv){
	time_t t = time(NULL);

	// if 1st index is null, gives ist and date
	if (argv[1] == NULL){
		struct tm *ist = localtime(&t);
		printf("%s", asctime(ist));
	}
	else if(argv[2] != NULL){
		printf("Too many arguments\n");
	}
	// if 1st index is "-u" it gives utc and date
	else if (strcmp(argv[1], "-u") == 0){
		struct tm *utc = gmtime(&t);
		printf("%s", asctime(utc));
	}
	// if 1st index is "-I" it gives date only
	else if (strcmp(argv[1], "-I") == 0){
		struct tm tm = *localtime(&t);
		printf("%d-%d-%d\n", tm.tm_year + 1900, tm.tm_mon+1, tm.tm_mday);
	}
	// if command is anything other than date, date -u, date -I, then error given
	else{
		printf("Invalid argument\n");
	}
}
