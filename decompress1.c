#include"headers.h"
#include"prototypes.h"

int decompress1(int ef,int ofd,char *ma)
{
	unsigned char ch;
	unsigned char byt;
	unsigned int c;
	int len;
	int k;

	len=strlen(ma);

	lseek(ef,0,SEEK_SET);
	lseek(ofd,0,SEEK_SET);

	while(1)
	{
		read(ef,&ch,1);

		for(k=0;k<=7;k++)
		{
			byt^=byt;
			c^=c;

			byt=byt|ch;
			byt=byt<<k;
			byt=byt>>7;
			c=byt;

			if(c==1)
			{
				goto OUT;
			}
		
			write(ofd,(ma+c),1);
		}		
	}
OUT:
	return 0;
}
