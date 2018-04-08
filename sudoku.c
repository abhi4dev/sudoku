#include <stdio.h>
#include <string.h>

#define ONE   0x1 << 1
#define TWO   0x1 << 2
#define THREE 0x1 << 3
#define FOUR  0x1 << 4
#define FIVE  0x1 << 5
#define SIX   0x1 << 6
#define SEVEN 0x1 << 7
#define EIGHT 0x1 << 8
#define NINE  0x1 << 9

unsigned int su[9][9] = {0};

void initTable (void)
{
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      su[i][j] = 0x1FF;
    }
  }
}

void printTable (void)
{
  printf ("\n");
  for (int i = 0; i < 9 ; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      if (a[i][j] != 0)
      {
        printf (" %u |", su[i][j]);
      }
      else
      {
        printf ("   |");
      }
    }
    printf ("\n------------------------------------\n");
  }
  return;
}

void fillTable (void)
{
  unsigned int r = 1;
  unsigned int c = 0, e = 0;
  char d = '\0';

  printf ("\ninput the table as column number and element.");

  while (r < 10)
  {
    printf ("\nDo you what to enter elements in row %d (y or n) :", r);
    d = getchar();
    if (d != 'y' && d != 'n')
    {
      printf ("\nnot a valid input");
      continue;
    }
    else if (d == 'n')
    {
      d = getchar();
      r++;
      continue;
    }
    printf ("column :");
    scanf ("%u", &c);
    if ((c > 9) || (c < 1))
    {
      printf ("Invalid column");
      continue;
    }

    printf ("element :");
    scanf ("%u", &e);
    if ((e > 9) || (e < 1))
    {
      printf ("Invalid element");
      continue;
    }
    d = getchar();

    a[r-1][c-1] = e;

    if (c == 9)
    {
      r++;
    }
  }
  return;
}
int main (void)
{
  #initialize the table
  initTable();

  #fill the table
  fillTable();

  #print the input table
  printTable();

  #cleanup the rows
  #cleanup the columns
  #cleanup the boxes
  
}
