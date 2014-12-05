#include "type.h"
#include "stdlib.h"
#include "string.h"
typedef struct user
{
	int gid;
	int uid;
	char homedir[256];
	char program[256];
}USER;

int main(argc, argv)int argc; char* argv[];
{	
	int stdin;
	int stdout;
	int stderr;
	int pfile;
	int i = 0;
	int found = 0;
	char* temp;

	char name[256];
	char passwd[256];
	char buf[1024];
	char buf2[1024];
	
	STAT status;
	USER a;

	stat("/etc/passwd", &status);

	close(0);
	close(1);

	stdin = open(argv[1],O_RDONLY);
	stdout = open(argv[1],O_WRONLY);	
	stderr = open(argv[1],O_WRONLY);
	fixtty(argv[1]);
	printf("Entering Hao's Login\n");

	pfile = open("/etc/passwd", O_RDONLY);
	i = read(3,buf2,1024);

	while(1)
	{
		memcpy(buf,buf2,1024);
		printf("Login : ");
		gets(name);
		printf("Password : ");
		gets(passwd);
		//putc('\r');
		temp = strtok(buf,":");
		while(temp != NULL)
		{
			if(!(strcmp(temp,name)))
			{
				//strcpy(a.name, temp);
				temp = strtok(NULL,":");
				if(!(strcmp(temp,passwd)))
				{
					// gid
                                	temp = strtok(NULL, ":");                          
					a.uid = atoi(temp);
                                	// uid
                                	temp = strtok(NULL, ":");
                                	a.uid = atoi(temp);
					// fullname(skip)                                	
					strtok(NULL, ":");
                                        // home directory           
                                        temp = strtok(NULL, ":");
                                	strcpy(a.homedir,temp);
					// default program
                                	temp = strtok(NULL, "\n");
					//strtok(NULL,"\n");                                	
					strcpy(a.program,temp);
					chown(a.uid);
					chdir(a.homedir);
					//printf(a.program);
					exec(a.program);
					
                           	}
			}
			strtok(NULL,"\n");
			temp = strtok(NULL,":");
		}
		printf("Invalid Account\n");	
	}
}
