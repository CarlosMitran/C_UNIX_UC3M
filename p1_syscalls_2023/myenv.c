//P1-SSOO-22/23
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#define N 1


int main(int argc, char *argv[])
{
    int fileIn, fileOut, n;

	char buf[N];


    /* If less than two arguments (argv[0] -> program, argv[1] -> file to save environment) print an error y return -1 */
    if(argc < 3)
    {
    	printf("Too few arguments\n");
    	return -1;
    }
    if(argc > 3)
    {
        printf("Too many arguments\n");
        return -1;
    }
    if ((fileIn = open("env.txt", O_RDONLY)) < 0||(fileOut= open(argv[2], O_WRONLY)) < 0)
	{
		printf("File can't be oppened\n");
		return -1;	
	}

    int counter;
    counter = 0;
    bool CHECK;
    CHECK = true;
    bool COPIAR = false;

    while ((n = read(fileIn, buf, N)) > 0){
        if (COPIAR == false){
            if (CHECK == false){                // Check = false means we have already now 
                if (buf[0] == '\n'){            // we are at incorrect line so we won't even compare
                    CHECK = true;
                    counter = 0;
                }
                continue;
            }       
            if (buf[0] == '='){             // If we reach this point it means we found it, we proceed to copy the line
                printf("Hemos encontrado, ahora copiamos\n");
                lseek(fileIn, -(counter+1), SEEK_CUR); // We set the pointer at The first position of the line, as we know length variable length (counter)
                COPIAR = true;
                
            }
            if (buf[0] != argv[1][counter]){ // If we find a discrepancy we already know it is not correct so no need to check (Check = false)
                CHECK = false;
            }
            counter++;                    // add 1 to the counter for the string
        }
        else{
            if (buf[0] == '\n'){            // Copy everything until we find the end of the line
                CHECK = true;               //Once we found it reset everything to start checking again
                COPIAR = false;
            }
            if (write(fileOut, buf, n) < n) {
                return -1;
                }
        }
    }
    close(fileIn);
    close(fileOut);
    printf("finished\n");
    return 0;
}
 
