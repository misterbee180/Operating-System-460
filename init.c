#include "type.h"
char* loginfiles[3] = {"login /dev/tty0", "login /dev/ttyS0","login /dev/ttyS1"};
int childpid[3]= {0};
int main(argc, argv) int argc; char* argv[];
{
	int pid = 0;
	int exitValue = 0;
	int i = 0;
	char buf[60];

	int stdin = open("dev/tty0", O_RDONLY);
	int stdout = open("dev/tty0", O_WRONLY);

	printf("Entering Hao's init\n");
	//getc();
	//getc();
	
	// Fork 3 child for login process
	for(i = 0; i < 3; i++)
	{
		pid = fork();
		if(pid == 0)
		{
			//printf(loginfiles[i]);
			exec(loginfiles[i]);
		}		
		childpid[i] = pid;
	}

/************ Critical Region ********/
	//printf("hi\n");
/**************************************/

	// Only P1 can reach here
	while(1)
	{

		pid = wait(&exitValue);
		for(i = 0; i < 3; i++)
		{
			if(pid == childpid[i])
			{
				printf("Login P%d Died with exit value %d, Forking Antoher\n",pid,exitValue);
				pid = fork();
				if(pid == 0)
				{
					exec(loginfiles[i]);
				}
				childpid[i] = pid;
				break;
			}
			//printf("Some process P%d died with ev %d\n",pid,exitValue);
		}
	}
		

		

}
