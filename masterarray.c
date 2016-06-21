#include"headers.h"
#include"prototypes.h"

char* masterarray(int fd)
{
	char *ma;
	char ch;
	int l;
	int i=0;
	int flag=0;
	int count=0;

	ma=(char*)malloc(sizeof(char)*100);

	if(!ma)
	{
		perror("malloc");
		goto OUT;
	}
	
	while(1)
	{
		count=read(fd,&ch,1);

		if(count==0)
		{
			break;
		}

		for(l=0;l<i;l++)
		{
			if(ch==*(ma+l))
			{
				flag=1;
				break;
			}
		}

		if(!flag)
		{
			*(ma+i)=ch;
			i++;
		}
	
		flag=0;
	}

	return(ma);
OUT:
	return 0;
}
