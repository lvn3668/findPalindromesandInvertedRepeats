// Author: Lalitha Viswanathan
// Affiliation: Tata Consultancy Services 
#include<iostream.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<ctype.h>
#include "palindromes.h"
#include "readDNA.cpp"
char* strng;
main(int argc,char *argv[])
{
		char* filename;
		if(argc!=8)
		{
			printf("\nInput should be in the form <filename> <minlength> <maxlength> <gaplength> <mismatches> <match score> <mismatch score>\n");
			exit(1);
		}
		filename=argv[1];
		minlength=atoi(argv[2]);
		maxlength=atoi(argv[3]);
		gaplength=atoi(argv[4]);
		mismatches=atoi(argv[5]);
		match=atoi(argv[6]);
	    	mismatch=atoi(argv[7]);
		readDNA(filename);
	        findpalindromesandinvertedrepeats();
}
char* getsubstr(long int x,long int y,char* s)
{
		long int q=0,a;
		for(a=x;a<=y && y<=len;a++)
		{
		    s[q]=seq[a];
	  	    q++;		
		}
		s[q]='\0';
		return s;
}	
char complementary(char characterInDNASeq)
{
		if(characterInDNASeq=='A')
				return 'T';
		else if(characterInDNASeq=='T')
				return 'A';
		else if(characterInDNASeq=='G')
				return 'C';
		else
				return 'G';
}		

char* complementarystring(char* string)
{
		char* t=(char *)malloc(sizeof(char)*strlen(string));
		for(long int counter=0;counter<strlen(string);counter++)
				t[counter]=complementary(string[counter]);
		return t;
}
void findpalindromesandinvertedrepeats()
{
		long int nom_is_inverse,nom_is_palindrome;
		float score_palindrome,score_inverse;
		char* firststring,*secondstring;
		FILE* f1,*f2;
		f1=fopen("invertedrepeats.txt","w+");
		f2=fopen("palondbstrand.txt","w+");
		for(long int a=1;a<=len;a++)
		    for(long int length=minlength;length<=maxlength;length++)
		        {
					//get 1st string
					 firststring=(char *)malloc(sizeof(char)*(length+1));
					 firststring=getsubstr(a,a+length-1,firststring);
						float cutoff=(length*match)-(mismatches*mismatch);
						for(long int gaplength=0;gaplength<=gaplength;gaplength++)
						{
							long int b=a+length+gaplength;
							//get second string;
					       secondstring=(char *)malloc(sizeof(char)*(length+1));
							secondstring=getsubstr(b,b+length-1,secondstring);
					        score_palindrome=0,score_inverse=0,nom_is_inverse=0,nom_is_palindrome=0;
							//search for palindromes
							for(long int q=0,r=length-1;q<length,r>=0;q++,r--)
							{
									if(firststring[q]==complementary(secondstring[r]))
										{}
									else
									{
										nom_is_palindrome++;				
									}
							}
							//search for inverted repeats
							for(long int q=0,r=length-1;q<length,r>=0;q++,r--)
							{
									 if(firststring[q]==secondstring[r])
									 {}// scoreinv+=match;	
									else
									{
										nom_is_inverse++;			    			
									}
							}
							score_inverse=(length*match)-(nom_is_inverse*mismatch);	
							score_palindrome=(length*match)-(nom_is_palindrome*mismatch);	
							//if score is greater than or equal to cutoff , then string is palindrome 
									if((score_inverse>=cutoff)&&(score_inverse>=score_palindrome))
									{
										fprintf(f1,"\n location %d %s %d %s",a,firststring,gaplength,secondstring);	
									}
								if((score_palindrome>=cutoff)&&(score_palindrome>=score_inverse))		
								{
									fprintf(f2,"\n location %d %s %d ",a,firststring,gaplength);	
									fprintf(f2,"\n             %s   ",complementarystring(firststring));	
								}	
								free(secondstring);
						}
								free(firststring);
				}
fclose(f1);
fclose(f2);
}

