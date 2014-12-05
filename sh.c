#include "type.h"
#include "string.h"
//char* commands[] = { "ls", "cd", "pwd", "cat", "more", "cp", "mv","mkdir", "rmdir", "creat", "rm", "chmod", "chown", "grep", "ps"};
char cmd[256] ="";
char child1[256]="";
void printH()
{
	printf("************************* Menu ****************************\n");
	printf("*  ls  chdor   pwd   cat   more   cp   mv   mkdir   rmdir *\n");
	printf("*  grep  ps   				                  *\n");
	printf("***********************************************************\n");
}
void cleanCmd()
{
	int i = 0;
	for(i = 0; i< 256; i++)
		cmd[i] = '\0';
}
int check(temp,c)char* temp; char c;
{
	int i = 0;
	while(*temp != '\0')
	{
		if(*temp == c)
			i++;
		*temp ++;
	}
	return i;
}
int CalPipes()
{
        int count = 0;
	char* temp = cmd;
        while (*temp != 0)
        {
                if (*temp == '|') 
		{
			count++;
		}
		temp++;
        }
        return count;
}
void run_the(line)char* line;
{
	STAT a;

	char buf[256];
	char buf2[256];
	int i = 1;
	char* temp;
	
	temp = strtok(line," ");
	strcpy(buf,temp);
	//printf("%x\n",buf[0]);
	strcpy(buf2,"/bin/");	
	strcat(buf2,temp);
	
	if(stat(buf2,&a) == -1)
	{
		if(buf[0] == 0xE8)
		{}
		else
		{	printf("%s is invalid command\n",buf);}
		exit(100);
	}
	while((temp = strtok(NULL," ")) != NULL)
	{
		strcat(buf," ");
		strcat(buf,temp);
	}
	//strcat(buf,'\0');
	//printf("exec: %s\n",buf);
	//getc();	
	exec(buf);
}

int main(argc,argv)int argc; char* argv[];
{
	char tty[256];
	int k =0;
	STAT a;
	int i = 0;
	char* child = NULL;
	char* file = NULL;
	int pipeCount = 0;
	int pipe1[2];
	int pipe2[2];
	int cpid = 0;

	char cmdbuf[256];
	char* command = NULL;
	char* parameter = NULL;
		
	printf("In Hao's Shell\n");
	gettty(tty);
	//printf("%s\n",tty);
	while(1)
	{
		pipeCount = 0;
		pipe1[0] = pipe1[1] = -1;
		pipe2[0] = pipe2[1] = -1;
		cleanCmd();
				
		printf("haoSh$ ");
		// Get the input		
		gets(cmd);
		strcpy(cmdbuf,cmd);
		
		// Check for three most basic command
		command = strtok(cmdbuf," ");
		parameter = strtok(NULL,"\n");

		if(!strcmp(cmd, "exit"))
		{
			exit(0);
		}
		else if(!strcmp(cmd,"help"))
		{
			printH();
		}
		else if(!strcmp(cmd,"pwd"))
		{
		}
		else if(!strcmp(command, "chdir"))
		{
			chdir(parameter);
		} // Basic Handle Done
		else 
		{
			pipeCount = CalPipes();
			if(pipeCount == 0)
			{	
				if(fork() == 0)
				{
					if (check(cmd,'>'))
					{
						child = strtok(cmd, ">");
		                		file = strtok(0, "\n");
						if(file == NULL)
								continue;
						// For appendent mode
						if (*file == '>')
						{
							file+= 2;
							//printf("%s\n",file);
							if(stat(file,&a) == -1)
								creat(file);
							close(1);
							k = open(file, O_APPEND);		
						}
						// For write mode
						else
						{
							file++;
//							printf("%s\n",file);
							if(stat(file,&a) == -1 && file[0] != ' ')
								creat(file);							
							close(1);
							k = open(file, O_WRONLY);

						}
					}
					if(check(cmd, '<'))
					{
//						printf("cmd :%s\n",cmd);
						child = strtok(cmd, "<");
						file = strtok(NULL, "\n");
//printf("%s\n",child);                                                						
//printf("%s\n",file);                                                
						//file++;
						close(0);
						open(file, O_RDONLY);
					}
					run_the(cmd);
				}
			}			
			else if(pipeCount > 0)
			{
				k = 0;
				// If there is a pipe create a first proc, 
				child = strtok(cmd, "|");
				pipe(pipe1);
				if((cpid = fork()) == 0)
				{
					//printf(child);
					dup2(pipe1[1], 1);
					close(pipe1[0]);
					// Only need to check for input indirection
										
					/*if (check(child, '<'))
                                        {
						//k = 1;
						child = strtok(child, '<');
						file = strtok(NULL, "\n");
						close(0);                                                
						open(file, O_RDONLY);
                                        }*/
					run_the(child);
				}
				close(pipe1[1]);
				
				// For procs in the middle
				for(i = 1; i < pipeCount; i++)
				{
					child = strtok(NULL,"|")+1;
					pipe(pipe2);
					if((cpid = fork()) == 0)
					{	
						dup2(pipe1[0], 0);
						dup2(pipe2[1], 1);
						//close(pipe1[0]);
						//close(pipe2[1]);
						close(pipe2[0]);
						run_the(child);
					}
					close(pipe1[0]); 
					close(pipe2[1]);
					pipe1[0] = pipe2[0];
				}
				
				// For last proc
				child = strtok(NULL, "|")+1;
				if((cpid = fork()) == 0)
				{
					dup2(pipe1[0], 0);
					//printf(child);
					if (check(child,'>'))
                                        {

                                                child = strtok(child, ">");
                                                file = strtok(NULL, "\r");
//						if(file == NULL)
//								continue;						
						//printf("%s\n",child);
						//printf("%s\n",file);

						// For appendent mode                                                
						if (*file == '>')
                                                {
                                                        file+= 2;
							if(stat(file,&a) == -1)
								creat(file);
							close(1);
                                                        open(file, O_APPEND);
                                                }
                                                // For write mode
                                                else
                                                {
							file++;
							if(stat(file,&a) == -1)
								creat(file);

							//printf("%s\n",file);
							close(1);
							open(file, O_WRONLY);
                                                }
					}
					//close(pipe1[0]);
					// Only need to check OuptIndirect
					run_the(child);
				}
				close(pipe1[0]);

			}
		}
		for(i = 0; i < pipeCount+1; i++)
		{
			wait(&k);
		}
	}

}
