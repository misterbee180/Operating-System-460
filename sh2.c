#include "type.h"
#include <string.h>

char command[256];
char* pcommand[20];
int token = 0;
char buf[256];

void buildbuf(i,j) int i; int j;
{
	strcpy(buf,pcommand[++i]);
	while( i < j-1 )
	{
		strcat(buf," ");
		strcat(buf,pcommand[++i]);
	}
}

int check_redirect(i,j) int i; int j;
{
	int k = 0;
	for(k = i+1; k <= j; k++)
	{
		if(!(strcmp(pcommand[k],">")))
		{
			//sleep();
			//printf("hi\n");
			close(1);
			open(pcommand[k+1], O_WRONLY|O_CREAT);
			return k;
		}
		else if(!(strcmp(pcommand[k],">>")))
		{
			close(1);
			open(pcommand[k+1], O_APPEND|O_WRONLY|O_CREAT);
			return k;
		}
		else if(!(strcmp(pcommand[k],"<")))
		{
			close(0);
			open(pcommand[k+1], O_RDONLY);
			return k;
		}
	}
	return k;
}

void run2(i,j) int i; int j;
{
	int direct_position = 0;
	direct_position = check_redirect(i,j);	
	buildbuf(i,direct_position);
//	printf("%s\n",buf);
	exec(buf);
}

int check_pipe(i) int i;
{
	while(i >= 0)
	{
		if(!strcmp(pcommand[i],"|"))
			return i; 
		i--;
	}
	return i;
}

void run1(i) int i;
{
	int pipe_position = 0;
	int pid = 0;	
	int pd[2];

	pipe_position = check_pipe(i);
	if(pipe_position == -1)
	{
		run2(-1,i);
	}
	else
	{
		pipe(pd);
		pid = fork();
		if(pid)
		{
			close(pd[1]);
			close(0);
			dup2(pd[0],0);
			run2(pipe_position,i);
		}
		else
		{
			close(pd[0]);
			close(1);
			dup2(pd[1],1);
			run1(pipe_position-1);
		}
		
	}
}
void printH()
{
	printf("************************* Menu ****************************\n");
	printf("*   ls   cd   pwd   cat   more   cp   mv   mkdir   rmdir  *\n");
	printf("*  grep  ps                                               *\n");
	printf("***********************************************************\n");
}
int tokenize(command) char* command;
{
	pcommand[token] = strtok(command," ");
	
	token ++;

	while((pcommand[token] = strtok(NULL," ")))
		token++;

}
int main(argc,argv)int argc; char* argv[];
{
	int i = 0;
	int status = 0;
	int pid = 0;

	printf("In Hao's Shell\n");

	while(1)
	{
		token = 0;
		strcpy(command,"");
		strcpy(buf,"");
		for(i = 0; i < 20; i++)
			pcommand[i] = NULL;
		i = 0;
		printf("mySHELL $ ");
		gets(command);
		
		tokenize(command);
		if(*pcommand[0] == 232)	continue;
		
/*		printf("Token : %d\n",token);
		for(i = 0; i< token; i++)
			printf("%s\n", pcommand[i]); */

		if(!strcmp(pcommand[0], "exit"))
		{
			exit(0);
		}
		else if(!strcmp(pcommand[0], "?"))
		{
			printH();
		}
		else if(!strcmp(pcommand[0], "pwd"))
		{
			getcwd(buf);
			printf("%s\n", buf);
		}
		else if(!strcmp(pcommand[0], "cd"))
		{
			chdir(pcommand[1]);
		}
		else
		{
			pid = fork();
			if(pid)
			{
				pid = wait(&status);
			}			
			else
			{
				printf("Token : %d\n",token);
				run1(token-1);
			}
		}
		
	}
}
