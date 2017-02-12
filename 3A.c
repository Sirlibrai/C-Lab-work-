#include <stdio.h>
#include <stdlib.h>

main(int argc,char ** argv)
{  int numChar;
   FILE * fp;
   char ch;
   fp = fopen(argv[1],"r");
   if(fp==NULL)
   {  printf("Cannot open %s\n",argv[1]);
      exit(0);
   }
   numChar = 0;
   ch = fgetc(fp);
   while((ch = fgetc(fp)) !=EOF)
   {   
	   numChar++;
   }
   fclose(fp);
   printf("%s has %d characters\n",argv[1],numChar);
}
