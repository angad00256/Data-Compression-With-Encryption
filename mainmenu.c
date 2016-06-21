#include"headers.h"
#include"prototypes.h"

int mainmenu()
{
	int choice;

	printf("\n......MAIN MENU......\n\n");

	printf("1.  Compression \n");

	printf("2.  Decompression \n");

	printf("0.  Exit \n\n");

	printf("Enter your choice : ");

	scanf("%d",&choice);

	printf("\n");

	return(choice);
}
