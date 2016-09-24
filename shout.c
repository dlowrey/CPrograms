/*Dane Lowrey
 *shout.c
 *dane.r.lowrey@ttu.edu
*/


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

/*input_from_user: returns a FILE that has the input source of the user.
if no FILE was specified, returns stdi*/

FILE*input_from_user(int argcount, const char*argv[])
{
	if(argcount ==1)
	{return stdin;}
	else
	{return fopen(argv[1],"r");}
}

/* convert takes the input, whether a file or keyboard input, converts all
 lowercase to uppercase, and writes all to the destinatin*/

void convert(FILE*src,FILE*dest)
{
	int c;
	while((c = fgetc(src)) != EOF)
	{fprintf(dest,"%c", toupper(c));}
}

int main(int argcount, const char*argv[])
{
FILE* src = input_from_user(argcount,argv);
FILE* dest = stdout;

if (src ==NULL)
{fprintf(stderr, "%s:unable to open%s\n", argv[0], argv[1]);
exit(EXIT_FAILURE);}

convert(src,dest);
fclose(src);
return EXIT_SUCCESS;}
