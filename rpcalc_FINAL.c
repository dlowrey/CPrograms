#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*Structure of the syntax tree for the order of operations, kind number or operator*/
struct AST
{
  char kind;
  char operator;
  int number;
  struct AST *left;
  struct AST *right;
};
/*Structure of the stack that will hold syntax trees*/
struct stack
{
  struct AST *data;
  struct stack *bottom;
};
/*Pop will return the top of the stack (a syntax tree) and modify the rest of the stack*/
struct AST *
pop(struct stack **s)
{
  struct AST *tree;
  struct stack *tmp;
  tree = (*s)->data;
  tmp = (*s)->bottom;
  (*s)->bottom = NULL;
  free(*s);
  (*s) = tmp;
  return tree;
}
/*push will push another syntax tree of type number or operator onto the top of the stack*/
struct stack *
push(struct stack *s, struct AST *tree)
{
  struct stack *tmp = (struct stack *)malloc(sizeof(struct stack));
  tmp->data = tree;
  tmp->bottom = s;
  return tmp;
}
/*free_TREE will clear and free the memory back to computer*/
struct AST *
free_TREE(struct AST *tree)
{
  if(tree != NULL){
    tree->left = free_TREE(tree->left);
    free(tree);
    tree->right = free_TREE(tree->right);
  }
  return tree;
}
/*create_TREE creates syntax tree using the stack to connect different roots.*/
/*    each tree node has its type (operator or number) and its fielt is char or int*/
struct AST *
create_TREE(int argc, const char *argv[])
{
  struct stack *s =(struct stack *)malloc(sizeof(struct stack));
  struct AST *tree, *op1, *op2;
  const char *c;
  int i,cc,start;
  int stackdepth = 0;
  start = *argv[1];

  if(isdigit(start)){
    start = 1;
  }else{
    start = 2;
  }
  
  for(i=start;i<argc;i++){
    c = argv[i];
    cc = *c;
    if(isdigit(cc)){
      tree =(struct AST *)malloc(sizeof(struct AST));
      tree->kind = 'N';
      tree->number = atoi(c);
      tree->operator = NULL; 
      tree->left = NULL;
      tree->right = NULL;
      s = push(s,tree);
      stackdepth++;
    }else if(stackdepth > 1){
      op1 = pop(&s);
      stackdepth--;
      op2 = pop(&s);
      stackdepth--;
      tree = (struct AST *)malloc(sizeof(struct AST));
      tree->kind = 'O';
      tree->operator = *c;
      tree->number = NULL;
      tree->left = op2;
      tree->right = op1;
      s = push(s,tree);
      stackdepth++;
    }else{
      printf("INVALID INPUT\n");
      exit(EXIT_FAILURE);
    }
  }
  if(stackdepth > 1){
    printf("INVALID INPUT\n");
    exit(EXIT_FAILURE);
  }
  return pop(&s);
}

int 
evaluate_TREE(struct AST *tree)
{
  if(tree->kind == 'O'){
    int op1 = evaluate_TREE(tree->left);
    int op2 = evaluate_TREE(tree->right);
    switch (tree->operator)
      {
        case 'A': 
		return op1 + op2;
        case 'S': 
		return op1 - op2;
        case 'X':
		return op1 * op2;
        case 'D': 
		if(op2 == 0){
                  printf("ZERO DIVISION ERROR\n");
		  exit(EXIT_FAILURE);
		}else{
		  return op1 / op2;
		}
        case 'M': 
		return op1 % op2;
        default: return 0;
      }
  }else{
    return(tree->number);
  }
}

void
print_infix(struct AST *tree ,int sw)
{
  int x = 0;
  if(tree != NULL){
    if(tree->kind == 'O'){
      if(((tree->operator == 'A')||(tree->operator == 'S'))&&(sw == 1)){
          printf("(");
          x = 1;
      }
    }

    print_infix(tree->left,1);
    if(tree->kind == 'O'){
      switch(tree->operator)
        {
          case 'A': printf("+");
                    break;
          case 'S': printf("-");
                    break;
          case 'D': printf("/");
                    break;
          case 'X': printf("*");
                    break;
          case 'M': printf("%%");
                    break;
          default: printf("\nERROR,ENCOUNTERED INVALID OPERATOR %c\n",tree->operator);
                   exit(EXIT_FAILURE);
                   break;
        }
    }else if(tree->kind == 'N'){
      printf("%d",tree->number);
    }
    print_infix(tree->right,1);

    if(x==1){
      printf(")");
    }
  }
}

int
wrt_asmble(struct AST *tree,int start)
{
  int new,left,right;
  if(tree->kind == 'N'){
    new = start;
    printf("MOVE R%d %d\n",new,tree->number);
    return new;
  }else{
    left =  wrt_asmble(tree->left,start);
    right = wrt_asmble(tree->right,start+left);
    new = right +1;
    switch(tree->operator)
      {
	case 'A': printf("ADD R%d R%d R%d\n",left,right,new);
		  break;
        case 'S': printf("SUB R%d R%d R%d\n",left,right,new);
		  break;
        case 'D': printf("DIV R%d R%d R%d\n",left,right,new);
		  break;
        case 'X': printf("MULT R%d R%d R%d\n",left,right,new);
		  break;
        case 'M': printf("MOD R%d R%d R%d\n",left,right,new);
		  break;
      }
    return new;
  }
}
    
    

int
main(int argc, const char *argv[])
{
  struct AST *tree;
  tree = create_TREE(argc,argv);
  const char *choice = argv[1];
  int choice1 = *choice;

  if(!strcmp(choice,"-c")){
    print_infix(tree,0);
    printf("\n");
  }else if(!strcmp(choice,"-g")){
    printf("WRT R%d\n",wrt_asmble(tree,1)); 
  }else if((!strcmp(choice,"-e"))||(isdigit(choice1))){
    printf("%d\n",evaluate_TREE(tree));
  }

  free_TREE(tree);
  return 0;
}   
