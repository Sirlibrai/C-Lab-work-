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

int contains(char target[],int m,char source[],int n)
{  int i,j;
   int found;
   i=0;
   while(i<n-m)
   {  found = 1;
      for(j=0;j<m;j++)
       found = found && (target[j]==source[i+j]);
      if(found)
       return 1;
      i++;
   }
   return 0;
}

int slength(char * a)
{  int i;
   i = 0;
   while(a[i]!='\0')
    i++;
   return i;
}
       
main(int argc,char ** argv)
{  FILE * filepath;
   char * a;
   int l;
   int line;
   if((filepath=fopen(argv[2],"r"))==NULL)
   {  printf("can't open %s\n",argv[1]);
      exit(0);
   }
   line = 1;
   a = (char *)malloc(MAX);
   while((l=getLine(filepath,a,MAX))!=EOF)
   {  if(contains(argv[1],slength(argv[1]),a,l))
       printf("%d %s\n",line,a);
      line++;
   }
   fclose(filepath);
}
