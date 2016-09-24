/*************************************************************************
 *				Dane Lowrey				 *
 *				Lab 7					 *
 *				G.Gelfond 001				 *
 *************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

/*************************************************************************
  Create structure to hold a pointer to first character of the word, the
  number of how many times the word has previously occurred,
  and left and right sub tree pointers 
***************************************************************************/


struct entry 
{
  char *word;
  unsigned int n;
  struct entry *left;
  struct entry *right;
};




/***************************************************************************
  insert: inserts a word found in the file into the tree in dictionary order
          by using strcmp function in standard library. Order is left to 
          right alphabetically. Also keeps cound of word occurances if the 
          word to be inserted is already in the table.
****************************************************************************/



struct entry*
insert(struct entry *table, char *str)
{
  if(table == NULL){
    table = (struct entry*)malloc(sizeof(struct entry));
    table->word = (char*)malloc(sizeof(char));
    strcpy(table->word,str); 
    table->n = 1;
    table->left = NULL;
    table->right = NULL;
  }else if(strcmp(str,table->word)==0){
    table->n = (table->n)+1;
  }else if(strcmp(str,table->word)<0){
    table->left = insert(table->left,str);
  }else{
    table->right = insert(table->right,str);
  }
  return table;
}



/******************************************************************************
 print_tree: prints out the binary tree in alphabetical order with the
             corresponding data fields.
*******************************************************************************/


void
print_tree(struct entry *tree)
{
  if(tree){
    print_tree(tree->left);
    printf("|%s\t\t%d|\n",tree->word,tree->n);
    print_tree(tree->right);
   
  }
}



/******************************************************************************
  open: opens the file and prints an error if file cannot be opened
*******************************************************************************/ 

FILE *
open(int argc,const char *argv[])
{
  FILE *input_file;
  if(argc==2){
    input_file = fopen(argv[1],"r");
    if(input_file == NULL){
      printf("Error opening file %s\n",argv[1]);
      exit(EXIT_FAILURE);
    }
  }else{
    input_file = stdin;
  }
  return input_file;
}  





/*****************************************************************************
  main control for the function allocates space for the pointer to the first
  character of a string (c) and has a control loop to read each word until the
  end of the file and put it into the binary tree.Also frees memory and closes
  file after printing the binary tree. 
******************************************************************************/
int main(int argc, const char *argv[])
{
  FILE *input_file = open(argc,argv);
  char *c = (char*)malloc(sizeof(char));
  struct entry *table; 

  while(fscanf(input_file,"%s",c)!=EOF){
    table =insert(table,c);
  }
  printf("__________________\n");
  printf("WORD\tOCCURANCES\n"); 
  print_tree(table);
  printf("__________________\n");
  free(c);
  free(table);
  fclose(input_file);
  exit(EXIT_SUCCESS);
}
  
