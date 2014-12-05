#include "type.h"
#include "string.h"
int main(void)
{
	char a[50];
	char* temp = NULL;
	strcpy(a,"ls | ls");
	
	printf("%s\n",strtok(a," "));
	temp = strtok(NULL,"|");
	if(temp != NULL)
		printf("%s\n",temp);
	printf("%s\n",strtok(NULL," "));

}
