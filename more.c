#include "type.h"

char buf[1024];
char line[256];

int main(argc,argv)int argc; char* argv[];
{
	int fd;
	char* cp;
	char* tty[256];
	char c;
	int i = 0;
	int n = 0;
	int lineCount = 0;
	gettty(tty);

	if(argc == 1)
	{
		fd = 0;
	}
	else
	{
		fd = open(argv[1], O_RDONLY);
	}
	while(n = read(fd,buf,1024))
	{
		cp = buf;
		while(cp <= &buf[n-1])
		{
			if(*cp != '\n')
			{
				line[i] = *cp;
				i++; cp++;
			}
			else
			{
				line[i] = '\0';
				printf("%s\n",line);
				lineCount++;
				i = 0;
				cp++;
				if(lineCount == 25)
				{
					if(fd == 0)
					{
						dup2(0,5);
						close(0);
						fd = open(tty,O_RDONLY);
						c = getc();
						close(0);
						dup2(5,0);
						close(5);
					}
					else
					{
						c = getc();
					}
					if(c == ' ')
						lineCount = 0;
					else
						lineCount--;

				}
			}
		}
	}
}
