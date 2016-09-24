/*DANE LOWREY
  tconv [method] [file]
  Prog.Princip.Lab-501
*/

/* Converts text from screen or file with user specified method. */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/*Takes number of inputs and decides whether to recieve input from
  a file or from the standard input, while applying the specified 
  operation to the input either way.*/

FILE *input(int argc, const char *argv[])
{
	if (argc == 1)
	  {return stdin;}
	else if(argc == 2)
	  {return stdin;}
	else 
	  {return fopen(argv[2],"r");}
}






/*Converts text from "input" to lowercase (-l), uppercase (-u), or 
  encodes in rot13 (-r) as specified by input. If an incorrect operation is 
  given will print an errror*/

void convert(FILE *src, FILE *dest,const char *argv[],int argc)
{
	int c;
	char *rot = "-r";
	char *upper = "-u";
	char *lower = "-l";

	    while((c = fgetc(src))!= EOF)
		{
		 if (argc > 1)
		{
		 if (strcmp(argv[1],rot) == 0)
		{ 
		  if(('A' <=c)&&(c<='M'))
			{c = c+13;}
		  else if(('N' <= c)&&(c <= 'Z'))
			{c = c-13;}
		  if(('a' <= c)&&(c <= 'm'))
			{c = c+13;}
		  else if(('n' <= c)&&(c <= 'z'))
			{c = c-13;}
		  fprintf(dest,"%c",c);
		}


		 else if (strcmp(argv[1],upper) == 0)
		 {fprintf(dest,"%c",toupper(c));}


		 else if (strcmp(argv[1],lower) == 0)
		 {fprintf(dest,"%c",tolower(c));}
		 

		 else 
		{printf("OPTION '%s' IS UNSUPPORTED\n",argv[1]);
		 break;}
		}
		else
		{char w = c;
		 fprintf(dest,"%c",w);}
		}
}



int main(int argc, const char *argv[])
{
	FILE *src = input(argc,argv);
	FILE *dest = stdout;
	if (src ==NULL)
	{fprintf(stderr,"%s:unable to open:%s\n",argv[0],argv[2]);
	 exit(EXIT_FAILURE);}

	convert(src,dest,argv,argc);
	fclose(src);
	return EXIT_SUCCESS;
}
