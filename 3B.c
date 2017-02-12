#include <stdio.h>
#include <stdlib.h>

copy(FILE * fpa,FILE * fpb)
{  char ch;
   ch = getc(fpa);
   while(ch!=EOF)
   {  putc(ch,fpb);
      ch = getc(fpa);
   }
}

main(int argc,char ** argv)
{  FILE * fpa, * fpb;
   int i;

   if(argc<3)
   {  printf("not enough files\n");
      exit(0);
   }

   fpb = fopen(argv[argc-1],"w");
   if(fpb==NULL)
   {  printf("copy: can't open %s\n",argv[argc-1]);
      exit(0);
   }

   for(i=1;i<=argc-2;i++)
   { fpa = fopen(argv[i],"r");
      if(fpa==NULL)
      {  printf("copy: can't open %s\n",argv[i]);
         exit(0);
      }
      copy(fpa,fpb);
      fclose(fpa);
   }
   fclose(fpb);
}
