#include"headers.h"
#include"prototypes.h"

int compress2(int fd,int ef,char* ma)
{
	unsigned char byt;
	unsigned char c;
	unsigned char ch;
	unsigned int index;
	unsigned int l;
	unsigned int len;
	int k;
	int count=0;

	len=strlen(ma);
	
	lseek(fd,0,SEEK_SET);
	lseek(ef,0,SEEK_SET);

	while(1)
	{
		byt^=byt;

		for(k=0;k<=6;k+=2)
		{
			c^=c;

			count=read(fd,&ch,1);
		
			if(count==0)
			{
				switch(k)
				{
					case 0: byt=0xff;
						write(ef,&byt,1);
						goto OUT;
					
					case 2: c=0x3f;
						break;

					case 4: c=0x0f;
						break;

					case 6: c=0x03;
						break;
				}

				byt=byt|c;
				write(ef,&byt,1);
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
			c=c<<6;
			c=c>>k;
			byt=byt|c;
		}

		write(ef,&byt,1);
	}
OUT:
	return 0;
}
