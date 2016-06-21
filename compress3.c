#include"headers.h"
#include"prototypes.h"

int compress3(int fd,int ef,char* ma)
{
	unsigned char byt;
	unsigned char c;
	unsigned char ch;
	unsigned int index;
	unsigned int l;
	unsigned int len;
	int k;
	int count=0;
	int a[8]={0,3,6,1,4,7,2,5};

	len=strlen(ma);
	
	lseek(fd,0,SEEK_SET);
	lseek(ef,0,SEEK_SET);

	while(1)
	{
		byt^=byt;
		c^=c;

		for(k=0;k<=7;k++)
		{
			count=read(fd,&ch,1);
		
			if(count==0)
			{
				switch(k)
				{
					case 0: goto DOWN;

					case 1: c=0x1f;
						break;

					case 2: c=0x03;
						break;

					case 3: c=0x7f;
						break;

					case 4: c=0x0f;
						break;

					case 5: c=0x01;
						break;

					case 6: c=0x3f;
						break;

					case 7: c=0x07;
						break;
				}

				byt=byt|c;
				write(ef,&byt,1);
DOWN:
				if((k==0)||(k==2)||(k==5))
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
			c=c<<5;
			c=c>>a[k];
			byt=byt|c;

			if((k==2)||(k==5)||(k==7))
			{
				write(ef,&byt,1);
				byt^=byt;

				if((k==2)||(k==5))
				{
					c=index;
					
					if(k==2)
					{
						c=c<<7;
					}

					if(k==5)
					{
						c=c<<6;
					}

					byt=byt|c;
				}
			}
		}
	}
OUT:
	return 0;
}
