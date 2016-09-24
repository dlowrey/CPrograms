/******************************************************************************
 *				Dane Lowrey				      *
 *				Gelfond 001				      *
 *				Lab 8 Sec 501				      *
 * 				tokenize.c				      *
 ******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


enum token
{
 NUM,
 BIN,
 COMP,
 INV,
 WHITE
};


/*input: CHOOSES WHERE THE INPUT IS COMING FROM RETURNS FILE PTR*/
/******************************************************************************/
FILE *
input(int argc, const char *argv[])
{
  if(argc == 2)
    {return fopen(argv[1],"r");}
  else
    {return stdin;}
}

/*contains: CHECKS TO SEE IF THE OBJECT 'X' IS A BINARY OP, NUMBER, OR COMP OP*/
/******************************************************************************/
int
contains(int max,char x, const char array[])
{
  int i;
  for(i=0;i<max;i++){
    if(array[i] == x){
	return 1;
    }
  }
  return 0;
}

/*isvalid: OVERALL CHECKS TO SEE IF THE CHAR 'C' IS A VALID TOKEN*/
/******************************************************************************/
int
isvalid(char c,const char bins[], const char comps[], const char nums[],const char alpha[])
{  
  int result  = 0;
  int sum = 1;
  result = result + contains(6,c,bins);
  result = result + contains(3,c,comps);
  result = result +contains(10,c,nums); 
  result = result + contains(52,c,alpha);
  if(result <1){
    sum = 0;
  }
  return sum;
}

/*procedure: CARRIES OUT PLACING THE LINE OF CHARACTERS INTO AN ARRAY AND COMPARING THEM
 *	     WITH A SWITCH CASE.*/
/******************************************************************************/    
  
void
procedure(FILE *src)
{
  char xs[35];
  const char bins[6] = {'+','-','*','/','^',' '};
  const char comps[3] = {'>','<','='};
  const char nums[10] = {'1','2','3','4','5','6','7','8','9','0'};
  const char alpha[52] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

  int i,n;
  char c;
  enum token hold;

  while((fgets(xs,36,src))!=NULL){	/*DETERMINES WHAT THE CHARACTER IS*/
    printf("    %s\n",xs);
    for(i=0;(isvalid(xs[i],bins,comps,nums,alpha)==1);i++){        /*AND WHICH CASE TO CHOOSE*/
      c = xs[i];
      if(c == ' '){
	hold = WHITE;
      }else if((contains(6,c,bins) == 1)){
        hold = BIN;
      }else if((contains(3,c,comps) == 1)){
        n = i;
        hold = COMP;
      }else if((contains(10,c,nums) == 1)){
        hold = NUM;
      }else if(contains(52,c,alpha)){
        hold = INV;
      } 
  switch (hold){
	case BIN:
		if(c  == '+'){
		  printf("%c\taddition operator\n",c);
		}else if(c == '-'){
		  printf("%c\tsubtraction operator\n",c);
		}else if(c == '*'){
		  printf("%c\tmultiplication operator\n",c);
		}else if(c == '/'){
		  printf("%c\tdivision operator\n",c);
		}else if(c == '^'){
		  printf("%c\texponential operator\n",c);
		}
		 break;
	case COMP:
		if((c == '<')||(c == '>')){
		  if(xs[n+1] == '='){
		    printf("%c%c\tcomparison operator\n",c,xs[n+1]);
		    i = n+1;
		  }else{
		    printf("%c\tcompairson operator\n",c);
		  }
		}else{
		  printf("%c\tcomparison operator\n",c);
		}
		break;
	case NUM:
		for(n=i;(contains(10,xs[n],nums))==1;n++){
		  printf("%c",xs[n]);
		}
		i = n-1;
		printf("\tsimple numeral\n");
		break;
	case INV:
		for(n=i;(contains(52,xs[n],alpha))==1;n++){
		  printf("%c",xs[n]);
		}
		i = n-1;
		printf("\tinvalid token\n");
		break;
	case WHITE:
		break;
  }
  }
  }
}

/******************************************************************************/

int
main(int argc, const char *argv[])
{
  FILE *src = input(argc,argv);
  procedure(src);
  fclose(src);
  exit(EXIT_SUCCESS);
}
  

    
