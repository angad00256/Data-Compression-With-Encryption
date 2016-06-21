#include"headers.h"
#include"prototypes.h"

int decompress5(int ef,int ofd,char *ma)
{
	unsigned char ch;
	unsigned char byt;
	unsigned char nbyt;
	unsigned int c;
	int len;
	int k;
	int a[7]={5,2,7,4,1,6,3};
	int b[4]={6,4,7,5};
	int j;

	len=strlen(ma);

	lseek(ef,0,SEEK_SET);
	lseek(ofd,0,SEEK_SET);

	while(1)
	{
		byt^=byt;
		nbyt^=nbyt;
		c^=c;
		j=0;
		
		for(k=0;k<=6;k++)
		{
			if((k!=2)&&(k!=5))	
			{
				read(ef,&ch,1);
			
				if(k==0)
				{
					byt=byt|ch;
					byt=byt>>3;	
				}
		
				else
				{
					nbyt=nbyt|ch;
					nbyt=nbyt>>b[j];
					byt=byt|nbyt;
					j++;
				}
			}

			c=byt;

			if(c==31)
			{
				goto OUT;
			}
		
			write(ofd,(ma+c),1);
			
			byt^=byt;
			byt=byt|ch;
			byt=byt<<a[k];
			byt=byt>>3;

			if(k==6)
			{
				c=byt;
				
				if(c==31)
				{
					goto OUT;
				}
		
				write(ofd,(ma+c),1);
				byt^=byt;
			}
		}
	}
OUT:
	return 0;
}
