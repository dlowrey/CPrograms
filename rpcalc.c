/*Dane Lowrey
  RPCALC
  LAB 6
  GELFOND*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
/*******************************************************************************/
struct stack
  {
    int datum;
    struct stack *bottom;
  };

/*******************************************************************************/
void
push(struct stack **stack,int x)
  {
    struct stack *tmp = (struct stack *)malloc(sizeof(struct stack));
    tmp -> datum = x;
    tmp -> bottom = *stack;
    *stack = tmp; 
  }

/*******************************************************************************/

int
pop(struct stack **stack)
  {
    int res;
    struct stack *tmp;
    res = (*stack)->datum;
    tmp = (*stack)->bottom;
    (*stack)->bottom = NULL;
    free(*stack);
    (*stack) = tmp;
    return res; 
  }

/*******************************************************************************/
int
operation(char op, int x, int y)
  {
    if(op == 'M'){
      return x*y;
    }else if(op == 'A'){
      return x+y;
    }else if(op == 'S'){
      return y-x;
    }else if(op == 'D'){
      return y/x;
    }else{
     printf("error: the symbol '%c' is not a supported operator\n",op); 
     exit(EXIT_FAILURE); 
    }
  }

/********************************************************************************/
int 
calc(int argc, const char *argv[])
  {
    int number,i,stackdepth,x,y,result;
    struct stack *stack = (struct stack *)malloc(sizeof(struct stack));
    stackdepth = 0;
    unsigned char item;
    for(i=1;i<argc;i++){
      item = *argv[i];
      if(isalpha(item)==1){
        if(stackdepth == 2){
          x = pop(&stack);
          stackdepth--;
          y = pop(&stack);
          stackdepth--;
          result = operation(item,x,y);
          push(&stack,result);
          stackdepth++;
        }else{
          printf("Error: the operator '%c' is a binary operator\n",item);
          exit(EXIT_FAILURE);
        }
      }else if(isdigit(item)){
         number = atoi(argv[i]);
         push(&stack,number);
         stackdepth++;
      }
    }
    if(stackdepth == 1){ 
      result = pop(&stack);
    }else{
      printf("error: no operation carried out\n");
      exit(EXIT_FAILURE);
    }
    return result;
  }
    
            
/*********************************************************************************/
int
main(int argc, const char* argv[])
  {
    int result;
    result = calc(argc,argv);
    printf("%d\n",result);
    exit(EXIT_SUCCESS);
  }
