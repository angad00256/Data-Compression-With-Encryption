#include"headers.h"
#include"prototypes.h"

int decompress6(int ef,int ofd,char *ma)
{
	unsigned char ch;
	unsigned char byt;
	unsigned char nbyt;
	unsigned int c;
	int len;
	int k;
	int a[3]={6,4,2};
	int b[2]={4,6};
	int j;

	len=strlen(ma);

	lseek(ef,0,SEEK_SET);
	lseek(ofd,0,SEEK_SET);

	byt^=byt;
	nbyt^=nbyt;
	c^=c;

	while(1)
	{
		j=0;

		read(ef,&ch,1);
		byt=byt|ch;
		
		for(k=0;k<=3;k++)
		{
			byt=byt>>2;
			c=byt;

			if(c==63)
			{
				goto OUT;
			}
		
			write(ofd,(ma+c),1);
			
			byt^=byt;
			nbyt^=nbyt;

			if(k!=3)
			{
				byt=byt|ch;
				byt=byt<<a[k];
			}

			if((k==0)||(k==1))
			{
				read(ef,&ch,1);
				nbyt=nbyt|ch;
				nbyt=nbyt>>b[j];
				nbyt=nbyt<<2;
				byt=byt|nbyt;
				j++;
			}	
		}
	}
OUT:
	return 0;
}
