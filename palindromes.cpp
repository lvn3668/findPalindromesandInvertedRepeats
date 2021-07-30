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
# define MINLENGTH 10
# define MAXLENGTH 20
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
		numberofmismatchesallowed=atoi(argv[5]);
		matchscore=atoi(argv[6]);
	    	mismatchscore=atoi(argv[7]);
			if (minlength < MINLENGTH)
			{
				print("Minimum length of palindrome / inverted repeat should be greater than  %d", MINLENGTH);
				exit;
			}
			if ( (maxlength > MAXLENGTH) || (maxlength < 0) || (maxlength < minlength))
			{
				print("Maximum length of palindrome / inverted repeat should be between %d and %d", MINLENGTH, MAXLENGTH);
				exit;
			}

		readDNA(filename);
	        findpalindromesandinvertedrepeats();
}
char* getsubstr(long int start,long int end,char* string)
{
		long int substrcounter=0,counter;
		for(counter=start;counter<=end && end<=len;counter++)
		{
		    string[substrcounter]=seq[counter];
	  	    substrcounter++;		
		}
		string[substrcounter]='\0';
		return string;
}
// Find complementary character
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
// Build complementary string for inverted repeats
char* complementarystring(char* string)
{
		char* complementarystring=(char *)malloc(sizeof(char)*strlen(string));
		for(long int counter=0;counter<strlen(string);counter++)
				complementarystring[counter]=complementary(string[counter]);
		return complementarystring;
}

// check if substr at given position is palindrome or inverted repeat
// get substring
// 
void findpalindromesandinvertedrepeats()
{
		long int nom_is_inverse,nom_is_palindrome;
		float score_palindrome,score_inverse;
		char* firststring,*secondstring;
		FILE* pointertoinvertedrepeatsfile,*pointertopalindromefiles;
		pointertoinvertedrepeatsfile=fopen("invertedrepeats.txt","w+");
		pointertopalindromefiles=fopen("palondbstrand.txt","w+");
		for(long int a=1;a<=len;a++)
		    for(long int length=minlength;length<=maxlength;length++)
		        {
					//get 1st string
					 firststring=(char *)malloc(sizeof(char)*(length+1));
					 firststring=getsubstr(a,a+length-1,firststring);
						float cutoff=(length*matchscore)-(numberofmismatchesallowed*mismatchscore);
						for(long int gaplength=0;gaplength<=gaplength;gaplength++)
						{
							long int b=a+length+gaplength;
							//get second string;
					       secondstring=(char *)malloc(sizeof(char)*(length+1));
							secondstring=getsubstr(b,b+length-1,secondstring);
					        score_palindrome=0,score_inverse=0,nom_is_inverse=0,nom_is_palindrome=0;
							//search for palindromes
							// Move along fwd strand and complementary strand and check for identical bases
							// Palindrome score = maximum score possible (match value x length of sequence) - (number of mismatches x mismatch score)
							for(long int forwardcounter=0,reversecounter=length-1;forwardcounter<length,reversecounter>=0;forwardcounter++,reversecounter--)
							{
									if(firststring[forwardcounter]==complementary(secondstring[reversecounter]))
										{}
									else
									{
										nom_is_palindrome++;				
									}
							}
							//search for inverted repeats
							// Inverted repeat is calculated as
							// move along fwd strand for sequence one
							// move along same strand for sequence two (in reverse order)
							// score calculated = max score (length of fragment x match score) - (number of mismatches x mismatch score)
							for(long int forwardcounter=0,reversecounter=length-1;forwardcounter<length,reversecounter>=0;forwardcounter++,reversecounter--)
							{
									 if(firststring[forwardcounter]==secondstring[reversecounter])
									 {}// scoreinv+=match;	
									else
									{
										nom_is_inverse++;			    			
									}
							}
							score_inverse=(length*matchscore)-(nom_is_inverse*mismatchscore);	
							score_palindrome=(length*matchscore)-(nom_is_palindrome*mismatchscore);	
							//if score is greater than or equal to cutoff , then string is palindrome 
							// if score is greater than or equal to cutoff, string is inverted repeat 
							// Write out to file, both fragments and gaplength along with score 
									if((score_inverse>=cutoff)&&(score_inverse>=score_palindrome))
									{
										fprintf(pointertoinvertedrepeatsfile,"\n location %d %s %d %s",a,firststring,gaplength,secondstring);	
									}
								if((score_palindrome>=cutoff)&&(score_palindrome>=score_inverse))		
								{
									fprintf(pointertopalindromefiles,"\n location %d %s %d ",a,firststring,gaplength);	
									fprintf(pointertopalindromefiles,"\n             %s   ",complementarystring(firststring));	
								}	
								free(secondstring);
						}
								free(firststring);
				}
fclose(pointertoinvertedrepeatsfile);
fclose(pointertopalindromefiles);
}

