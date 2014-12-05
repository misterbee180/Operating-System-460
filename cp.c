#include "type.h"
#include <string.h>
char buf[1024];
int mycp();
char* basename(str1)char* str1;
{
	char* c = str1;
	c += strlen(str1);
	while(*c != '/')
	{
		c--;
	}
	return c+1;
}
void cpf2f(f1,f2)char* f1; char* f2;
{
	int f1d;
	int f2d;
	int n;	

//	printf("f%s to f%s\n", f1,f2);
	f1d = open(f1, O_RDONLY);
	f2d = open(f2, O_WRONLY|O_CREAT);

	if(f1d==-1 || f2d == -1)
	{
		printf("WHY AGAIN~~~~~\n");
		getc();
	}

	while(n = read(f1d,buf,1024))
	{
		write(f2d,buf,n);
	}
	close(f1d);
	close(f2d);
}

void cpf2d(f1,d2)char* f1; char* d2;
{
	char buf2[1024];
	STAT a;

//	printf("Cp f to d\n");	
	strcpy(buf2,d2);
	strcat(buf2,"/");
	strcat(buf2,basename(f1));
//	printf("%s\n",buf2);
	/*if(stat(buf2,&a) == -1)
	{
		printf("NOT Found\n");
	}*/

	cpf2f(f1,buf2);		
}

void cpd2d(d1,d2)char* d1; char* d2;
{
	STAT a;
	
	char buf2[128];
	char buf3[128];
	char buf4[1024];
	char buf5[128];

	char* cp;
	DIR* dp;	
	int n = 0;
	int fd = 0;
	int i = 0;

	if(stat(d2,&a) == -1)
	{
		mkdir(d2);
		strcpy(buf2,d2);
	}
	else
	{	
		strcpy(buf2,d2);
		strcat(buf2,"/");
		strcat(buf2,d1);
		mkdir(buf2);
	}

//	printf("%s\n",d1);
	fd = open(d1, O_RDONLY);
	if(fd == -1 )
	{
		printf("WHY ~~~~~\n");
		getc();
	}

	while(n = read(fd,buf4,1024))
	{
		printf("%d\n",n);
		dp = cp = buf4;
		while( cp <= &buf4[n-1])
		{
			strncpy(buf3,dp->name,dp->name_len);
			buf3[dp->name_len] = '\0';
			if(strcmp(buf3,".") && strcmp(buf3,".."))
			{
				strcpy(buf5,d1);
				strcat(buf5,"/");
				strcat(buf5,buf3);
				mycp(buf5,buf2);
			}
			cp+= dp->rec_len;
			dp = cp;
		}
	}
	close(fd);
}
int mycp(str1,str2)char* str1; char* str2;
{
	STAT f1;
	STAT f2;

	stat(str1,&f1);
	stat(str2,&f2);

	if(f1.st_ino == f2.st_ino)
	{
		printf("Oh Come on\n");
		exit(11);
	}
	
	if((f1.st_mode & 0040000))
	{
		printf("D:%s to D:%s\n",str1,str2);
//		getc();
		cpd2d(str1,str2);
	}
	else if( (f1.st_mode & 0100000) && (f2.st_mode & 0040000) )
	{
		printf("F:%s to D:%s\n",str1,str2);
//		getc();
		cpf2d(str1,str2);
	}
	else if( (f1.st_mode & 0100000))
	{
		printf("F:%s to F:%s\n",str1,str2);
//		getc();
		cpf2f(str1,str2);
	}
	else
	{
		printf("??\n");
		exit(12);
	}
	
}

int main(argc, argv) int argc; char* argv[];
{
	
	if( argc < 3)
	{
		printf("NO!!!\n");
		exit(10);
	}
//	printf("Copying %s to %s\n",argv[1],argv[2]);
//	getc();
	mycp(argv[1],argv[2]);
}
