#include"headers.h"
#include"prototypes.h"

int compress7(int fd,int ef,char* ma)
{
	unsigned char byt;
	unsigned char c;
	unsigned char ch;
	unsigned int index;
	unsigned int l;
	unsigned int len;
	int k;
	int count=0;
	int a[8]={0,7,6,5,4,3,2,1};

	len=strlen(ma);
	
	lseek(fd,0,SEEK_SET);
	lseek(ef,0,SEEK_SET);

	byt^=byt;
	c^=c;

	while(1)
	{
		for(k=0;k<=7;k++)
		{
			count=read(fd,&ch,1);
		
			if(count==0)
			{
				switch(k)
				{
					case 0: goto DOWN;

					case 1: c=0x01;
						break;

					case 2: c=0x03;
						break;

					case 3: c=0x07;
						break;

					case 4: c=0x0f;
						break;

					case 5: c=0x1f;
						break;

					case 6: c=0x3f;
						break;

					case 7: c=0x7f;
						break;
				}

				byt=byt|c;
				write(ef,&byt,1);
				printf("byt = %x \n",byt);
DOWN:
				if(k!=7)
				{
					byt=0xff;
					write(ef,&byt,1);
					printf("byt = %x \n",byt);
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
			c=c<<1;
			c=c>>a[k];
			byt=byt|c;

			if(k!=0)
			{
				write(ef,&byt,1);
				printf("byt = %x \n",byt);
				byt^=byt;
				
				if(k!=7)
				{
					c=index;
					c<<(k+1);
					byt=byt|c;
				}
			}
		}
	}
OUT:
	return 0;
}
