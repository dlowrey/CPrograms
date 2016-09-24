/************************************************************
 *							    *
 *			Dane Lowrey 			    *
 *  			linked-lists.c  		    *
 * 			LAB 5 2-25-15		  	    *
 *							    *
 ************************************************************/


#include <stdio.h>
#include <stdlib.h>


struct lnode
{
  int datum;
  struct lnode *nxt;
};

int
find_minimum(struct lnode *list)
/*finds_minimum: finds the minimum integer in the linked list and returns it*/
  {
    int min= list->datum; 
    
    while(list != NULL){
      if(list->datum < min){
        min = list->datum;
      }
      list = list->nxt;
    }
    return min;
  }

struct lnode *
prepend(struct lnode *list, int x)
/*prepend: puts the desired integer at the beginning of the linked list*/
  {
    struct lnode *node = (struct lnode *)malloc(sizeof(struct lnode));
    node -> datum = x;
    node -> nxt = list;
    return list = node;
  }


struct lnode *
append(struct lnode *list, int x)
/*append: puts the desired integer at the end of the linked list*/
  {
    if(list == NULL){
      list  = (struct lnode *)malloc(sizeof(struct lnode));
      list ->datum = x;
      list -> nxt = NULL;
    }else{
      list ->nxt = append(list -> nxt, x);
    }
    return list; 
  }


struct lnode *
Ddelete(struct lnode *list, int x)
/*Ddelete: deletes the first occurance of desired element in the linked list*/
  {
    if(list == NULL){
      return NULL;
    }else if(list->datum == x){
      struct lnode *tmp;
      tmp = list->nxt;
      free(list);
      return tmp;
    }
    list->nxt = Ddelete(list->nxt,x);
    return list;
  }
 

int
check(struct lnode *list,int x)
/*check: checks to see if the desired element is in the linked list*/
  {
    if(list == NULL){
      return 0;
    }else if(list -> datum == x){
      return 1;
    }else{
      return check(list -> nxt, x);
    }
  }


int
count(struct lnode *list)
/*count: counts the number of elements in the linked list*/
  {
    int c = 0;
    while(list != NULL){
      c++;
      list = list -> nxt;
    }
    return c;
  }

void
print_list(struct lnode *list)
/*print_list: prints each element of the linked list*/
  {
    if(list == NULL){
      printf("NULL\n");
    }else{
      printf("\%d->",list -> datum);
      print_list(list -> nxt);
    }
  }

struct lnode * 
sort(struct lnode *list,struct lnode *nlist)
/*sort: sorts the linked list in ascending order*/
  {
    int min;
    if(list != NULL){
      if(nlist == NULL)
        {nlist = (struct lnode *)malloc(sizeof(struct lnode));
         nlist=NULL;}
      min = find_minimum(list);
      nlist = append(nlist,min);
      list = Ddelete(list,min);
      nlist = sort(list,nlist);
    }
    return list = nlist;
  }
         
struct lnode *
delete_all(struct lnode *list,int x)
/*delete_all: works with remove duplicates - deletes all repetitions of integer 'x'*/
/*in the linked list*/
  { 
    struct lnode *tmp = (struct lnode *)malloc(sizeof(struct lnode));
    tmp->datum = list->datum;
    tmp->nxt = list->nxt;

    while(tmp!=NULL){
      if(tmp->datum == x){
        list  = Ddelete(tmp->nxt,x);
      }
      tmp = tmp->nxt;
    }
    free(tmp);
    return list;
  }


struct lnode *
remove_duplicate(struct lnode *list)
/*remove_duplicate: removes all duplicate numbers in a linked list.*/
  {
   struct lnode *tmp,*newlist = (struct lnode *)malloc(sizeof(struct lnode));
   tmp ->datum = list->datum;
   tmp ->nxt = list->nxt;
   newlist->datum = NULL;
   newlist->nxt = NULL;
   while((tmp!=NULL)&&(list != NULL)){
    list = delete_all(list,tmp->datum);
    newlist = append(newlist,tmp->datum);
    tmp = tmp->nxt;
   }
   free(tmp);
   free(list);
   newlist = Ddelete(newlist,0);
   return newlist;
  }

struct lnode *
quit(struct lnode *list)
/*quit: frees allocated memory and then quits program*/
  {
    while (list != NULL){
      free(list);
      list = list->nxt;
    }
    return list;
  }

void
print_prompt()
/*print_prompt: prints the on screen prompt*/
  {
    printf("Select an operation to perform:\n");
    printf("\t[1] Prepend an item\n");
    printf("\t[2] Append an item\n");
    printf("\t[3] Delete an item\n");
    printf("\t[4] Check for an item\n");
    printf("\t[5] Count the number of items\n");
    printf("\t[6] Print the list\n");
    printf("\t[7] Sort the list in ascending order\n");
    printf("\t[8] Remove duplicate elements\n");
    printf("\t[9] Quit\n");
    printf(">>");
  }
int main(int argc, const char *argv[])
 {
    struct lnode *list,*nlist;
    int choice,x,result;
    while (1){
      print_prompt();
      scanf("%d",&choice);
      if(choice == 1){
        printf("ENTER A NUMBER TO PREPEND\n>>");
        scanf("%d", &x);
        list = prepend(list,x);
      }else if(choice == 2){
        printf("ENTER A NUMBER TO APPEND\n>>");
        scanf("%d", &x);
        list = append(list,x);
      }else if(choice == 3){
        printf("ENTER A NUMBER TO DELETE\n>>");
        scanf("%d", &x);
        list = Ddelete(list,x);
      }else if(choice == 4){
        printf("ENTER A NUMBER TO CHECK FOR\n>>");
        scanf("%d", &x);
        result = check(list,x);
        if(result == 1){
         printf("The number %d exists in the list\n",x);
        }else if(result == 0) 
         printf("The number %d does not exist in the list\n",x);
      }else if(choice == 5){
        result = count(list);
        printf("There are %d number(s) in the list\n",result);
      }else if(choice == 6){
        print_list(list);
      }else if(choice == 7){
        list = sort(list,nlist);
      }else if(choice == 8){
        list = remove_duplicate(list);
      }else if(choice == 9){
        list = quit(list);
        nlist = quit(nlist);
        break;
      }else{printf("PLEASE SELECT A VALID OPERATION");} 
      
    }
    return EXIT_SUCCESS;
  }
