#include <stdio.h>
int main()
{
     FILE *fpw;

     /*Char array to store strings */
     char str[100];

     /*Opening the file FILEW.TXT in "w" mode for writing*/
     fpw = fopen("file2.txt", "w");

     /*Error handling for output file*/
     if (fpw== NULL)
     {
          puts("Issue in opening the Output file");
     }

     printf("Enter your string:");

     /*Stored the input string into array – str*/
     gets(str);

     /* Copied the content of str into file – 
      * mynewtextfile2.txt using pointer – fpw
      */
     fputs(str, fpw);

     /*Closing the Output file after successful writing*/
     fclose(fpw);
     return 0;
}
