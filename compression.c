#include"headers.h"
#include"prototypes.h"

int compression()
{
	char *encfilename;
	char *keyfilename;
	int fd;
	int i;
	int nocr;
	char *path;
	char *ma;
	int ndc;
	int cl;
	int ef;
	int mafd;
	int ret;
	int pfd;
	int stop;
	char ch='c';
	int count=0;

	ma=(char*)malloc(sizeof(char)*100);
	
	path=(char*)malloc(sizeof(char)*100);
	
	ret=fork();
	
	switch(ret)
	{
      		case 0: execl("fileselect","fileselect",&ch,NULL);
                        break;
	}
			
	wait(&stop);
	
	pfd=open("selectedfilepath",O_RDONLY);

	i=0;

	while(1)
	{
		read(pfd,(path+i),1);

		if(*(path+i)==10)
		{
			*(path+i)='\0';
			break;
		}

		i++;
	}

	system("rm selectedfilepath");
		
	fd=open(path,O_RDONLY);

	if(fd<0)
	{
		perror("open");
		goto OUT;
	}

	printf("\n");

        while(nocr)
        {
                nocr=read(fd,&ch,1);

		count++;
        }

	count--;

	printf("Total number of characters : %d \n",count);

	lseek(fd,0,SEEK_SET);

	ma=masterarray(fd);
	
	printf("\nDistinct characters are \n");

	printf("%s \n",ma);
	
	ndc=strlen(ma);

	printf("\nNumber of distinct characters : %d\n",ndc);

	keyfilename=(char*)malloc(sizeof(char)*20);

	if(!keyfilename)
	{
		perror("malloc");
		goto OUT;
	}
	
	printf("\nEnter the name of key file to be set : ");

	scanf("%s",keyfilename);

	mafd=open(keyfilename,O_WRONLY|O_CREAT);

        if(mafd<0)
        {
                perror("open");
                goto OUT;
        }
	
	write(mafd,ma,ndc);
	write(mafd,&ch,1);

	cl=codelength(ndc);

	printf("\nCode length : %d\n",cl);

	encfilename=(char*)malloc(sizeof(char)*20);

	if(!encfilename)
	{
		perror("malloc");
		goto OUT;
	}
	
	printf("\nEnter the name of encrytion file to be set : ");

	scanf("%s",encfilename);

	ef=open(encfilename,O_WRONLY|O_CREAT);

	if(ef<0)
	{
		perror("open");
		goto OUT;
	}

	switch(cl)
	{
		case 1: compress1(fd,ef,ma);
			break;

		case 2: compress2(fd,ef,ma);
			break;

		case 3: compress3(fd,ef,ma);
			break;

		case 4: compress4(fd,ef,ma);
			break;

		case 5: compress5(fd,ef,ma);
			break;
		
		case 6: compress6(fd,ef,ma);
			break;
		
		case 7: compress7(fd,ef,ma);
			break;
	}

	printf("\nFile Compression Successful \n");

	ch='c';
	
	ret=fork();
	
	if(ret==0)
	{
      		execl("movefiles","movefiles",&ch,encfilename,keyfilename,NULL);
	}
			
	wait(&stop);
	
	return 0;
OUT:
	return -1;
}
