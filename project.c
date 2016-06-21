#include"headers.h"
#include"prototypes.h"

int main()
{
	int choice;

	while(1)
	{
		choice=mainmenu();

		switch(choice)
		{	
			case 1: compression();
				break;
	
			case 2: decompression();
				break;

			case 0: return 0;

			default: printf("Enter a valid choice \n");
			 	 break;
		}

		printf("\n");
	}

	return 0;
}
