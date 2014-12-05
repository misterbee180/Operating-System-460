#include "type.h"
#include <string.h>

char buf[1024];
char line[256];

int str_match(str1, str2) char* str1; char* str2;
{
	int i = 0;
	int n = strlen(str1);
	int m = strlen(str2);
	
//	printf("%s %d\n",str1,n);
//	printf("%s %d\n",str2,m);
//	printf("%d\n",n-m+1);
//	getc();
	
	for(i = 0; i < (n-m+1); i++)
	{
		
		if(!strncmp(&str1[i],str2,m))
		{
			return 1;
		}
	}
	return 0;
	
}

int main(argc,argv)int argc; char* argv[];
{
	int fd;
	char* cp;
	char tty[256];
	int i = 0;
	int n = 0;
	int k = 0;
	int j = 0;
	gettty(tty);
	if(argc == 2)
	{
		dup2(1,5);
		close(1);
		fd = open(tty,O_WRONLY);
		printf("Grep From Stdin\n");
		close(1);		
		dup2(5,1);
		fd = 0;
	}
	else if(argc == 3)
	{
//		printf("%s\n",argv[1]);
//		printf("%s\n",argv[2]);	
		fd = open(argv[2],O_RDONLY);
		if(fd < 0 ) exit(100);		
	}
	else
	{
		fd = open(tty,O_WRONLY);
		write(fd,"Error\n\r",8);
		close(fd);
		exit(1);
	}

	while(n = read(fd,buf,1024))
	{
		cp = buf;
		while( cp <= &buf[n-1])
		{
			if(*cp == '\r')
			{
				//cp++;
			}
			else if(*cp == '\n' || *cp == '\0')
			{
				line[i] = '\0';
				if(str_match(line, argv[1]))
				{
					for(j = 0; j<i; j++)
					{
						putc(line[j]);
					}
					putc(*cp);
//					printf("%s\n",line);
				}
				i = 0;
			}			
			else
			{
				line[i] = *cp;
				i++;
			}
			cp++;
		}
	}
	close(1);
	close(fd);
	exit(0);

}

