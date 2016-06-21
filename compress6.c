#include"headers.h"
#include"prototypes.h"

int compress6(int fd,int ef,char* ma)
{
	unsigned char byt;
	unsigned char c;
	unsigned char ch;
	unsigned int index;
	unsigned int l;
	unsigned int len;
	int k;
	int count=0;
	int a[4]={0,6,4,2};

	len=strlen(ma);
	
	lseek(fd,0,SEEK_SET);
	lseek(ef,0,SEEK_SET);

	while(1)
	{
		byt^=byt;
		c^=c;

		for(k=0;k<=3;k++)
		{
			count=read(fd,&ch,1);
		
			if(count==0)
			{
				switch(k)
				{
					case 0: goto DOWN;

					case 1: c=0x03;
						break;

					case 2: c=0x0f;
						break;

					case 3: c=0x3f;
						break;
				}

				byt=byt|c;
				write(ef,&byt,1);
DOWN:
				if(k!=3)
				{
					byt=0xff;
					write(ef,&byt,1);
				}

				goto OUT;
			}

			for(l=0;l<len;l++)
			{
				if(ch==*(ma+l))
				{
					index=l;
					break;
				}
			}

			c=index;
			c=c<<2;
			c=c>>a[k];
			byt=byt|c;

			if((k==1)||(k==2))
			{
				write(ef,&byt,1);
				byt^=byt;
				c=index;
				
				if(k==1)
				{
					c=c<<4;
				}	
				
				else if(k==2)
				{
					c=c<<6;
				}	

				byt=byt|c;
			}

			if(k==3)
			{
				write(ef,&byt,1);
			}
		}
	}
OUT:
	return 0;
}
