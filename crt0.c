#include <string.h>
int argc;
char *argv[32];
int color = 0x006;

int token(line) char *line;
{
	int new = 1;
	char* temp = line;


	while((*temp) != '\0')
	{
		if((*temp) == ' ')
		{
			new = 1;
			*temp = '\0';
		}
		else if(new == 1)
		{
			argc++;			
			argv[argc-1] = temp;
			new = 0;
		}
		temp++;
	}
}

main0(s) char* s;
{
//	printf("%s\n",s);
  	token(s);

//	printf("%d ",argc);
//	printf("%s\n",argv[0]);
//	printf("%s\n",argv[1]);
  	main(argc, argv);
}

