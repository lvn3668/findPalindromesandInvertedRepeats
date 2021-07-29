// Author: Lalitha Viswanathan
// Affiliation: Tata Consultancy Services 
#include <cstdio>
#include <stdlib.h>
void readDNA(char *filename)
{
	  FILE* fp;
	  char str[500],ch;
	  char* seq;
	  long int size=1,i, len;
	  if(!(fp=fopen(filename,"r")))
	  {
		  printf("Filename %s does not exist\n",filename);
		  exit(1);
	  }
	  fseek(fp,0L,SEEK_END);
	  long int temp=ftell(fp);
	  seq=(char *)(malloc(sizeof(char)*temp));
	  fseek(fp,0L,SEEK_SET);
	  while(!feof(fp))
	  {	
			  	 ch=fgetc(fp);
				 // Ignores junk DNA characters
				 // Does not flag errors in input fasta file 
   				 if((ch=='A')||(ch=='T')||(ch=='U')||(ch=='C')||(ch=='G'))
					 seq[size++]=ch;
	  }
	  len=size;
}
