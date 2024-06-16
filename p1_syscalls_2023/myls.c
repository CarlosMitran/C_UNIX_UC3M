//P1-SSOO-22/23

#include <stdio.h>		// Header file for system call printf
#include <unistd.h>		// Header file for system call gtcwd
#include <sys/types.h>	// Header file for system calls opendir, readdir y closedir
#include <dirent.h>
#include <string.h>
#define PATH_MAX 4096

int main(int argc, char *argv[])
{
	//If less than two arguments (argv[0] -> program, argv[1] -> file to process) print an error y return -1
	if(argc > 2)
	{	
		printf("Too many arguments\n");
		return -1;
	}
	DIR *dir;
	char *dir_path;
	struct dirent *n;
	char cwd[PATH_MAX];
	int var;
	if (argc == 1){
		if ((dir_path = getcwd(cwd, sizeof(cwd))) == NULL){
			printf("Error while trying to open");
			return -2;
		}
		if ((dir = opendir(dir_path)) == NULL){
			printf("Something went wrong 1");
			return -3;
		}
	}
	else{
		if ((dir = opendir(argv[1])) == NULL){
			printf("Something went wrong 2");
			return -4;
		}

		
	}

	while ((n = readdir(dir)) != NULL){
		printf("%s\n", n->d_name);
	}
	if ((var= closedir(dir)) < 0){
		printf("error while closing");
		return -5;
	}
	return 0;
}

