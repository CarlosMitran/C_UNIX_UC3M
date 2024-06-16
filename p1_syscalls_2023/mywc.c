//P1-SSOO-22/23
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#define N 1

int main(int argc, char *argv[])
{
	int fd, n;
	char buf[N];
	int lines = 0;
	int words = 0;
	int bytes = 0;
	//If less than two arguments (argv[0] -> program, argv[1] -> file to process) print an error y return -1
	if(argc < 2)
	{
		printf("Too few arguments\n");
		return -1;
	}
	if(argc > 2)
	{	
		printf("Too many arguments\n");
		return -1;
	}
	
	if ((fd= open(argv[1], O_RDONLY)) < 0)
	{
		printf("File can't be oppened\n");
		return -1;	
	}
	while ((n = read(fd, buf, N)) > 0){
		if (buf[0] == '\n')
		{
			lines ++;
			words ++;
			bytes ++;	
		} 
		else if (buf[0] == '\t' || buf[0] == ' ')
		{
			words ++;
			bytes ++;
		}
		else
		{
			bytes ++;
		}
	}
	if (n < 0){
			printf("An error has occured");
			return -1;
		}
	if (bytes > 0){   // If file is not empty we add the last word that is not included
		words ++;

	}


	close(fd);
	printf("%d %d %d %s\n", lines, words, bytes, argv[1]);
	return 0;
}

