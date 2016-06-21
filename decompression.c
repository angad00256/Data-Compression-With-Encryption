#include"headers.h"
#include"prototypes.h"

int decompression()
{
	char *encpath;
	int ret;
	char ch='e';
	int stop;
	int pfd;
	int i;
	char *keypath;
	int mafd;
	char *ma;
	int ndc=0;
	int cl=0;
	int ef;
	char *decompressed;
	int ofd;

	encpath=(char*)malloc(sizeof(char)*100);

	ret=fork();
	
	if(ret==0)
	{
      		execl("fileselect","fileselect",&ch,NULL);
	}
			
	wait(&stop);
	
	pfd=open("selectedfilepath",O_RDONLY);

	i=0;

	while(1)
	{
		read(pfd,(encpath+i),1);

		if(*(encpath+i)==10)
		{
			*(encpath+i)='\0';
			break;
		}

		i++;
	}

	system("rm selectedfilepath");

	ch='k';

	keypath=(char*)malloc(sizeof(char)*100);

	ret=fork();
	
	if(ret==0)
	{
      		execl("fileselect","fileselect",&ch,NULL);
	}
			
	wait(&stop);
	
	pfd=open("selectedfilepath",O_RDONLY);

	i=0;

	while(1)
	{
		read(pfd,(keypath+i),1);

		if(*(keypath+i)==10)
		{
			*(keypath+i)='\0';
			break;
		}

		i++;
	}

	system("rm selectedfilepath");

	mafd=open(keypath,O_RDONLY);

	ma=getmasterarray(mafd);

	printf("\nDistinct characters are : \n");

	printf("%s \n",ma);

	ndc=strlen(ma);

	printf("Number of distinct characters : %d \n",ndc);

	cl=codelength(ndc);

	printf("\nCodelength : %d \n",cl);

	ef=open(encpath,O_RDONLY);

	decompressed=(char*)malloc(sizeof(char)*20);
	
	printf("\nEnter the name to be set for the decompressed file : ");
 	
	scanf("%s",decompressed);

	ofd=open(decompressed,O_WRONLY|O_CREAT);

	switch(cl)
	{
		case 1: decompress1(ef,ofd,ma);
			break;

		case 2: decompress2(ef,ofd,ma);
			break;

		case 3: decompress3(ef,ofd,ma);
			break;

		case 4: decompress4(ef,ofd,ma);
			break;
		
		case 5: decompress5(ef,ofd,ma);
			break;
		
		case 6: decompress6(ef,ofd,ma);
			break;
		
		case 7: decompress7(ef,ofd,ma);
			break;
	}

	printf("\nFile Decompression Successful \n");

	ch='d';
	
	ret=fork();
	
	if(ret==0)
	{
      		execl("movefiles","movefiles",&ch,decompressed,NULL);
	}
			
	wait(&stop);
	
	return 0;
OUT:
	return -1;
}
