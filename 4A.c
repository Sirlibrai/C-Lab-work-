#include <stdio.h>
#include <stdlib.h>

#define MAX 80

int getLine(FILE* filepath,char a[],int n)
{  int i;
   int ch;
   ch = getc(filepath);
   i = 0;
   while(ch!='\n' && ch!=EOF && i<n-1)
   {  a[i] = ch;
      i++;
      ch = getc(filepath);
   }
   a[i] = '\0';
   if(ch==EOF)
    return EOF;
   if(ch!='\n')
   {  printf("line too long\n");
      while(ch!='\n')
       ch=getc(filepath);
   }
   return i;
}

main(int argc,char ** argv)
{  FILE * filepath;
   char * a;
   int line;
   if((filepath=fopen(argv[1],"r"))==NULL)
   {  printf("can't open %s\n",argv[1]);
      exit(0);
   }
   line = 1;
   a = (char *)malloc(MAX);
   while(getLine(filepath,a,MAX)!=EOF)
   {  printf("%d %s\n",line,a);
      line++;
   }
   fclose(filepath);
}
