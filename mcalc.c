/*Dane Lowrey
  Mcalc
  Progamming II (C)
  lab 3
*/

/******************************************************************************
mcalc : a program that can multiply, add, and subtract matricies. Takes 3
arguments, mcalc[-a,-s,-m][file1][file2]. File one and two contain the matriciesthat will be operated on.
*******************************************************************************/

#include <stdio.h>
#include <strings.h>
#include <ctype.h>
#include <stdlib.h>
/*custom structure matrix will hold 3 types of information .rows, .cols, and .data*/
struct matrix
{
  int rows;
  int cols;
  int **data;
};

/*option will be used to pass the option the user selected to various functions*/

typedef enum
{
  INVALID,
  ADD,
  SUB,
  MULT
}option;



FILE *input(int argc, const char argv[])
	{
	  FILE * src;
	  src= fopen(argv,"r");
	  return src; 
	}

/*Reads matrix and assigns to m1 and m2 (in main), */
struct matrix read_matrix(FILE *src)
	{
	  struct matrix m;
	  int i,j;
	  fscanf(src,"%d", &m.rows);  /*Read in from the file*/
	  fscanf(src,"%d", &m.cols);
	  m.data = (int **)malloc(m.rows *sizeof(int *)); /*allocate memory*/
	  for(i=0;i<m.rows;i++)
	    {m.data[i] = (int *)malloc(m.cols *sizeof(int));}

	  for(i = 0;i<m.rows;i++)
	  {for(j=0;j<m.cols;j++)
	    {fscanf(src,"%d", &m.data[i][j]);}}
	  return m;
	}
/*Creates new matrix to store outcome of process, according to operation*/
struct matrix new_matrix_mem(struct matrix m1, struct matrix m2, option choice)
	{
	  int i;
	  struct matrix nm;
	  if((choice == ADD)||(choice == SUB))
	    {nm.data = (int **)malloc(m1.rows * sizeof(int *));
	      for(i = 0; i < m1.cols; i++)
	        {nm.data[i] = (int *)malloc(m1.cols * sizeof(int));}
	    }
	  else if(choice == MULT)
	      {nm.data = (int **)malloc(m1.rows * sizeof(int *));
	      for(i = 0; i <m1.rows ;i++)
	        {nm.data[i] = (int *)malloc(m2.cols * sizeof(int));}
	    }
	  return nm;
	}
/*writes the nm (new matrix) to the ouput file (default stdout)*/
void write_matrix(FILE* dest, struct matrix nm)
	{
	  int i, j;
	  fprintf(dest, "%d\n", nm.rows);
	  fprintf(dest, "%d\n", nm.cols);

	  for(i = 0; i <nm.rows; i++)
	    {for(j = 0; j<nm.cols; j++)
	      {fprintf(dest,"%d\t", nm.data[i][j]);}
	  fprintf(dest,"\n");
	    }
	}

/*gets option and passes it to main to be passed to other functions (ADD, SUB, MULT or INVALID)*/
option check_option(int argc, const char *argv[])
	{
	  option choice;
	  if((memcmp(argv[1], "-a",2))==0)
	    {choice = ADD;}
	  else if((memcmp(argv[1],"-s",2))==0)
	    {choice = SUB;}
	  else if((memcmp(argv[1],"-m",2))==0)
	    {choice = MULT;}
	  else
	    {choice = INVALID;}
	  return choice;
	}

/*checks to see if the option is even possible to apply to given matricies*/
int possible(struct matrix m1, struct matrix m2, option choice)
	{
	  int result;
	  if((choice == ADD)||(choice == SUB))
	    {if((m1.rows == m2.rows)&&(m1.cols == m2.cols))
	      {result =0;}
	    }
	  else if(choice == MULT)
	    {if(m1.cols == m2.rows)
	      {result = 0;}
	    }

	  else
	    {result = 1;}
	  return result; 
	}

/*Process applies the option to the two matricies, different case for add, sub, and mult.*/
struct matrix process(struct matrix m1, struct matrix m2, option choice,struct matrix nm)
	{
	  int i,j;
	  int k,hold;
	  
	  if(choice ==  ADD)
	    {nm.rows = m1.rows;
	     nm.cols = m1.cols;
	     for(i = 0; i < m1.rows; i++)
	      {for(j = 0; j < m1.cols; j++)
		{hold = 0;
	         hold = hold+( m1.data[i][j] + m2.data[i][j]);
		 nm.data[i][j] = hold;}
	      }
	    }

	  else if(choice == SUB)
	    {nm.rows = m1.rows;
	     nm.cols = m1.cols;
	     for(i = 0; i < m1.rows; i++)
	      {for(j = 0; j < m1.cols; j++)
	        {nm.data[i][j] = m1.data[i][j] - m2.data[i][j];}
	      }
	    }


	   else if(choice == MULT)
	    {if(m1.rows>m2.rows)
		{nm.rows = m1.rows;
		 nm.cols = m2.cols;}
	     else if(m1.rows<m2.rows)
		{nm.rows = m1.rows;
		 nm.cols = m2.cols;}
	     for(i=0;i<m1.rows;i++)
	      {for(j=0;j<m2.cols;j++)
	        {hold = 0;
	         for(k=0;k<m1.cols;k++)
		   {hold = hold + (m1.data[i][k] * m2.data[k][j]);
	           nm.data[i][j]= hold;}
	        }
	      }
	    }

	  return nm;
	}
/*Clears the data and sends it back to the comp to be used  by anything else (used in main)*/
void clear_matrix(struct matrix m)
	{
	  int i;
	  for(i = 0; i<m.rows; i++)
	    {free(m.data[i]);}
	
	  free(m.data);
	}


int main(int argc, const char *argv[])
	{ if(argc < 4)
	    {printf("Please input an output destination, operation, and two files\n");
	     exit(EXIT_FAILURE);}
	  FILE *src1 = input(argc,argv[2]);
	  FILE *src2 = input(argc,argv[3]);
	  FILE *dest = stdout;

	  struct matrix m1;
	  struct matrix m2;
	  struct matrix nm;
	  option choice;
	  int result = 0;

	  if((src1 == NULL)||(src2 == NULL))
	    {fprintf(stderr, "%s unable to open file %s or %s\n", argv[0], argv[2], argv[3]);
	     exit(EXIT_FAILURE);}

	  choice = check_option(argc, argv);
	  if (choice == INVALID)
	    {printf("Ivalid option, please input -a, -s, or -m\n");
	     exit(EXIT_FAILURE);}
	  m1 = read_matrix(src1);
	  fclose(src1);
	  m2 = read_matrix(src2);
	  fclose(src2);

	  result = possible(m1,m2,choice);
	  if(result != 0 )
	    {printf("Matrix structure is invalid for process\n");
	     exit(EXIT_FAILURE);}
	  nm = new_matrix_mem(m1,m2,choice);
	  nm = process(m1,m2,choice,nm);

	  write_matrix(dest,nm);
	  clear_matrix(m1);
	  clear_matrix(m2);
	  clear_matrix(nm);
	  return EXIT_SUCCESS; 
	}
