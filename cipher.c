/*Dane Lowrey
  Cipher.c
  Lab 3
  Programing II (c)
*/


/*******************************************************************************
  Cipher takes user input, an optional command and optional file, and encrypts
  or decrypts them
*******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/******************************************************************************
  check_Method will tell the input functio what file to open for input 
  based on count of arguments and the nature of them.
  check_Method will also tell the cipher function which process to run
******************************************************************************/

typedef enum methods
{
  ENCRYPT,
  DECRYPT,
  ENCRYPT_EMPT,
  ENCRYPT_FILE,
  INVALID 
}method;

method check_method(int argc, const char *argv[])
{
  method method;
  if(argc > 1)
  {
    if((memcmp(argv[1],"-e",2))==0)
    {method = ENCRYPT;}
    else if((memcmp(argv[1],"-d",2))==0)
    {method = DECRYPT;}
    else if((memcmp(argv[1],"-",1))!=0)
    {method = ENCRYPT_FILE;}
    else
    {method = INVALID;}
  }
  else
  {method = ENCRYPT_EMPT;}
return method;
}

FILE *input(int argc,const char *argv[], method method)
{
  FILE *user_input;
  if(((method == ENCRYPT)||(method == DECRYPT))&&(argc == 3))
    {user_input = fopen(argv[2],"r");}
  else if(((method == ENCRYPT)||(method == DECRYPT))&&(argc == 2))
    {user_input = stdin;}
  else if((method == ENCRYPT_FILE))
    {user_input = fopen(argv[1],"r");}
  else if((method == ENCRYPT_EMPT))
    {user_input = stdin;}
return user_input;
}

/**********************************************************************************************************************
  cipher encrypts or decrypts the message from stdin or the input file and prints it to the screen.
  cipher compares the current character (c) to each character in the corresponding array key, and increments 'i'
  untill it finds a match, then it assigns the character form the opposite key array at the same index to be the 'new'
  character
***********************************************************************************************************************/



void cipher(FILE *src, FILE *dest, method method, const char *argv[])
{
  int i;
  int c;
  char l;
  char new;
  const char dKEY[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  const char eKEY[27] = "XYZABCDEFGHIJKLMNOPQRSTUVW";
  while((c = fgetc(src))!= EOF)
  {
     if(isalpha(c))
     {
      c=toupper(c);
      l = c;
      if(method == DECRYPT)
      {
       for(i=0;l!=eKEY[i];i++);
       new = dKEY[i];
       fprintf(dest,"%c",new);
      }
      if(((method == ENCRYPT)||(method == ENCRYPT_FILE)||(method == ENCRYPT_EMPT)))
      {
       for(i=0;l!=dKEY[i];i++);
       new = eKEY[i];
       fprintf(dest,"%c",new);
      }
     }
     else
     {printf("%c", c);}
  } 
}

/*********************************************************************************************************************
  main will control the last enum method, INVALID. If the method returns invalid (perhaps by invalid command input),
  main will exit the program before any file even tries to get opened. Other than that, it is the basc control flow
  for the funcitons. 
*******************************************************************************************************************/

int main(int argc, const char *argv[])
{
  FILE *src;
  FILE *dest;
  method method;
  method = check_method(argc, argv);
  if(method == INVALID)
    {
     printf("%s is an invalid command option\n",argv[1]);
     exit(EXIT_FAILURE);
    }

  src = input(argc, argv, method);
  dest = stdout;
  if(src == NULL)
  {
    fprintf(stderr,"%s: unable to open file\n",argv[0]);
    exit(EXIT_FAILURE);
  }
  cipher(src,dest,method,argv);
  fclose(src);
  return EXIT_SUCCESS;
} 
