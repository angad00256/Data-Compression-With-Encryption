#include"headers.h"
#include"prototypes.h"

int decompress3(int ef,int ofd,char *ma)
{
	unsigned char ch;
	unsigned char byt;
	unsigned char nbyt;
	unsigned int c;
	int len;
	int k;
	int j;
	int a[8]={0,3,0,1,4,0,2,5};
	int b[2]={6,7};
	int d[2]={7,6};

	len=strlen(ma);

	lseek(ef,0,SEEK_SET);
	lseek(ofd,0,SEEK_SET);

	while(1)
	{
		byt^=byt;
		nbyt^=nbyt;
		c^=c;
		j=0;
		
		read(ef,&ch,1);
		byt=byt|ch;
		
		for(k=0;k<=7;k++)
		{
			byt=byt<<a[k];
			byt=byt>>5;
			c=byt;

			if(c==7)
			{
				goto OUT;
			}
		
			write(ofd,(ma+c),1);
			
			byt^=byt;
			nbyt^=nbyt;
			
			if(k!=7)
			{
				byt=byt|ch;
			}

			if((k==1)||(k==4))
			{
				byt=byt<<b[j];
				read(ef,&ch,1);
				nbyt=nbyt|ch;
				nbyt=nbyt>>d[j];
				nbyt=nbyt<<5;
				byt=byt|nbyt;
				j++;
			}
		}
	}
OUT:
	return 0;
}
