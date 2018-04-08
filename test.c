#include <stdio.h>

int a[9][9] = {0};

void printTable (void)
{
  printf ("\n");
  for (int i = 0; i < 9 ; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      if (a[i][j] != 0)
      {
        printf (" %d |", a[i][j]);
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

int main (void)
{

  int r = 1;
  int c, e;
  char d;

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
    scanf ("%d", &c);
    if ((c > 9) || (c < 1))
    {
      printf ("Invalid column");
      continue;
    }

    printf ("element :");
    scanf ("%d", &e);
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

  printTable();
  return 0;
}
