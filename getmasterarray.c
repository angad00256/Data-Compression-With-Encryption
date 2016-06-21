#include"headers.h"
#include"prototypes.h"

char* getmasterarray(int mafd)
{
	char ch;
	int ndc=0;
	char *ma;
	int count=0;

/*        mafd=open("mafile",O_RDONLY);

        if(mafd<0)
        {
                perror("open");
                goto OUT;
        }
*/
	while(1)
        {
                count=read(mafd,&ch,1);

                if(count==0)
                {
                        break;
                }

                else
                {
                        ndc++;
                }
        }

        ma=(char*)malloc(sizeof(char)*(ndc+1));

        if(!ma)
        {
                perror("malloc");
                goto OUT;
        }

        lseek(mafd,0,SEEK_SET);

        read(mafd,ma,ndc);

	*(ma + ndc)='\0'; 

        close(mafd);

	return ma;
OUT:
	return 0;
}
