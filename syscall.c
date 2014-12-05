#include "type.h"
//#include "uio.c" 
#define DEC 10
#define HEX 16
char *table = "0123456789";
char* HexTable = "0123456789abcdef";

int getpid()
{
   return syscall(0,0,0);
}
int fork()
{
   return syscall(5, 0, 0);
}

int exec(file) char *file;
{
   return syscall(6, file, 0);
}

int wait(status) int *status;
{
  return (syscall(20, status, 0));
}

int mkdir(name) char *name;
{
   return syscall(21, name, 0);
}

int rmdir(name) char *name;
{
   return syscall(22, name, 0);
}

int creat(filename) char *filename;
{
    return syscall(23, filename, 30);
}

int rm(name) char *name;
{
   return syscall(24, name, 0);
}

int chdir(name) char *name;
{
   return syscall(26, name, 0);
}

int open(file, flag) char *file; int flag;
{
    return syscall(28, file, flag);
}

int close(fd) int fd;
{
    return syscall(29, fd);
}

long lseek(fd, offset, ww) int fd; long offset; int ww;
{
    return syscall(30, fd, (long)offset, ww);
}

int chmod(mode,file) int mode; char *file;
{
  return syscall(33, mode, file, 0);
}   

int chown(uid) int uid;
{
    return syscall(34, uid, 0);
}   

int read(fd, buf, nbytes) int fd, nbytes; char *buf;
{
    return syscall(35, fd, buf, nbytes);
}

int write(fd, buf, nbytes) int fd, nbytes; char *buf;
{
    return syscall(36, fd, buf, nbytes);
}

int stat(filename, sPtr) char *filename; struct stat *sPtr;
{   
   return syscall(38, filename, sPtr);
}

int getcwd(cwdname) char *cwdname;
{
    return syscall(39, cwdname, 0);
}

int pipe(pd) int *pd;
{
    return syscall(40, pd, 0);
}

int dup(fd) int fd;
{
   return syscall(41, fd, 0);
}

int dup2(fd,gd) int fd, gd;
{
   return syscall(42, fd, gd);
}

int fstat(fd, sptr) int fd; struct stat *sptr;
{
  return syscall(45,fd,sptr,0);
}

int kill(sig, pid) int sig, pid;
{
  return syscall(50, sig, pid);
}

int signal(sig, catcher) ushort sig, catcher;
{
  return syscall(51, sig, catcher);
}

int touch(filename) char *filename;
{
  return syscall(54, filename, 0);
}

int fixtty(s) char *s;
{
  syscall(80, s, 0,0);
}

int gettty(s) char *s;
{
  syscall(81, s, 0,0);
}

int sync()
{
  return syscall(90, 0, 0, 0);
}

int getuid()
{
  return syscall(93, 0);
}

int chuid(uid) int uid;
{
  return syscall(94, uid, 0);
}

int exit(value) int value;
{
   syscall(99, value, 0);
}

void putc(c) int c;
{
	STAT a;
	char b = '\r';
	int i = 0;
	fstat(1,&a);
	//getc();
	i = (a.st_mode & 0020000);
	write(1, &c, 1);
	//getc();
	if(c == '\n' && i)
		write(1,&b,1);
}
int getc()
{
	int c;
	read(0, &c, 1);
	return (c & 0x7F);
}
/*
void gets(s) char* s;
{
	//STAT a;
	//b = '\r';
	//fstat(1,&a)
	
	//i = a.st_mode & 0x8000;
	while((*s = getc()) != '\r')
	{
		putc(*s);
		s++;
	}
	//if(c == '\n' && !i)
	//write(1,&b,1);
	
	putc('\n');
	putc('\r');
	*s = '\0';
}

int printu(unsigned int x)
{
    if (!x)
       putc('0');
    else
       rpu(x);
}
int rpu(unsigned int x)
{
    char c;
    if (x){
       c = table[x % DEC];
       rpu(x / DEC);
       putc(c);
    }
}
int prints(char *s)
{
	while(*s != '\0')
	{
		putc(*s);
		s++;
	}
}
int printi(int x)
{
	if(!x)
	{
		putc('0');
	}
	else if(x<0)
	{	
		putc('-');				
		x = -x;		
		rpu(x);
	}	
	else
	{
		rpu(x);
	}
}
int printx(int x)
{
	if(!x)
	{
		putc('0');
	}
	else if(x<0)
	{	
		putc('-');				
		x = -x;		
		rpx(x);
	}	
	else
	{
		rpx(x);
	}
}
int rpx(int x)
{
    char c;
    if (x){
       c = HexTable[x % HEX];
	   rpx(x / HEX);
       putc(c);
    }
}
int printf(char* str, ...)
{
	unsigned int* ptr = &str;	
	char c;
	c = *str;
	while(c != '\0')
	{
		if(c == '%')
		{
			str++;
			c=*str;
			switch (c)
			{
				case 'x':
					printx(*(++ptr));
					break;
				case 'u':
					printu(*(++ptr));
					break;
				case 'c':
					putc(*(++ptr));
					break;
				case 'd':
					printi(*(++ptr));
					break;
				case 's':
					prints(*(++ptr));
					break;
				default:
					putc('%');
					putc(c);
					break;
			}
		}
		else if(c == '\\')
		{
			str++;
			c=*str;
			switch (c)
			{
				case 'n':
					putc('\n');
					break;
				case 't':
					putc('\t');
					break;
				case '\r':
					putc('\r');
					break;
				default:
					putc(c);
					break;
			}						
		}
		else
		{
			putc(c);
		}
		c = *(++str);
	}
}*/
