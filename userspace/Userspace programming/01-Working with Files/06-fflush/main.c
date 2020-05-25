#include <stdio.h>
int main()
{
   char buf[50];
   FILE *fp;
   fp = fopen("test.txt", "r+");
   if (fp)
   {
      fputs("Test data by Fresh2refres", fp);
      fflush(buf); // flushes the buffer to load the data from file
      fgets(buf, 20, fp); // It loads 1st 20 characters from file to buffer
      puts(buf); // It displays buffer data in output screen
      fclose(fp);
      return 0;
   }
   return 1;
}
