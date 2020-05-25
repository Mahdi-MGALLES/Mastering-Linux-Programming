#include <stdio.h>
#include <stdlib.h>

int main()
{
	//Initialize the file pointer
	FILE *f;
	//Take a array of characters 
	char ch[100];
	//Create the file for write operation
	f=fopen("includehelp.txt","w");
	printf("Enter five strings\n");
	for(int i=0;i<4;i++){
		//take the strings from the users
		scanf("%[^\n]",ch);
		//write back to the file
		fputs(ch,f);
		//every time take a new line for the new entry string 
		fputs("\n",f);
		//except for last entry.Otherwise print the last line twice
		//clear the stdin stream buffer
		fflush(stdin );
		//if we don't write this then after taking string 
		//%[^\n] is waiting for the '\n' or white space
	}
	 printf("out from loop for\n");
	//take the strings from the users
	scanf("%[^\n]",ch);
	fputs(ch,f);
	//close the file after write operation is over
	fclose(f);

	//open a file
	f=fopen("includehelp.txt","r");		
	printf("File content is--\n");
	printf("\n...............print the strings..............\n");
	while(!feof(f)){
		//takes the first 100 character in the character array 
		fgets(ch,100,f);				
		//and print the strings
		printf("%s",ch);
	}

	//close the file
	fclose(f);

	return 0;
}
