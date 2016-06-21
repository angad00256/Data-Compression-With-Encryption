#include"headers.h"
#include"prototypes.h"

int decompress7(int ef,int ofd,char *ma)
{
	unsigned char ch;
	unsigned char byt;
	unsigned char nbyt;
	unsigned int c;
	int len;
	int k;
	int j;
	int a[7]={7,6,5,4,3,2,1};
	int b[6]={2,3,4,5,6,7};

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
		
		for(k=0;k<=7;k++)
		{
			byt=byt>>1;
			c=byt;

			if(c==127)
			{
				goto OUT;
			}
		
			write(ofd,(ma+c),1);
			
			byt^=byt;
			nbyt^=nbyt;

			if(k!=7)
			{
				byt=byt|ch;
				byt=byt<<a[k];
			}

			if((k!=6)&&(k!=7))
			{
				read(ef,&ch,1);
				nbyt=nbyt|ch;
				nbyt=nbyt>>b[j];
				nbyt=nbyt<<1;
				byt=byt|nbyt;
				j++;
			}	
		}
	}
OUT:
	return 0;
}
