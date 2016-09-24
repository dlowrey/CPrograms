/*Dane Lowrey
  Programming II (c)
  tstats.c
*/

/* tstats will display the number of words, lines, and characters
   contained in each input file, or standard input (if no input files are
   specified) to standard output.
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>


enum state
{
    START,
    WORD,
    DELIM,
};



/* input returns a FILE * to the source specified by the user.
If no file was specified, returns stdin. */

FILE *
input(int argc,const char *argv[],int i)
{
    if (argc == 1){
	return stdin;
    } else {
	return fopen(argv[i],"r");
	 
    }
}

/* scount: counts nubmer of words, lines, and characters in the source and 
   prints the final stats to the screen */

void
scount(FILE *src, FILE *dest)
{
    int character, words, lines, chcount;
    enum state cstate;
    
    words = 0;
    chcount = 0;
    lines = 0;

    cstate = START;

    while ((character = fgetc(src))!= EOF){
	chcount ++;
	switch (cstate){
		case START:
			if(isspace(character)){
				cstate = DELIM;
				if (character == '\n') {
					lines ++;
				}
			}else{
				cstate = WORD;
				words ++;
			}
			break;
		case WORD:
			if(isspace(character)){
				cstate = DELIM;
				if(character == '\n'){
					lines++;
				}
			}
			break;
		case DELIM:
			if(character == '\n'){
				lines++;
			}else if (!isspace(character)){
				cstate = WORD;
				words++;
			}
			break;
		}
	}
	fprintf(dest,"WORDS:%d CHARACTERS:%d LINES:%d\n\n",words,chcount,lines);
}

int main(int argc, const char *argv[])
{
 int i = 1;
 FILE *src;
 FILE *dest;
 while(i<=argc){
    if(argc == 1)
     {src = stdin;
      dest = stdout;}
    else if(i<argc)
     {src = input(argc,argv,i);
      if(src == NULL)
        {fprintf(stderr, "%s: unable to open %s\n",argv[0],argv[i]);
	 break;}
      dest = stdout;
    printf("\nNAME OF FILE:%s\n",argv[i]);}
    else{break;}
    scount(src,dest);
    fclose(src);
    i++;
    }


return EXIT_SUCCESS;
}
